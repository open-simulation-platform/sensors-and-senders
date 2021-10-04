#pragma once

#include <string>

#include "common/math/MarkovNoise.hpp"

class WindSensor {
public:
    WindSensor();

    void step(double wind_speed, double wind_direction, double step_size);

    double direction() const;
    double speed() const;
    std::string direction_reference() const;
    std::string speed_reference() const;
    std::string sensor_ok() const;

    void enable_sensor();
    void disable_sensor();

    MarkovNoise& direction_noise();
    MarkovNoise& speed_noise();

private:

    double _direction = 0.0;
    double _speed = 0.0;

    std::string _direction_reference = "R";
    std::string _speed_reference = "M";
    std::string _sensor_ok = "A";

    MarkovNoise _direction_noise;
    MarkovNoise _speed_noise;

};