#pragma once

#include <string>

#include "common/math/MarkovNoise.hpp"

struct WindSensor {
    WindSensor();

    void step(double wind_speed, double wind_direction, double step_size);

    double direction = 0.0;
    double speed = 0.0;

    std::string direction_reference = "R";
    std::string speed_reference = "M";
    std::string sensor_ok = "A";

    MarkovNoise direction_noise;
    MarkovNoise speed_noise;

};