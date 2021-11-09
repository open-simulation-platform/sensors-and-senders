#include "Ned2Llh.hpp"
#include "common/math/Conversions.hpp"
#define _USE_MATH_DEFINES 
#include <cmath>

Ned2LLH::Ned2LLH(double initial_latitude, double initial_longitude, double initial_height)
    : m_initial_latitude(initial_latitude)
    , m_initial_longitude(initial_longitude)
    , m_initial_height(initial_height)
{
    m_rn = rn();
    m_rm = rm();
}

double Ned2LLH::latitude(double north_position) const {
    return rad2deg(delta_latitude(north_position))  + m_initial_latitude;
}

double Ned2LLH::longitude(double east_position) const {        
    return rad2deg(delta_longitude(east_position)) + m_initial_longitude;
}

double Ned2LLH::height(double height) const {
    return height + m_initial_height;
}

double Ned2LLH::delta_latitude(double north_position) const {
    return north_position * std::atan2(1, m_rm);
}
double Ned2LLH::delta_longitude(double east_position) const {
    return east_position *
        std::atan2(1, m_rn * std::cos(deg2rad(m_initial_latitude)));
}

double Ned2LLH::rn() const {

    return m_equatorial_radius /  
        std::sqrt( 1  - std::pow(m_earth_eccentricity, 2) * std::pow(std::sin(deg2rad(m_initial_latitude)), 2));
}

double Ned2LLH::rm() const {

    return (1 - std::pow(m_earth_eccentricity, 2)) *
    m_rn /
    ( 1 - std::pow(std::sin(deg2rad(m_initial_latitude)), 2) * std::pow(m_earth_eccentricity, 2));  
}