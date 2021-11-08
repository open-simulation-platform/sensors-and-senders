#include <boost/property_tree/xml_parser.hpp>
#include <algorithm>

#include "NmeaSenderComponent.hpp"
#include "ConfigParser.hpp"

NmeaSenderComponent::NmeaSenderComponent(const std::string& instance_name, const fmi2Type& type, const fmi2String& uuid, const std::string& resource_directory,
        const fmi2CallbackFunctions* callback_functions)
    : Component(instance_name, type, uuid, resource_directory, callback_functions)
{

    parseModelDescription();
    parseConfig();
}

void NmeaSenderComponent::parseModelDescription() {

    std::string scheme {"file://"};
    const auto n = resources_directory_.find(scheme);
    if (n != std::string::npos) {
        resources_directory_.erase(n, scheme.length());
    }

    std::string model_description_path = resources_directory_ + "/../modelDescription.xml";

    boost::property_tree::ptree modelDescription;
    try {
        boost::property_tree::read_xml(model_description_path, modelDescription);

    } catch(const boost::property_tree::xml_parser_error& error) {

        callback_functions_->logger(nullptr, instance_name_.c_str(), fmi2Fatal,
            "debug", error.what());
    }

    auto modelVariables = modelDescription.get_child("fmiModelDescription.ModelVariables");

    auto toVariables = [](const std::pair<boost::property_tree::ptree::key_type, boost::property_tree::ptree>& property) {
        
        Variable var {};
        var.valueReference = static_cast<fmi2ValueReference>(property.second.get<int>("<xmlattr>.valueReference"));
        var.causality = toCausality(property.second.get<std::string>("<xmlattr>.causality"));

        auto field_name = "Invalid";
        if(property.second.get_child_optional("Real")) {
            var.type = Type::Real;
            field_name = "Real";
            var.start = "0.0";
        } else if (property.second.get_child_optional("Integer")) {
            var.type = Type::Integer;
            field_name = "Integer";
            var.start = "0";
        } else if (property.second.get_child_optional("Boolean")) {
            var.type = Type::Boolean;
            field_name = "Boolean";
            var.start = "0";
        } else if (property.second.get_child_optional("String")) {
            var.type = Type::String;
            field_name = "String";
            var.start = "";
        } else {
            var.type = Type::Invalid;
        }

        if(var.causality == Causality::Parameter || var.causality == Causality::Input) {
            var.start = property.second.get_child_optional(field_name)->get<std::string>("<xmlattr>.start");
        }

        auto name = property.second.get<std::string>("<xmlattr>.name");

        return std::make_pair(name, var);
    };

    std::transform(modelVariables.begin(), modelVariables.end(), std::inserter(variables_, variables_.end()), toVariables);

    for (const auto& [name, variable] : variables_) {
        (void) name;
        
        switch(variable.type) {
            case Type::Real:
                m_reals[variable.valueReference] = std::stod(variable.start);
                break;
            case Type::Integer:
                m_integers[variable.valueReference] = std::stoi(variable.start);
                break;
            case Type::Boolean:
                m_booleans[variable.valueReference] = static_cast<bool>(std::stoi(variable.start));
                break;
            case Type::String:
                m_strings[variable.valueReference] = variable.start;
                break;
            case Type::Invalid:
                break;
        }
    }
}

void NmeaSenderComponent::parseConfig() {

    std::string path = resources_directory_ + "/NmeaConfig.json";

    const auto NmeaConfig = parseNmeaConfig(path);
    telegrams_ = NmeaConfig.telegrams;
    if(telegrams_.empty()) {
        callback_functions_->logger(nullptr, instance_name_.c_str(), fmi2Warning,
            "debug", "No NMEA telegrams have been configured for this sender. Please check resources/NmeaConfig.json");
    }
}

void NmeaSenderComponent::step(double step_size) {

    (void) step_size;
    remoteIp_ = m_strings[25];
    remotePort_ = m_integers[26];

    updateTelegrams();
    sendTelegrams();
}

void NmeaSenderComponent::updateTelegrams() {

    const auto updateField = [this](Nmea::Field& field) {

        if (variables_.find(field.name) != variables_.end()) {
            auto variable = variables_[field.name];
            switch(variable.type) {
                case Type::Real:
                    field.value = std::to_string(m_reals[variable.valueReference]);
                    break;
                case Type::Integer:
                    field.value = std::to_string(m_integers[variable.valueReference]);
                    break;
                case Type::Boolean:
                    field.value = std::to_string(static_cast<int>(m_booleans[variable.valueReference]));
                    break;
                case Type::String:
                    field.value = m_strings[variable.valueReference];
                    break;
                default:
                    field.value = "";
            }
        }
    };

    for (auto& telegram : telegrams_) {
        std::for_each(telegram.fields.begin(), telegram.fields.end(), updateField);
    }
}

void NmeaSenderComponent::sendTelegrams() {
    
    for (const auto& telegram: telegrams_) {

        auto payload = encode(telegram);
        udpSender_.sendTo(remoteIp_, remotePort_, payload);
    }
}

void NmeaSenderComponent::enter_initialization() {
}

void NmeaSenderComponent::exit_initialization() {
    udpSender_.open();
}
