#pragma once

#include "Gyro.hpp"
#include "common/Component.hpp"

class GyroComponent : public Component {
public:

    GyroComponent(const std::string& instance_name, const fmi2Type& type, const fmi2String& uuid, const std::string& resources_directory,
        const fmi2CallbackFunctions* callback_functions);

    void enter_initialization() override;
    void exit_initialization() override;
    void step(double step_size) override;

private:

    Gyro m_gyro;
};