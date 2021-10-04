#include <common/fmi/fmi2Functions.h>
#include "WindSensorComponent.hpp"

fmi2Component fmi2Instantiate(fmi2String instanceName, fmi2Type type, fmi2String uuid, fmi2String resourcesUri,
    const fmi2CallbackFunctions* callbackFunctions, fmi2Boolean visible, fmi2Boolean loggingOn) {

    (void) loggingOn;
    (void) visible;

    if (type != fmi2CoSimulation) {
        return NULL;
    }

    return new WindSensorComponent(instanceName, type, uuid, resourcesUri, callbackFunctions);
}