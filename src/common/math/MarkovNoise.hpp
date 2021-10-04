#pragma once
#include <random>

class MarkovNoise {
public:

    MarkovNoise(double mean, double std, double time_constant);
    void step(double step_size);
    double value() const;

    double mean() const;
    double standard_deviation() const;

    void mean(double mean);
    void standard_deviation(double standard_deviation);

private:

    double _time_constant;
    double _x;
    double _x_dot;

    double _mean;
    double _standard_deviation;

    std::random_device _random_device;
    std::normal_distribution<double> _normal_distribution;
};