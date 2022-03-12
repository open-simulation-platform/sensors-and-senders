#pragma once

#include <string>
#include <array>

#include "Ned2Llh.hpp"
#include "common/math/MarkovNoise.hpp"
#include "UtcTime.hpp"

struct AntennaPosition {
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;
};

std::array<double, 3> calculate_offset(const AntennaPosition&, std::array<double, 3> orientation);

struct Gnss {

    using ned_state = std::array<double, 6>;
    using lat_lon_height = std::array<double, 3>;

    explicit Gnss(const AntennaPosition& antenna_position);

    void step(ned_state, double step_size);

    struct Errors {
        double rms_residual = 2.5;
        double ellipse_major = 3.5;
        double ellipse_minor = 1.5;
        double ellipse_orientation = 37.0;
        double latitude_sigma_error = 3.1;
        double longitude_sigma_error = 2.2;
        double height_sigma_error = 4.0;
    };

    double latitude  = 62.00;
    double longitude = 6.328221;
    double height = 0.0;

    Ned2LLH ned_to_llh;
    AntennaPosition antenna_position;

    MarkovNoise north_noise;
    MarkovNoise east_noise;
    MarkovNoise down_noise;  

    UtcTime utc_time;
};

double to_degrees_and_minutes(double value);