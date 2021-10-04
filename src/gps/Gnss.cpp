#include <cmath>

#include "Gnss.hpp"

PosRefOffset::PosRefOffset(const AntennaPosition& antenna_position) 
    : _antenna_position(antenna_position)
{

}

std::array<double, 3> PosRefOffset::get_offset(std::array<double, 3> orientation) {
    
    std::array<double, 3> gps_offset {0, 0, 0};

    const auto cRoll = std::cos(orientation[0]);
    const auto sRoll = std::sin(orientation[0]);

    const auto cPitch = std::cos(orientation[1]);
    const auto sPitch = std::sin(orientation[1]);

    const auto cYaw = std::cos(orientation[2]);
    const auto sYaw = std::sin(orientation[2]);

    gps_offset[0] = _antenna_position.x * cYaw * cPitch +
                    _antenna_position.y * (cYaw * sPitch * sRoll - sYaw * cRoll) +
                    _antenna_position.z * (cRoll * sPitch * cYaw + sYaw * sRoll);
    
    gps_offset[1] = _antenna_position.x * sYaw * cPitch +
                    _antenna_position.y * (sYaw * sPitch * sRoll + cYaw * cRoll) +
                    _antenna_position.z * (sYaw * sPitch * cRoll - cYaw * sRoll);
    
    gps_offset[2] = _antenna_position.x * -sPitch +
                    _antenna_position.y * cPitch * sRoll + 
                    _antenna_position.z * cPitch * cRoll;

    return gps_offset; 
}

AntennaPosition& PosRefOffset::antenna_position() {
    return _antenna_position;
}

Gnss::Gnss(const AntennaPosition& antenna_position)
    : _offset(antenna_position)
    , _north_noise(0.0, 0.5, 100.0)
    , _east_noise(0.0, 0.5, 100.0)
    , _down_noise(0.0, 0.8, 100.0) {

}


void Gnss::step(ned_state ned_state, double step_size) {

    std::array<double, 3> position {ned_state[0], ned_state[1], ned_state[2]};

    const auto offset = _offset.get_offset( {ned_state[3], ned_state[4], ned_state[5]});
    position[0] += offset[0];
    position[1] += offset[1];
    position[2] += offset[2];

    _north_noise.step(step_size);
    _east_noise.step(step_size);
    _down_noise.step(step_size);

    position[0] += _north_noise.value();
    position[1] += _east_noise.value();
    position[2] += _down_noise.value();

    _latitude = ned_to_llh.latitude(position[0]);
    _longitude = ned_to_llh.longitude(position[1]);
    _height = ned_to_llh.height(position[2]);

    _latitude = to_degrees_and_minutes(_latitude);
    _longitude = to_degrees_and_minutes(_longitude);
}

double to_degrees_and_minutes(double value) {

    const auto degrees = std::floor(value);
    const auto minutes = (value - degrees) * 60;
    return degrees * 100 + minutes; 
}

double Gnss::utc_time() {
    return _utc_time.time();
}

double Gnss::latitude() const {
    return _latitude;
}

double Gnss::longitude() const {
    return _longitude;
}

double Gnss::height() const {
    return _height;
}

std::string Gnss::latitude_direction() const {
    return {"N"};
}

std::string Gnss::longitude_direction() const {
    return {"E"};
}

std::string Gnss::altitude_unit() const {
    return {"M"};
}

std::string Gnss::height_unit() const {
    return {"M"};
}

int Gnss::quality() const {
    return 2;
}

int Gnss::number_of_satellites() const {
    return 8;
}

double Gnss::horizontal_dilution() const {
    return 0.0;
}

int Gnss::altitude() const {
    return 0;
}

int Gnss::height_geo_id() const {
    return 0;
}

double Gnss::update_time() const {
    return 0.0;
}

int Gnss::station_id() const {
    return 1;
}

double Gnss::rms_residual() const {
    return _errors.rms_residual;
}

double Gnss::error_ellipse_major() const {
    return _errors.ellipse_major;
}

double Gnss::error_ellipse_minor() const {
    return _errors.ellipse_minor;
}

double Gnss::ellipse_orientation() const {
    return _errors.ellipse_orientation;
}

double Gnss::lat_sigma_error() const {
    return _errors.latitude_sigma_error;
}

double Gnss::long_sigma_error() const {
    return _errors.longitude_sigma_error;
}

double Gnss::height_sigma_error() const {
    return _errors.height_sigma_error;
}

MarkovNoise& Gnss::north_noise() {
    return _north_noise;
}

MarkovNoise& Gnss::east_noise() {
    return _east_noise;
}

MarkovNoise& Gnss::down_noise() {
    return _down_noise;
}

PosRefOffset& Gnss::posref_offset() {
    return _offset;
}