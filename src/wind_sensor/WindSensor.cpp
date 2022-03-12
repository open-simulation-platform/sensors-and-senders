#include "WindSensor.hpp"

WindSensor::WindSensor() 
    : direction_noise(0.0, 0.05, 100)
    , speed_noise(0.0, 0.05, 100)
{}

void WindSensor::step(double wind_speed, double wind_direction, double step_size) {

    direction_noise.step(step_size);
    speed_noise.step(step_size);

    speed = wind_speed + speed_noise.value();
    direction = wind_direction + direction_noise.value();
}