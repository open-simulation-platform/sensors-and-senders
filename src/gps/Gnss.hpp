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

class PosRefOffset {
public:

    explicit PosRefOffset(const AntennaPosition& antenna_position);
    std::array<double, 3> get_offset(std::array<double, 3> orientation) const;

    AntennaPosition& antenna_position();

private:
    AntennaPosition m_antenna_position;
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

    explicit Gnss(const AntennaPosition& antenna_position);

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

    double m_latitude  = 62.00;
    double m_longitude = 6.328221;
    double m_height = 0.0;

    Ned2LLH ned_to_llh;
    PosRefOffset m_offset;
    Gnss::Errors m_gnss_errors;

    MarkovNoise m_north_noise;
    MarkovNoise m_east_noise;
    MarkovNoise m_down_noise;  

    Errors m_errors;

    UtcTime m_utc_time;
};

double to_degrees_and_minutes(double value);