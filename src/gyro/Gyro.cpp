#include "Gyro.hpp"
#include "common/math/Conversions.hpp"
#define _USE_MATH_DEFINES 
#include <cmath>

Gyro::Gyro()
    : noise(0.0, 0.5 * M_PI / 180, 100) 
{
}

void step(Gyro& gyro, double heading_in_radians, double step_size) {

    gyro.noise.step(step_size);
    gyro.heading = rad2deg(heading_in_radians + gyro.noise.value());
    gyro.heading = constrain_angle(gyro.heading);
}