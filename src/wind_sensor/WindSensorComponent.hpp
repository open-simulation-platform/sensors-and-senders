#pragma once

#include <string>

#include "common/Component.hpp"
#include "WindSensor.hpp"

class WindSensorComponent : public Component {
public:

    WindSensorComponent(const std::string& instance_name, const fmi2Type& type, const fmi2String& uuid, const std::string& resource_directory,
        const fmi2CallbackFunctions* callback_functions);

    void enter_initialization() override;
    void step(double step_size) override;

private:

    WindSensor _wind_sensor;
};