#include "Ned2Llh.h"
#define _USE_MATH_DEFINES 
#include <cmath>

Ned2LLH::Ned2LLH(double initial_latitude, double initial_longitude, double initial_height)
    : _initial_latitude(initial_latitude)
    , _initial_longitude(initial_longitude)
    , _initial_height(initial_height)
{
    _rn = rn();
    _rm = rm();
}

double Ned2LLH::latitude(double north_position) const {
    return rad2deg(delta_latitude(north_position))  + _initial_latitude;
}

double Ned2LLH::longitude(double east_position) const {        
    return rad2deg(delta_longitude(east_position)) + _initial_longitude;
}

double Ned2LLH::height(double height) const {
    return height + _initial_height;
}

double Ned2LLH::delta_latitude(double north_position) const {
    return north_position * std::atan2(1, _rm);
}
double Ned2LLH::delta_longitude(double east_position) const {
    return east_position *
        std::atan2(1, _rn * std::cos(deg2rad(_initial_latitude)));
}

double Ned2LLH::rn() {

    return _equatorial_radius /  
        std::sqrt( 1  - std::pow(_earth_eccentricity, 2) * std::pow(std::sin(deg2rad(_initial_latitude)), 2));
}

double Ned2LLH::rm() {

    return (1 - std::pow(_earth_eccentricity, 2)) *
    _rn /
    ( 1 - std::pow(std::sin(deg2rad(_initial_latitude)), 2) * std::pow(_earth_eccentricity, 2));  
}

double rad2deg(double rad) {
    return rad * 180 / M_PI;
}

double deg2rad(double deg) {
    return deg * M_PI / 180;
}