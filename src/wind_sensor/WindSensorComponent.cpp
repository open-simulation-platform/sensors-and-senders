#include "WindSensorComponent.hpp"
#include <iostream>

WindSensorComponent::WindSensorComponent(const std::string& instance_name, const fmi2Type& type, const fmi2String& uuid,
    const std::string& resource_directory, const fmi2CallbackFunctions* callback_functions)
    : Component(instance_name, type, uuid, resource_directory, callback_functions)
{

    values_[0].value = _wind_sensor.direction();
    values_[1].value = _wind_sensor.direction_reference();

    values_[2].value = _wind_sensor.speed();
    values_[3].value = _wind_sensor.speed_reference();

    values_[4].value = _wind_sensor.sensor_ok();

    values_[5].value = double{0.0};
    values_[6].value = double{0.0};

    values_[7].value = double{0.0};
    values_[8].value = double{0.0087};

    
    values_[9].value = double{0.0};
    values_[10].value = double{0.05};

    values_[11].value = bool{false};
}

void WindSensorComponent::step(double step_size) {

    try {

        const auto wind_speed = std::get<1>(values_[5].value);
        const auto wind_direction = std::get<1>(values_[6].value);
        _wind_sensor.step(wind_speed, wind_direction, step_size);

        const auto direction_noise_mean = std::get<1>(values_[7].value);
        if(direction_noise_mean != _wind_sensor.direction_noise().mean()) { 
            _wind_sensor.direction_noise().mean(direction_noise_mean);
        }

        const auto direction_noise_std = std::get<1>(values_[8].value);
        if(direction_noise_std != _wind_sensor.direction_noise().standard_deviation()) {
            _wind_sensor.direction_noise().standard_deviation(direction_noise_std);
        }

        const auto speed_noise_mean = std::get<1>(values_[9].value);
        if(speed_noise_mean != _wind_sensor.speed_noise().mean()){
            _wind_sensor.speed_noise().mean(speed_noise_mean);
        }

        const auto speed_noise_std = std::get<1>(values_[10].value);
        if(speed_noise_std != _wind_sensor.speed_noise().standard_deviation()){
            _wind_sensor.speed_noise().standard_deviation(speed_noise_std);
        }

        const auto enable_sensor_fault = std::get<2>(values_[11].value);
        if(enable_sensor_fault) {
            _wind_sensor.disable_sensor();
        } else {
            _wind_sensor.enable_sensor();
        }

        values_[0].value = _wind_sensor.direction();
        values_[1].value = _wind_sensor.direction_reference();
        values_[2].value = _wind_sensor.speed();
        values_[3].value = _wind_sensor.speed_reference();
        values_[4].value = _wind_sensor.sensor_ok();

    } catch (const std::bad_variant_access& err) {
        std::cerr << err.what();
    }
}

void WindSensorComponent::enter_initialization() {
    
}