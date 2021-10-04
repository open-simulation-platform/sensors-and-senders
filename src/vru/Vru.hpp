#pragma once

#include "common/math/MarkovNoise.hpp"

class Vru {
public:

    Vru();

    void step(double roll, double pitch, double step_size);

    double roll() const;
    double pitch() const;

    int sensor_ok() const;

    MarkovNoise& pitch_noise();
    MarkovNoise& roll_noise();

    void enable_sensor();
    void disable_sensor();
    
private:

    double _roll = 0.0;
    double _pitch = 0.0;

    int _sensor_ok = 10;

    MarkovNoise _roll_noise;
    MarkovNoise _pitch_noise;
};