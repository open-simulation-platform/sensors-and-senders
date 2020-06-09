#include "Gyro.h"
#include <common/math/Conversions.h>
#define _USE_MATH_DEFINES 
#include <cmath>

Gyro::Gyro()
    : _gyro_noise(0.0, 0.5 * M_PI / 180, 100) 
{
}

void Gyro::step(double heading_in_radians, double step_size) {

    _gyro_noise.step(step_size);
    _heading = rad2deg(heading_in_radians + _gyro_noise.value());
    _heading = constrain_angle(_heading);
}

double Gyro::heading() const {
    return _heading;
}

std::string Gyro::sensor_ok() const {
    return _sensor_ok;
}

MarkovNoise& Gyro::noise() {
    return _gyro_noise;
}

void Gyro::disable_sensor() {
    _sensor_ok = "V";
}

void Gyro::enable_sensor() {
    _sensor_ok = "A";
}