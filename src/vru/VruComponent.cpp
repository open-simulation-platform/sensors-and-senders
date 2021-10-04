#include "VruComponent.hpp"
#include <iostream>

VruComponent::VruComponent(std::string instance_name, const fmi2Type& type, const fmi2String& uuid,
    std::string resources_directory, const fmi2CallbackFunctions* callback_functions)
    : Component(std::move(instance_name), type, uuid, std::move(resources_directory), callback_functions)
{
    values_[0].value = _vru.sensor_ok();
    values_[1].value = _vru.pitch();
    values_[2].value = _vru.roll();

    values_[3].value = double{0.0};
    values_[4].value = double{0.0};

    values_[5].value = double{0.0};
    values_[6].value = double{0.0087};

    values_[7].value = double{0.0};
    values_[8].value = double{0.0087};

    values_[9].value = bool{false};

}

void VruComponent::step(double step_size) {

    try {

        const auto roll = std::get<1>(values_[3].value);
        const auto pitch = std::get<1>(values_[4].value); 
        _vru.step(roll, pitch, step_size);


        const auto roll_noise_mean = std::get<1>(values_[5].value);
        if(roll_noise_mean != _vru.roll_noise().mean()) {
            _vru.roll_noise().mean(roll_noise_mean);
        }

        const auto roll_noise_std = std::get<1>(values_[6].value);
        if(roll_noise_std != _vru.roll_noise().standard_deviation()){
            _vru.roll_noise().standard_deviation(roll_noise_std);
        }

        const auto pitch_noise_mean = std::get<1>(values_[7].value);
        if(pitch_noise_mean != _vru.pitch_noise().standard_deviation()) {
            _vru.pitch_noise().mean(pitch_noise_mean);
        }

        const auto pitch_noise_std = std::get<1>(values_[8].value);
        if (pitch_noise_std != _vru.pitch_noise().standard_deviation()) {
            _vru.pitch_noise().standard_deviation(pitch_noise_std);
        }

        const auto enable_sensor_fault = std::get<2>(values_[9].value);
        if(enable_sensor_fault) {
            _vru.disable_sensor();
        } else {
            _vru.enable_sensor();
        }

        values_[0].value = _vru.sensor_ok();
        values_[1].value = _vru.roll();
        values_[2].value = _vru.pitch();


    } catch (const std::bad_variant_access& err) {
        std::cerr << err.what();
    }
}

void VruComponent::enter_initialization() {

}