#pragma once

#include <string>

#include "common/Component.hpp"
#include "common/fmi/fmi2TypesPlatform.h"
#include "common/math/MarkovNoise.hpp"


class VruComponent : public Component {
public:

    VruComponent(std::string instance_name, const fmi2Type& type, const fmi2String& uuid, std::string resources_directory,
        const fmi2CallbackFunctions* callback_functions);

    void enter_initialization() override;
    void exit_initialization() override;
    void step(double step_size) override;
    
private:

    MarkovNoise m_roll_noise;
    MarkovNoise m_pitch_noise;
    int sensor_ok = 10;
};