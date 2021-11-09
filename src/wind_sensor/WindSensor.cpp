#include "WindSensor.hpp"

WindSensor::WindSensor() 
    : m_direction_noise(0.0, 0.05, 100)
    , m_speed_noise(0.0, 0.05, 100)
{}

void WindSensor::step(double wind_speed, double wind_direction, double step_size) {

    m_direction_noise.step(step_size);
    m_speed_noise.step(step_size);

    m_speed = wind_speed + m_speed_noise.value();
    m_direction = wind_direction + m_direction_noise.value();
}

void WindSensor::enable_sensor() {
    m_sensor_ok = std::string{"A"};
}

void WindSensor::disable_sensor() {
    m_sensor_ok = std::string{"V"};
}

double WindSensor::direction() const {
    return m_direction;
}

double WindSensor::speed() const {
    return m_speed;
}

MarkovNoise& WindSensor::direction_noise() {
    return m_direction_noise;
}

MarkovNoise& WindSensor::speed_noise() {
    return m_speed_noise;
}

std::string WindSensor::speed_reference() const {
    return m_speed_reference;
}

std::string WindSensor::direction_reference() const {
    return m_direction_reference;
}

std::string WindSensor::sensor_ok() const {
    return m_sensor_ok;
}