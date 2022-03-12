#pragma once

#include <string>

#include "common/Component.hpp"
#include "common/math/MarkovNoise.hpp"

class WindSensorComponent : public Component {
public:

    WindSensorComponent(const std::string& instance_name, const fmi2Type& type, const fmi2String& uuid, const std::string& resource_directory,
        const fmi2CallbackFunctions* callback_functions);

    void step(double step_size) override;

private:

    MarkovNoise m_direction_noise;
    MarkovNoise m_speed_noise;
};