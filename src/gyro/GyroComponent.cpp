#include "GyroComponent.hpp"
#include <iostream>

GyroComponent::GyroComponent(const std::string& instance_name, const fmi2Type type, const fmi2String uuid,
    const std::string& resources_directory, const fmi2CallbackFunctions* callback_functions)
    : Component(instance_name, type, uuid, resources_directory, callback_functions)
{
    values_[0].value = _gyro.heading();
    values_[1].value = _gyro.sensor_ok();

    values_[2].value = double{0.0};

    values_[3].value = double{0.0};
    values_[4].value = double{0.0087};
    values_[5].value = bool{false};
}

void GyroComponent::step(double step_size) {

    try {
        const auto noise_mean = std::get<1>(values_[3].value);
        if(noise_mean != _gyro.noise().mean()) {
            _gyro.noise().mean(noise_mean);
        }

        const auto noise_std = std::get<1>(values_[4].value);
        if(noise_std != _gyro.noise().standard_deviation()) {
            _gyro.noise().standard_deviation(noise_std);
        }

        const auto sensor_error = std::get<2>(values_[5].value);
        if(sensor_error) {
            _gyro.disable_sensor();
        } else {
            _gyro.enable_sensor();
        }

        const auto heading = std::get<1>(values_[2].value);
        _gyro.step(heading, step_size);

        values_[0].value = _gyro.heading();
        values_[1].value = _gyro.sensor_ok();


    } catch (const std::bad_variant_access& err) {
        std::cerr << err.what();
    }
}

void GyroComponent::enter_initialization() {
    
}