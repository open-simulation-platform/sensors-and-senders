#include "common/fmi/fmi2Functions.h"
#include "Component.hpp"

fmi2String fmi2GetTypesPlatform() {
    return fmi2TypesPlatform;
}

fmi2String fmi2GetVersion() {
    return fmi2Version;
}

fmi2Status fmi2SetDebugLogging(fmi2Component component, fmi2Boolean loggingOn, size_t categoriesSize,
const fmi2String categories[]) {

    (void) component;
    (void) loggingOn;
    (void) categoriesSize;
    (void) categories;

    return fmi2OK;
}

void fmi2FreeInstance(fmi2Component component) {

    if (component != nullptr) {
        auto typedComponent = static_cast<Component*>(component);
        delete typedComponent;
        typedComponent = NULL;
    }
}

fmi2Status fmi2SetupExperiment(fmi2Component component, fmi2Boolean toleranceDefined, fmi2Real tolerance,
    fmi2Real startTime, fmi2Boolean stopTimeDefined, fmi2Real stopTime) {
    
    (void) component;
    (void) toleranceDefined;
    (void) tolerance;
    (void) startTime;
    (void) stopTimeDefined;
    (void) stopTime;

    return fmi2OK;
}

fmi2Status fmi2EnterInitializationMode(fmi2Component component) {
    
    const auto typed_component = static_cast<Component*>(component);
    typed_component->enter_initialization();

    return fmi2OK;
}

fmi2Status fmi2ExitInitializationMode(fmi2Component component) {
    
    (void) component;

    return fmi2OK;
}

fmi2Status fmi2Terminate(fmi2Component component) {

    (void) component;

    return fmi2OK;
}

fmi2Status fmi2GetReal(fmi2Component component, const fmi2ValueReference references[], size_t referencesSize,
    fmi2Real values[]) {

    if (component == NULL) {
        return fmi2Error;
    }

    const auto typedComponent = static_cast<Component*>(component);

    for( decltype(referencesSize) i = 0; i < referencesSize; ++i) {
        auto value = typedComponent->real(references[i]);

        if (!value) {
            return fmi2Warning;
        }

        values[i] = value.value();
    }

    return fmi2OK;
}

fmi2Status fmi2GetInteger(fmi2Component component, const fmi2ValueReference references[], size_t referencesSize,
    fmi2Integer values[]) {

    if (component == NULL) {
        return fmi2Error;
    } 


    const auto typedComponent = static_cast<Component*>(component);

    for (decltype(referencesSize) i = 0; i < referencesSize; ++i) {

        auto value = typedComponent->integer(references[i]);
        
        if(!value) {
            return fmi2Warning;
        }

        values[i] = value.value();
    }
    return fmi2OK;
}

fmi2Status fmi2GetBoolean(fmi2Component component, const fmi2ValueReference references[], size_t referencesSize,
    fmi2Boolean values[]) {
    
    if (component == NULL) {
        return fmi2Error;
    }

    const auto typedComponent = static_cast<Component*>(component);

    for (decltype(referencesSize) i = 0; i < referencesSize; ++i) {
        auto value = typedComponent->boolean(references[i]);

        if(!value) {
            return fmi2Warning;
        }

        values[i] = static_cast<fmi2Boolean>(value.value());
    }

    return fmi2OK;
}

fmi2Status fmi2GetString(fmi2Component component, const fmi2ValueReference references[], size_t referencesSize,
    fmi2String values[]) {

    if (component == NULL) {
        return fmi2Error;
    }
    
    const auto typedComponent = static_cast<Component*>(component);

    for (decltype(referencesSize) i = 0; i < referencesSize; ++i) {
        
        auto value = typedComponent->string(references[i]);

        if(!value) {
            return fmi2Warning;
        }

        values[i] = value.value();
    }

    return fmi2OK;
}

fmi2Status fmi2SetReal(fmi2Component component, const fmi2ValueReference references[], size_t referencesSize,
    const fmi2Real values[]) {

    auto typedComponent = static_cast<Component*>(component);

    for (decltype(referencesSize) i = 0; i < referencesSize; ++i) {
        typedComponent->setReal(references[i], values[i]);
    }
    
    return fmi2OK;
}

fmi2Status fmi2SetInteger(fmi2Component component, const fmi2ValueReference references[], size_t referencesSize,
    const fmi2Integer values[]) {
    
    auto typedComponent = static_cast<Component*>(component);

    for (decltype(referencesSize) i = 0; i < referencesSize; ++i) {
        typedComponent->setInteger(references[i], values[i]);
    }

    return fmi2OK;
}

fmi2Status fmi2SetBoolean(fmi2Component component, const fmi2ValueReference references[], size_t referencesSize,
    const fmi2Boolean values[]) {
    
    auto typedComponent = static_cast<Component*>(component);

    for (decltype(referencesSize) i = 0; i < referencesSize; ++i) {
        typedComponent->setBoolean(references[i], values[i]);
    }

    return fmi2OK;
}

fmi2Status fmi2SetString(fmi2Component component, const fmi2ValueReference references[], size_t referencesSize,
    const fmi2String values[]) {

    auto typedComponent = static_cast<Component*>(component);

    for (decltype(referencesSize) i = 0; i < referencesSize; ++i) {
        typedComponent->setString(references[i], values[i]);
    }

    return fmi2OK;
}

fmi2Status fmi2SetRealInputDerivatives(fmi2Component component, const fmi2ValueReference references[],
    size_t referencesSize, const fmi2Integer order[], const fmi2Real values[]) {

    (void) component;
    (void) references;
    (void) referencesSize;
    (void) order;
    (void) values;

    return fmi2OK;
}

fmi2Status fmi2GetRealOutputDerivatives(fmi2Component component, const fmi2ValueReference references[],
    size_t referencesSize, const fmi2Integer order[], fmi2Real values[]) {
    
    (void) component;
    (void) references;
    (void) referencesSize;
    (void) order;
    (void) values;

    return fmi2OK;
}

fmi2Status fmi2DoStep(fmi2Component component, fmi2Real currentPoint, fmi2Real stepSize,
    fmi2Boolean noSetFmuStatePriorToCurrentPoint) {

    (void) currentPoint;
    (void) noSetFmuStatePriorToCurrentPoint;

    auto typedComponent = static_cast<Component*>(component);

    typedComponent->step(stepSize);
        
    return fmi2OK;
}

fmi2Status fmi2CancelStep(fmi2Component component) {
    
    (void) component;

    return fmi2OK;
}

fmi2Status fmi2Reset(fmi2Component component) {

    (void) component;

    return fmi2OK;
}

fmi2Status fmi2GetStatus(fmi2Component component, const fmi2StatusKind status,
    fmi2Status* value) {

    (void) component;
    (void) status;
    (void) value;

    return fmi2OK;
}

fmi2Status fmi2GetRealStatus(fmi2Component component, const fmi2StatusKind status,
    fmi2Real* value) {
    
    (void) component;
    (void) status;
    (void) value;

    return fmi2OK;
}

fmi2Status fmi2GetIntegerStatus(fmi2Component component, const fmi2StatusKind status,
    fmi2Integer* value) {

    (void) component;
    (void) status;
    (void) value;

    return fmi2OK;
}

fmi2Status fmi2GetBooleanStatus(fmi2Component component, const fmi2StatusKind status,
    fmi2Boolean* value) {

    (void) component;
    (void) status;
    (void) value;

    return fmi2OK;
}

fmi2Status fmi2GetStringStatus(fmi2Component component, const fmi2StatusKind status,
    fmi2String* value) {

    (void) component;
    (void) status;
    (void) value;
    
    return fmi2OK;
}