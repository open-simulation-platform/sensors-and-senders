#include "WindSensorComponent.hpp"

WindSensorComponent::WindSensorComponent(const std::string& instance_name, const fmi2Type& type, const fmi2String& uuid,
    const std::string& resource_directory, const fmi2CallbackFunctions* callback_functions)
    : Component(instance_name, type, uuid, resource_directory, callback_functions)
    , m_direction_noise(0.0, 0.05, 100)
    , m_speed_noise(0.0, 0.05, 100)
{

    std::string direction_reference = "R";
    std::string speed_reference = "M";
    std::string sensor_ok = "A";

    m_reals[0] = 0.0;
    m_strings[1] = direction_reference;

    m_reals[2] = 0.0;
    m_strings[3] = speed_reference;

    m_strings[4] = sensor_ok;

    m_reals[5] = 0.0;
    m_reals[6] = 0.0;

    m_reals[7] = 0.0;
    m_reals[8] = 0.0087;
    
    m_reals[9] = 0.0;
    m_reals[10] = 0.05;

    m_booleans[11] = false;
}

void WindSensorComponent::step(double step_size) {

    const auto wind_speed = m_reals[5];
    const auto wind_direction = m_reals[6];
    
    m_direction_noise.step(step_size);
    m_speed_noise.step(step_size);

    const auto direction_noise_mean = m_reals[7];
    if(direction_noise_mean != m_direction_noise.mean()) { 
        m_direction_noise.mean(direction_noise_mean);
    }

    const auto direction_noise_std = m_reals[8];
    if(direction_noise_std != m_direction_noise.standard_deviation()) {
        m_direction_noise.standard_deviation(direction_noise_std);
    }

    const auto speed_noise_mean = m_reals[9];
    if(speed_noise_mean != m_speed_noise.mean()){
        m_speed_noise.mean(speed_noise_mean);
    }

    const auto speed_noise_std = m_reals[10];
    if(speed_noise_std != m_speed_noise.standard_deviation()){
        m_speed_noise.standard_deviation(speed_noise_std);
    }

    const auto enable_sensor_fault = m_booleans[11];

    m_reals[0] = wind_direction + m_direction_noise.value();
    m_reals[2] = wind_speed + m_speed_noise.value();
    m_strings[4] = enable_sensor_fault ? "V" : "A";
}