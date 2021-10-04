#include "WindSensor.hpp"

WindSensor::WindSensor() 
    : _direction_noise(0.0, 0.05, 100)
    , _speed_noise(0.0, 0.05, 100)
{

}

void WindSensor::step(double wind_speed, double wind_direction, double step_size) {

    _direction_noise.step(step_size);
    _speed_noise.step(step_size);

    _speed = wind_speed + _speed_noise.value();
    _direction = wind_direction + _direction_noise.value();
}

void WindSensor::enable_sensor() {
    _sensor_ok = std::string{"A"};
}

void WindSensor::disable_sensor() {
    _sensor_ok = std::string{"V"};
}

double WindSensor::direction() const {
    return _direction;
}

double WindSensor::speed() const {
    return _speed;
}

MarkovNoise& WindSensor::direction_noise() {
    return _direction_noise;
}

MarkovNoise& WindSensor::speed_noise() {
    return _speed_noise;
}

std::string WindSensor::speed_reference() const {
    return _speed_reference;
}

std::string WindSensor::direction_reference() const {
    return _direction_reference;
}

std::string WindSensor::sensor_ok() const {
    return _sensor_ok;
}