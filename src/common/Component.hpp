#pragma once

#include <variant>
#include <map>
#include <optional>
#include <string>

#include "common/fmi/fmi2TypesPlatform.h"
#include "common/fmi/fmi2FunctionTypes.h"

#ifdef _WIN32
    #define DLL_EXPORT __declspec(dllexport)
#else 
    #define DLL_EXPORT
#endif

struct Value {
    std::variant<int, double, bool, std::string> value;  
};

class DLL_EXPORT Component {
public:

    Component(std::string instanceName, const fmi2Type& type, const fmi2String& uuid,  
        std::string resourcesDirectory, const fmi2CallbackFunctions* callbackFunctions);

    virtual ~Component() = default;

    Component(const Component&) = default;
    Component(Component&&) = default;

    Component& operator=(const Component&) = default;
    Component& operator=(Component&&) = default;

    void setReal(fmi2ValueReference reference, fmi2Real value);
    std::optional<double> real(fmi2ValueReference reference) const;

    void setInteger(fmi2ValueReference reference, fmi2Integer value);
    std::optional<int> integer(fmi2ValueReference reference) const;

    void setBoolean(fmi2ValueReference reference, fmi2Boolean value);
    std::optional<bool> boolean(fmi2ValueReference reference) const;

    void setString(fmi2ValueReference reference, fmi2String string);
    std::optional<fmi2String> string(fmi2ValueReference reference) const;

    virtual void step(double step_size) = 0;
    virtual void enter_initialization() = 0;

    const std::string_view instanceName() const;
    fmi2Type type() const;
    const std::string_view uuid() const;
    const std::string_view resourcesDirectory() const;

protected:

    void logMessage(const fmi2Status& status, const std::string& message, const std::string& category = "") const;

    std::map<fmi2ValueReference, Value> values_;

    std::string instance_name_;
    std::string uuid_;
    std::string resources_directory_;
    fmi2Type type_;
    const fmi2CallbackFunctions* callback_functions_;
};