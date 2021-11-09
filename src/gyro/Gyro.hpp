#pragma once 

#include "common/math/MarkovNoise.hpp"

struct Gyro {
    Gyro();
    double heading = 0.0;
    char sensor_ok = 'A';
    MarkovNoise noise;
};

void step(Gyro& gyro, double heading_in_radians, double step_size);