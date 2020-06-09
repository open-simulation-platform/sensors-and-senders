#pragma once

#include <memory>
#include "Gyro.h"
#include <common/Component.h>

class GyroComponent : public Component {
public:

    GyroComponent(const std::string& instance_name, const fmi2Type type, const fmi2String uuid, const std::string& resources_directory,
        const fmi2CallbackFunctions* callback_functions);

    ~GyroComponent() = default;

    void enter_initialization() override;
    void step(double step_size) override;

private:

    Gyro _gyro;
};