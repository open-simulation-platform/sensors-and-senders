#include "GyroComponent.hpp"
#include "common/math/Conversions.hpp"


GyroComponent::GyroComponent(const std::string& instance_name, const fmi2Type& type, const fmi2String& uuid,
    const std::string& resources_directory, const fmi2CallbackFunctions* callback_functions)
    : Component(instance_name, type, uuid, resources_directory, callback_functions)
    , m_noise(0.0, 0.0087, 100.0)
{
    m_reals[0] = 0.0;
    m_strings[1] = "A";

    m_reals[2] = 0.0;

    m_reals[3] = 0.0;
    m_reals[4] = 0.0087;
    m_booleans[5] = false;
}

void GyroComponent::step(double step_size) {

    const auto noise_mean = m_reals[3];
    if(noise_mean != m_noise.mean()) {
        m_noise.mean(noise_mean);
    }

    const auto noise_std = m_reals[4];
    if(noise_std != m_noise.standard_deviation()) {
        m_noise.standard_deviation(noise_std);
    }

    const auto sensor_error = m_booleans[5];
    m_sensor_ok = sensor_error ? 'V' : 'A';

    auto heading = m_reals[2];
    m_noise.step(step_size);

    heading = rad2deg(heading + m_noise.value());
    heading = constrain_angle(heading);

    m_reals[0] = heading;
    m_strings[1] = m_sensor_ok;
}

void GyroComponent::enter_initialization() {}
void GyroComponent::exit_initialization() {}