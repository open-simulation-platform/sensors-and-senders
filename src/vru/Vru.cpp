#include "Vru.hpp"

Vru::Vru()
    : _roll_noise(0.0, 0.0087, 100)
    , _pitch_noise(0.0, 0.0087, 100) 
{

}

void Vru::step(double roll, double pitch, double step_size) {

    _roll_noise.step(step_size);
    _pitch_noise.step(step_size);

    _roll = roll + _roll_noise.value();
    _pitch = pitch + _pitch_noise.value();
}

double Vru::roll() const {
    return _roll;
}

double Vru::pitch() const {
    return _pitch;
}

int Vru::sensor_ok() const {
    return _sensor_ok;
}

void Vru::disable_sensor() {
    _sensor_ok = 11;
}

void Vru::enable_sensor() {
    _sensor_ok = 10;
}

MarkovNoise& Vru::roll_noise() {
    return _roll_noise;
}

MarkovNoise& Vru::pitch_noise() {
    return _pitch_noise;
}