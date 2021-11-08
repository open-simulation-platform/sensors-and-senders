#include "GpsComponent.hpp"

GpsComponent::GpsComponent(std::string instance_name, const fmi2Type& type, const fmi2String& uuid,
    std::string resource_directory, const fmi2CallbackFunctions* callback_functions)
    : Component(std::move(instance_name), type, uuid, std::move(resource_directory), callback_functions)
{
    _gnss = std::make_unique<Gnss>(AntennaPosition{0.0, 0.0, 0.0});   

    m_reals[21] = 0.0;
    m_reals[22] = 0.0;
    m_reals[23] = 0.0;
    m_reals[24] = 0.0;
    m_reals[25] = 0.0;
    m_reals[26] = 0.0;

    m_reals[0] = _gnss->utc_time();
    m_reals[1] = _gnss->latitude();
    m_strings[2] = _gnss->latitude_direction();
    m_reals[3] = _gnss->longitude();
    m_strings[4] = _gnss->longitude_direction();
    m_integers[5] = _gnss->quality();
    m_integers[6] = _gnss->number_of_satellites();
    m_reals[7] = _gnss->horizontal_dilution();
    m_integers[8] = _gnss->altitude();
    m_strings[9] = _gnss->altitude_unit();
    m_integers[10] = _gnss->height_geo_id();
    m_strings[11] = _gnss->height_unit();
    m_reals[12] = _gnss->update_time();
    m_integers[13] = _gnss->station_id();

    m_reals[14] = _gnss->rms_residual();
    m_reals[15] = _gnss->error_ellipse_major();
    m_reals[16] = _gnss->error_ellipse_minor();
    m_reals[17] = _gnss->ellipse_orientation();
    m_reals[18] = _gnss->lat_sigma_error();
    m_reals[19] = _gnss->long_sigma_error();
    m_reals[20] = _gnss->height_sigma_error();

    m_reals[27] = 0.0;
    m_reals[28] = 0.0;
    m_reals[29] = 0.0;
    m_reals[30] = 0.0;
    m_reals[31] = 0.0;
    m_reals[32] = 0.0;

    m_reals[33] = 0.0;
    m_reals[34] = 0.0;
    m_reals[35] = 0.0;
}

void GpsComponent::step(double step_size) {

    Gnss::ned_state ned_state;

    ned_state[0] = m_reals[21];
    ned_state[1] = m_reals[22];
    ned_state[2] = m_reals[23];
    ned_state[3] = m_reals[24];
    ned_state[4] = m_reals[25];
    ned_state[5] = m_reals[26];

    _gnss->step(ned_state, step_size);

    m_reals[0] = _gnss->utc_time();
    m_reals[1] = _gnss->latitude();
    m_strings[2] = _gnss->latitude_direction();
    m_reals[3] = _gnss->longitude();
    m_strings[4] = _gnss->longitude_direction();
    m_integers[5] = _gnss->quality();
    m_integers[6] = _gnss->number_of_satellites();
    m_reals[7] = _gnss->horizontal_dilution();
    m_integers[8] = _gnss->altitude();
    m_strings[9] = _gnss->altitude_unit();
    m_integers[10] = _gnss->height_geo_id();
    m_strings[11] = _gnss->height_unit();
    m_reals[12] = _gnss->update_time();
    m_integers[13] = _gnss->station_id();

    m_reals[14] = _gnss->rms_residual();
    m_reals[15] = _gnss->error_ellipse_major();
    m_reals[16] = _gnss->error_ellipse_minor();
    m_reals[17] = _gnss->ellipse_orientation();
    m_reals[18] = _gnss->lat_sigma_error();
    m_reals[19] = _gnss->long_sigma_error();
    m_reals[20] = _gnss->height_sigma_error();

    const auto north_noise_mean = m_reals[27];
    if(north_noise_mean != _gnss->north_noise().mean()) {
        _gnss->north_noise().mean(north_noise_mean);
    }

    const auto north_noise_std = m_reals[28];
    if(north_noise_std != _gnss->north_noise().standard_deviation()) {
        _gnss->north_noise().standard_deviation(north_noise_std);
    }

    const auto east_noise_mean = m_reals[29];
    if(east_noise_mean != _gnss->east_noise().mean()) {
        _gnss->east_noise().mean(east_noise_mean);
    }

    const auto east_noise_std = m_reals[30];
    if(east_noise_std != _gnss->east_noise().standard_deviation()) {
        _gnss->east_noise().standard_deviation(east_noise_std);
    }

    const auto down_noise_mean = m_reals[31];
    if(down_noise_mean != _gnss->down_noise().mean()) {
        _gnss->down_noise().mean(down_noise_mean);
    }

    const auto down_noise_std = m_reals[32];
    if(down_noise_std != _gnss->down_noise().standard_deviation()) {
        _gnss->down_noise().standard_deviation(down_noise_std);
    }

    const auto antenna_x_pos = m_reals[33];
    if(antenna_x_pos != _gnss->posref_offset().antenna_position().x) {
        _gnss->posref_offset().antenna_position().x = antenna_x_pos;
    }

    const auto antenna_y_pos = m_reals[35];
    if(antenna_y_pos != _gnss->posref_offset().antenna_position().y) {
        _gnss->posref_offset().antenna_position().y = antenna_y_pos;
    }
    const auto antenna_z_pos = m_reals[35];
    if(antenna_z_pos != _gnss->posref_offset().antenna_position().z) {
        _gnss->posref_offset().antenna_position().z = antenna_z_pos;
    }
}

void GpsComponent::reset() {
    _gnss = std::make_unique<Gnss>(AntennaPosition{0.0, 0.0, 0.0});
}

void GpsComponent::enter_initialization() {   
}

void GpsComponent::exit_initialization() {
}