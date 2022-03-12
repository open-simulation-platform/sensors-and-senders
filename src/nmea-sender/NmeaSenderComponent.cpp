#include <boost/property_tree/xml_parser.hpp>
#include <algorithm>

#include "NmeaSenderComponent.hpp"
#include "ConfigParser.hpp"

NmeaSenderComponent::NmeaSenderComponent(const std::string& instance_name, const fmi2Type& type, const fmi2String& uuid, const std::string& resource_directory,
        const fmi2CallbackFunctions* callback_functions)
    : Component(instance_name, type, uuid, resource_directory, callback_functions)
{

    parse_model_description();
    parse_config();
}

void NmeaSenderComponent::parse_model_description() {

    #ifdef _WIN32
        std::string scheme {"file:///"};
    #else
        std::string scheme {"file://"};
    #endif
    
    const auto n = m_resources_directory.find(scheme);
    if (n != std::string::npos) {
        m_resources_directory.erase(n, scheme.length());
    }

    std::string model_description_path = m_resources_directory + "/../modelDescription.xml";

    boost::property_tree::ptree modelDescription;
    try {
        boost::property_tree::read_xml(model_description_path, modelDescription);

    } catch(const boost::property_tree::xml_parser_error& error) {

        m_callback_functions->logger(nullptr, m_instance_name.c_str(), fmi2Fatal,
            "debug", error.what());
    }

    auto model_variables = modelDescription.get_child("fmiModelDescription.ModelVariables");

    auto to_variables = [](const std::pair<boost::property_tree::ptree::key_type, boost::property_tree::ptree>& property) {
        
        Variable var {};
        var.reference = static_cast<fmi2ValueReference>(property.second.get<int>("<xmlattr>.valueReference"));
        var.causality = to_causality(property.second.get<std::string>("<xmlattr>.causality"));

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

    std::transform(model_variables.begin(), model_variables.end(), std::inserter(m_variables, m_variables.end()), to_variables);

    for (const auto& [name, variable] : m_variables) {
        (void) name;
        
        switch(variable.type) {
            case Type::Real:
                m_reals[variable.reference] = std::stod(variable.start);
                break;
            case Type::Integer:
                m_integers[variable.reference] = std::stoi(variable.start);
                break;
            case Type::Boolean:
                m_booleans[variable.reference] = static_cast<bool>(std::stoi(variable.start));
                break;
            case Type::String:
                m_strings[variable.reference] = variable.start;
                break;
            case Type::Invalid:
                break;
        }
    }
}

void NmeaSenderComponent::parse_config() {

    std::string path = m_resources_directory + "/NmeaConfig.json";

    const auto nmea_config = parse_nmea_config(path);
    m_telegrams = nmea_config.telegrams;
    if(m_telegrams.empty()) {
        m_callback_functions->logger(nullptr, m_instance_name.c_str(), fmi2Warning,
            "debug", "No NMEA telegrams have been configured for this sender. Please check resources/NmeaConfig.json");
    }
}

void NmeaSenderComponent::step(double step_size) {

    (void) step_size;
    m_remote_ip = m_strings[25];
    m_remote_port = m_integers[26];

    update_telegrams();
    send_telegrams();
}

void NmeaSenderComponent::update_telegrams() {

    const auto update_field = [this](Nmea::Field& field) {

        if (m_variables.find(field.name) != m_variables.end()) {
            auto variable = m_variables[field.name];
            switch(variable.type) {
                case Type::Real:
                    field.value = std::to_string(m_reals[variable.reference]);
                    break;
                case Type::Integer:
                    field.value = std::to_string(m_integers[variable.reference]);
                    break;
                case Type::Boolean:
                    field.value = std::to_string(static_cast<int>(m_booleans[variable.reference]));
                    break;
                case Type::String:
                    field.value = m_strings[variable.reference];
                    break;
                default:
                    field.value = "";
                    break;
            }
        }
    };

    for (auto& telegram : m_telegrams) {
        std::for_each(telegram.fields.begin(), telegram.fields.end(), update_field);
    }
}

void NmeaSenderComponent::send_telegrams() {
    
    for (const auto& telegram: m_telegrams) {

        auto payload = encode(telegram);
        m_udp_sender.send_to(m_remote_ip, m_remote_port, payload);
    }
}

void NmeaSenderComponent::exit_initialization() {
    m_udp_sender.open();
}
