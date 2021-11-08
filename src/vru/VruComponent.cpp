#include "VruComponent.hpp"

VruComponent::VruComponent(std::string instance_name, const fmi2Type& type, const fmi2String& uuid,
    std::string resources_directory, const fmi2CallbackFunctions* callback_functions)
    : Component(std::move(instance_name), type, uuid, std::move(resources_directory), callback_functions)
{
    m_integers[0] = _vru.sensor_ok();
    m_reals[1] = _vru.pitch();
    m_reals[2] = _vru.roll();

    m_reals[3] = 0.0;
    m_reals[4] = 0.0;

    m_reals[5] = 0.0;
    m_reals[6] = 0.0087;

    m_reals[7] = 0.0;
    m_reals[8] = 0.0087;

    m_booleans[9] = false;
}

void VruComponent::step(double step_size) {

    const auto roll = m_reals[3];
    const auto pitch = m_reals[4]; 
    _vru.step(roll, pitch, step_size);


    const auto roll_noise_mean = m_reals[5];
    if(roll_noise_mean != _vru.roll_noise().mean()) {
        _vru.roll_noise().mean(roll_noise_mean);
    }

    const auto roll_noise_std = m_reals[6];
    if(roll_noise_std != _vru.roll_noise().standard_deviation()){
        _vru.roll_noise().standard_deviation(roll_noise_std);
    }

    const auto pitch_noise_mean = m_reals[7];
    if(pitch_noise_mean != _vru.pitch_noise().standard_deviation()) {
        _vru.pitch_noise().mean(pitch_noise_mean);
    }

    const auto pitch_noise_std = m_reals[8];
    if (pitch_noise_std != _vru.pitch_noise().standard_deviation()) {
        _vru.pitch_noise().standard_deviation(pitch_noise_std);
    }

    const auto enable_sensor_fault = m_booleans[9];
    if(enable_sensor_fault) {
        _vru.disable_sensor();
    } else {
        _vru.enable_sensor();
    }

    m_integers[0] = _vru.sensor_ok();
    m_reals[1] = _vru.roll();
    m_reals[2] = _vru.pitch();
}

void VruComponent::enter_initialization() {
}

void VruComponent::exit_initialization() {
}