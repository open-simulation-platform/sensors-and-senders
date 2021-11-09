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

    double m_direction = 0.0;
    double m_speed = 0.0;

    std::string m_direction_reference = "R";
    std::string m_speed_reference = "M";
    std::string m_sensor_ok = "A";

    MarkovNoise m_direction_noise;
    MarkovNoise m_speed_noise;

};