#pragma once
#include <string>
#include <array>
#include "Ned2Llh.h"
#include <common/math/MarkovNoise.h>
#include "UtcTime.h"

struct AntennaPosition {
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;
};

class PosRefOffset {
public:

    PosRefOffset(const AntennaPosition& antenna_position);
    std::array<double, 3> get_offset(std::array<double, 3> orientation);

    AntennaPosition& antenna_position();

private:
    AntennaPosition _antenna_position;
};



struct GnssParameters {
    AntennaPosition antenna_position;

};

struct NedPosition {
    double north;
    double east;
    double down;
    double roll;
    double pitch;
    double yaw;
};



class Gnss {
public:

    using ned_state = std::array<double, 6>;
    using lat_lon_height = std::array<double, 3>;

    Gnss(const AntennaPosition& antenna_position);

    void step(ned_state, double step_size);

    double utc_time();

    double latitude() const;
    double longitude() const;
    double height() const;

    std::string latitude_direction() const;
    std::string longitude_direction() const;
    std::string altitude_unit() const;
    std::string height_unit() const;
    int quality() const;
    int number_of_satellites() const;
    double horizontal_dilution() const;
    int altitude() const;
    int height_geo_id() const;
    double update_time() const;
    int station_id() const;

    double rms_residual() const;
    double error_ellipse_major() const;
    double error_ellipse_minor() const;
    double ellipse_orientation() const;
    double lat_sigma_error() const;
    double long_sigma_error() const;
    double height_sigma_error() const;

    MarkovNoise& north_noise();
    MarkovNoise& east_noise();
    MarkovNoise& down_noise();

    PosRefOffset& posref_offset(); 

    struct Errors {
        double rms_residual = 2.5;
        double ellipse_major = 3.5;
        double ellipse_minor = 1.5;
        double ellipse_orientation = 37.0;
        double latitude_sigma_error = 3.1;
        double longitude_sigma_error = 2.2;
        double height_sigma_error = 4.0;
    };


private:

    double _latitude  = 62.00;
    double _longitude = 6.328221;
    double _height = 0.0;

    Ned2LLH ned_to_llh;
    PosRefOffset _offset;
    Gnss::Errors gnss_errors;

    MarkovNoise _north_noise;
    MarkovNoise _east_noise;
    MarkovNoise _down_noise;  

    Errors _errors;

    UtcTime _utc_time;
};

double to_degrees_and_minutes(double value);