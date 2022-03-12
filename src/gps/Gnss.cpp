#include <cmath>

#include "Gnss.hpp"

std::array<double, 3> calculate_offset(const AntennaPosition& antenna_position, std::array<double, 3> orientation) {
    
    std::array<double, 3> gps_offset {0, 0, 0};

    const auto cRoll = std::cos(orientation[0]);
    const auto sRoll = std::sin(orientation[0]);

    const auto cPitch = std::cos(orientation[1]);
    const auto sPitch = std::sin(orientation[1]);

    const auto cYaw = std::cos(orientation[2]);
    const auto sYaw = std::sin(orientation[2]);

    gps_offset[0] = antenna_position.x * cYaw * cPitch +
                    antenna_position.y * (cYaw * sPitch * sRoll - sYaw * cRoll) +
                    antenna_position.z * (cRoll * sPitch * cYaw + sYaw * sRoll);
    
    gps_offset[1] = antenna_position.x * sYaw * cPitch +
                    antenna_position.y * (sYaw * sPitch * sRoll + cYaw * cRoll) +
                    antenna_position.z * (sYaw * sPitch * cRoll - cYaw * sRoll);
    
    gps_offset[2] = antenna_position.x * -sPitch +
                    antenna_position.y * cPitch * sRoll + 
                    antenna_position.z * cPitch * cRoll;

    return gps_offset; 
}

Gnss::Gnss(const AntennaPosition& antenna)
    : antenna_position(antenna)
    , north_noise(0.0, 0.5, 100.0)
    , east_noise(0.0, 0.5, 100.0)
    , down_noise(0.0, 0.8, 100.0) 
{}

void Gnss::step(ned_state state, double step_size) {

    std::array<double, 3> position {state[0], state[1], state[2]};

    const auto offset = calculate_offset(antenna_position, {state[3], state[4], state[5]});
    position[0] += offset[0];
    position[1] += offset[1];
    position[2] += offset[2];

    north_noise.step(step_size);
    east_noise.step(step_size);
    down_noise.step(step_size);

    position[0] += north_noise.value();
    position[1] += east_noise.value();
    position[2] += down_noise.value();

    latitude = ned_to_llh.latitude(position[0]);
    longitude = ned_to_llh.longitude(position[1]);
    height = ned_to_llh.height(position[2]);

    latitude = to_degrees_and_minutes(latitude);
    longitude = to_degrees_and_minutes(longitude);
}

double to_degrees_and_minutes(double value) {

    const auto degrees = std::floor(value);
    const auto minutes = (value - degrees) * 60;
    return degrees * 100 + minutes; 
}