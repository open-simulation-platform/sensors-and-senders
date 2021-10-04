#include "Component.hpp"

Component::Component(std::string instanceName, const fmi2Type type, const fmi2String uuid,
        std::string resourcesDirectory, const fmi2CallbackFunctions* callbackFunctions)
    : instance_name_(std::move(instanceName))
    , uuid_(uuid)
    , resources_directory_(std::move(resourcesDirectory))
    , type_(type)
    , callback_functions_(callbackFunctions) 
{
}


void Component::setReal(fmi2ValueReference reference, fmi2Real value) {
    values_[reference].value = value;
}

std::optional<double> Component::real(fmi2ValueReference reference) const {

    if(values_.find(reference) != values_.end()) {      
        if(auto value = std::get_if<double>(&(values_.at(reference).value))) {
            return {*value};
        }
    }

    return {};
}

void Component::setInteger(fmi2ValueReference reference, fmi2Integer value) {
    values_[reference].value = value;
}

std::optional<int> Component::integer(fmi2ValueReference reference) const {
    
    if(values_.find(reference) != values_.end()) {      
        if(auto value = std::get_if<int>(&(values_.at(reference).value))) {
            return {*value};
        }
    }

    return {};
}

void Component::setBoolean(fmi2ValueReference reference, fmi2Boolean value) {
    values_[reference].value = static_cast<bool>(value);
}

std::optional<bool> Component::boolean(fmi2ValueReference reference) const {

    if(values_.find(reference) != values_.end()) {      
        if(auto value = std::get_if<bool>(&(values_.at(reference).value))) {
            return {*value};
        }
    }
    
    return {};
}

void Component::setString(fmi2ValueReference reference, fmi2String string) {
        values_[reference].value = std::string {string};
}

std::optional<fmi2String> Component::string(fmi2ValueReference reference) const {
    
    if(values_.find(reference) != values_.end()) {
        if(const auto value = std::get_if<std::string>(&(values_.at(reference).value))) {
            return value->c_str();
        }
    }

    return {};
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
    if(callback_functions_ && callback_functions_->logger) {
            callback_functions_->logger(nullptr, instance_name_.c_str(), status, category.c_str(),
        message.c_str());
    }
}