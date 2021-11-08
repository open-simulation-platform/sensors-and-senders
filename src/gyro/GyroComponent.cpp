#include "GyroComponent.hpp"

GyroComponent::GyroComponent(const std::string& instance_name, const fmi2Type& type, const fmi2String& uuid,
    const std::string& resources_directory, const fmi2CallbackFunctions* callback_functions)
    : Component(instance_name, type, uuid, resources_directory, callback_functions)
{
    m_reals[0] = _gyro.heading();
    m_strings[1] = _gyro.sensor_ok();

    m_reals[2] = 0.0;

    m_reals[3] = 0.0;
    m_reals[4] = 0.0087;
    m_booleans[5] = false;
}

void GyroComponent::step(double step_size) {

    const auto noise_mean = m_reals[3];
    if(noise_mean != _gyro.noise().mean()) {
        _gyro.noise().mean(noise_mean);
    }

    const auto noise_std = m_reals[4];
    if(noise_std != _gyro.noise().standard_deviation()) {
        _gyro.noise().standard_deviation(noise_std);
    }

    const auto sensor_error = m_booleans[5];
    if(sensor_error) {
        _gyro.disable_sensor();
    } else {
        _gyro.enable_sensor();
    }

    const auto heading = m_reals[2];
    _gyro.step(heading, step_size);

    m_reals[0] = _gyro.heading();
    m_strings[1] = _gyro.sensor_ok();
}

void GyroComponent::enter_initialization() {
}

void GyroComponent::exit_initialization() {
}