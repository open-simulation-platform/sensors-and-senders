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

    double m_time_constant;
    double m_x;
    double m_x_dot;

    double m_mean;
    double m_standard_deviation;

    std::random_device m_random_device;
    std::normal_distribution<double> m_normal_distribution;
};