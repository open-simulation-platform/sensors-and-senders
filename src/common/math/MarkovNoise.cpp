#include "MarkovNoise.hpp"
#include <cmath>

MarkovNoise::MarkovNoise(double mean, double std, double time_constant)
    : m_time_constant(time_constant)
    , m_x(0.0)
    , m_x_dot(0.0)
    , m_mean(mean)
    , m_standard_deviation(std)
    , m_normal_distribution(mean, std)

{}
    
void MarkovNoise::step(double step_size) {

    const auto r = m_normal_distribution(m_random_device);
    m_x_dot = (r * m_time_constant - m_x) * 1 / m_time_constant;

    m_x += m_x_dot * step_size;
}

double MarkovNoise::value() const {
    return m_x_dot;
}

void MarkovNoise::mean(double mean) {
    m_mean = mean;
    m_normal_distribution = std::normal_distribution(m_mean, m_standard_deviation);
}

void MarkovNoise::standard_deviation(double standard_deviation) {
    m_standard_deviation = standard_deviation;
    m_normal_distribution = std::normal_distribution(m_mean, m_standard_deviation);
}

double MarkovNoise::mean() const {
    return m_mean;
}

double MarkovNoise::standard_deviation() const {
    return m_standard_deviation;
}