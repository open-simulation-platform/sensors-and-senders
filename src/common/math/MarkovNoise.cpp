#include "MarkovNoise.hpp"
#include <cmath>

MarkovNoise::MarkovNoise(double mean, double std, double time_constant)
    : _time_constant(time_constant)
    , _x(0.0)
    , _x_dot(0.0)
    , _mean(mean)
    , _standard_deviation(std)
    , _normal_distribution(mean, std)

{}
    
void MarkovNoise::step(double step_size) {

    const auto r = _normal_distribution(_random_device);
    _x_dot = (r * _time_constant - _x) * 1 / _time_constant;

    _x += _x_dot * step_size;
}

double MarkovNoise::value() const {
    return _x_dot;
}

void MarkovNoise::mean(double mean) {
    _mean = mean;
    _normal_distribution = std::normal_distribution(_mean, _standard_deviation);
}

void MarkovNoise::standard_deviation(double standard_deviation) {
    _standard_deviation = standard_deviation;
    _normal_distribution = std::normal_distribution(_mean, _standard_deviation);
}

double MarkovNoise::mean() const {
    return _mean;
}

double MarkovNoise::standard_deviation() const {
    return _standard_deviation;
}