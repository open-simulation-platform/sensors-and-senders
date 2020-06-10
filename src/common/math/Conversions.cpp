#include "common/math/Conversions.h"
#define _USE_MATH_DEFINES 
#include <cmath>

double constrain_angle(double angle_in_degrees) {

    constexpr auto degrees_in_circle = 360;
    angle_in_degrees = std::fmod(angle_in_degrees, degrees_in_circle);
    if(angle_in_degrees < 0) {
        angle_in_degrees += 360;
    }

    return angle_in_degrees;
}

double rad2deg(double rad) {
    return rad * 180 / M_PI;
}

double deg2rad(double deg) {
    return deg * M_PI / 180;
}