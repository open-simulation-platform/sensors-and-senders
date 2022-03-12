#pragma once

#include <map>
#include <string>

#include "common/fmi/fmi2TypesPlatform.h"
#include "common/fmi/fmi2FunctionTypes.h"

#ifdef _WIN32
    #define DLL_EXPORT __declspec(dllexport)
#else 
    #define DLL_EXPORT
#endif

class DLL_EXPORT Component {
public:

    Component(std::string instanceName, const fmi2Type& type, const fmi2String& uuid,  
        std::string resourcesDirectory, const fmi2CallbackFunctions* callbackFunctions);

    virtual ~Component() = default;

    Component(const Component&) = default;
    Component(Component&&) = default;

    Component& operator=(const Component&) = default;
    Component& operator=(Component&&) = default;

    fmi2Status set_real(fmi2ValueReference reference, fmi2Real value);
    fmi2Status real(fmi2ValueReference reference, fmi2Real& value) const;

    fmi2Status set_integer(fmi2ValueReference reference, fmi2Integer value);
    fmi2Status integer(fmi2ValueReference reference, fmi2Integer& value) const;

    fmi2Status set_boolean(fmi2ValueReference reference, fmi2Boolean value);
    fmi2Status boolean(fmi2ValueReference reference, fmi2Boolean& value) const;

    fmi2Status set_string(fmi2ValueReference reference, fmi2String string);
    fmi2Status string(fmi2ValueReference reference, fmi2String& str) const;

    virtual void step(double step_size) = 0;
    virtual void enter_initialization() = 0;
    virtual void exit_initialization() = 0;

    const std::string& instanceName() const;
    fmi2Type type() const;
    const std::string& uuid() const;
    const std::string& resourcesDirectory() const;

protected:

    void logMessage(const fmi2Status& status, const std::string& message, const std::string& category = "") const;

    std::map<fmi2ValueReference, double> m_reals;
    std::map<fmi2ValueReference, int> m_integers;
    std::map<fmi2ValueReference, bool> m_booleans;
    std::map<fmi2ValueReference, std::string> m_strings;

    std::string m_instance_name;
    std::string m_uuid;
    std::string m_resources_directory;
    fmi2Type m_type;
    const fmi2CallbackFunctions* m_callback_functions;
};