#include "Component.hpp"

Component::Component(std::string instanceName, const fmi2Type& type, const fmi2String& uuid,
        std::string resourcesDirectory, const fmi2CallbackFunctions* callbackFunctions)
    : instance_name_(std::move(instanceName))
    , uuid_(uuid)
    , resources_directory_(std::move(resourcesDirectory))
    , type_(type)
    , callback_functions_(callbackFunctions) 
{
}


fmi2Status Component::set_real(fmi2ValueReference reference, fmi2Real value) {
    m_reals[reference] = value;
    return fmi2OK;
}

fmi2Status Component::real(fmi2ValueReference reference, fmi2Real& value) const {

    if(m_reals.find(reference) != m_reals.end()) {      
        value = m_reals.at(reference);
        return fmi2OK;
    }

    return fmi2Error;
}

fmi2Status Component::set_integer(fmi2ValueReference reference, fmi2Integer value) {
    m_integers[reference] = value;
    return fmi2OK;
}

fmi2Status Component::integer(fmi2ValueReference reference, fmi2Integer& value) const {
    
    if(m_integers.find(reference) != m_integers.end()) {      
        value = m_integers.at(reference);
        return fmi2OK;
    }

    return fmi2Error;
}

fmi2Status Component::set_boolean(fmi2ValueReference reference, fmi2Boolean value) {
    m_booleans[reference] = static_cast<bool>(value);
    return fmi2OK;
}

fmi2Status Component::boolean(fmi2ValueReference reference, fmi2Boolean& value) const {

    if(m_booleans.find(reference) != m_booleans.end()) {      
        value = static_cast<fmi2Boolean>(m_booleans.at(reference));
        return fmi2OK;
    }

    return fmi2Error;
}

fmi2Status Component::set_string(fmi2ValueReference reference, fmi2String string) {
    m_strings[reference] = std::string {string};
    return fmi2OK;
}

fmi2Status Component::string(fmi2ValueReference reference, fmi2String& string) const {
    
    if(m_strings.find(reference) != m_strings.end()) {
        string = m_strings.at(reference).c_str();
        return fmi2OK;
    }

    return fmi2Error;
}

const std::string_view Component::instanceName() const {
    return instance_name_;
}

fmi2Type Component::type() const {
    return type_;
}

const std::string_view Component::uuid() const {
    return uuid_;
}

const std::string_view Component::resourcesDirectory() const {
    return std::string_view (resources_directory_);
}

void Component::logMessage(const fmi2Status& status, const std::string& message, const std::string& category) const {
    if(callback_functions_ != nullptr && callback_functions_->logger != nullptr) {
            callback_functions_->logger(nullptr, instance_name_.c_str(), status, category.c_str(),
        message.c_str());
    }
}