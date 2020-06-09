#include "NmeaSenderComponent.h"
#include <boost/filesystem.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <utility>
#include <nlohmann/json.hpp>
#include <algorithm>
#include "ConfigParser.h"

NmeaSenderComponent::NmeaSenderComponent(const std::string& instance_name, const fmi2Type type, const fmi2String uuid, const std::string& resource_directory,
        const fmi2CallbackFunctions* callback_functions)
    : Component(instance_name, type, uuid, resource_directory, callback_functions)
{

    parseModelDescription();
    parseConfig();
    udpSender_.open();
}

void NmeaSenderComponent::parseModelDescription() {

    const std::vector<std::string> schemes {"file:///", "file://"};
    for(const auto& scheme : schemes) {
        const auto n = resources_directory_.find(scheme);
        if (n == std::string::npos) {
            continue;
        }
        resources_directory_.erase(n, scheme.length());
    }

    boost::filesystem::path path (resources_directory_.c_str());

    auto descriptionPath = path.parent_path();
    descriptionPath /= "modelDescription.xml";

    if(!boost::filesystem::exists(descriptionPath)) {

        auto message = descriptionPath.string() + " not found\n";
        
        callback_functions_->logger(nullptr, instance_name_.c_str(), fmi2Fatal,
            "debug", message.c_str());
    }

    boost::property_tree::ptree modelDescription;
    try {
        boost::property_tree::read_xml(descriptionPath.string(), modelDescription);

    } catch(const boost::property_tree::xml_parser_error& error) {

        callback_functions_->logger(nullptr, instance_name_.c_str(), fmi2Fatal,
            "debug", error.what());
    }

    auto modelVariables = modelDescription.get_child("fmiModelDescription.ModelVariables");

    auto toVariables = [](const std::pair<boost::property_tree::ptree::key_type, boost::property_tree::ptree>& property) {
        
        Variable var {};
        var.valueReference = static_cast<fmi2ValueReference>(property.second.get<int>("<xmlattr>.valueReference"));
        var.causality = toCausality(property.second.get<std::string>("<xmlattr>.causality"));

        if(property.second.get_child_optional("Real")) {
            var.type = Type::Real;
        } else if (property.second.get_child_optional("Integer")) {
            var.type = Type::Integer;
        } else if (property.second.get_child_optional("Boolean")) {
            var.type = Type::Boolean;
        } else if (property.second.get_child_optional("String")) {
            var.type = Type::String;
        } else {
            var.type = Type::Invalid;
        }

        auto name = property.second.get<std::string>("<xmlattr>.name");

        return std::make_pair(name, var);
    };

    std::transform(modelVariables.begin(), modelVariables.end(), std::inserter(variables_, variables_.end()), toVariables);

    for (const auto& [name, variable] : variables_) {
        (void) name;
        Value value;
        
        switch(variable.type) {
            case Type::Real:
                values_[variable.valueReference].value.emplace<double>(0.0);
                break;
            case Type::Integer:
                values_[variable.valueReference].value.emplace<int>(0);
                break;
            
            case Type::Boolean:
                values_[variable.valueReference].value.emplace<bool>(false);
                break;
            
            case Type::String:
                values_[variable.valueReference].value.emplace<std::string>("");
                break;
            case Type::Invalid:
                break;
        }
    }
}

void NmeaSenderComponent::parseConfig() {

    boost::filesystem::path path(resources_directory_.c_str());
    path /= "NmeaConfig.json";

    const auto NmeaConfig = parseNmeaConfig(path);
    telegrams_ = NmeaConfig.telegrams;

    remoteIp_ = NmeaConfig.remoteIp;
    remotePort_ = NmeaConfig.remotePort;
}

void NmeaSenderComponent::step(double step_size) {

    (void) step_size;

    updateTelegrams();
    sendTelegrams();
}

void NmeaSenderComponent::updateTelegrams() {

    const auto updateField = [this](NmeaField& field) {

        if (variables_.find(field.name) != variables_.end()) {
            auto variable = variables_[field.name];
            field.value = values_[variable.valueReference].value;
        }
    };

    for (auto& telegram : telegrams_) {

        std::for_each(telegram.begin(), telegram.end(), updateField);
    }
}

void NmeaSenderComponent::sendTelegrams() {
    
    for (const auto& telegram: telegrams_) {

        auto nmeaTelegram = telegram.encode();
        udpSender_.sendTo(remoteIp_, remotePort_, nmeaTelegram);
    }
}

void NmeaSenderComponent::enter_initialization() {
    
}
