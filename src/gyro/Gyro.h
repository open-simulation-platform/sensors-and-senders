#pragma once 

#include <common/math/MarkovNoise.h>
#include <string>

class Gyro {
public:

    Gyro();

    void step(double heading_in_radians, double step_size);
    double heading() const;

    std::string sensor_ok() const;

    MarkovNoise& noise();

    void enable_sensor(); 
    void disable_sensor();

private:

    double _heading = 0.0;
    std::string _sensor_ok = "A";

    MarkovNoise _gyro_noise;
};