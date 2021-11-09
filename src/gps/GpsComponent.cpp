#include "GpsComponent.hpp"

GpsComponent::GpsComponent(std::string instance_name, const fmi2Type& type, const fmi2String& uuid,
    std::string resource_directory, const fmi2CallbackFunctions* callback_functions)
    : Component(std::move(instance_name), type, uuid, std::move(resource_directory), callback_functions)
{
    m_gnss = std::make_unique<Gnss>(AntennaPosition{0.0, 0.0, 0.0});   

    m_reals[21] = 0.0;
    m_reals[22] = 0.0;
    m_reals[23] = 0.0;
    m_reals[24] = 0.0;
    m_reals[25] = 0.0;
    m_reals[26] = 0.0;

    m_reals[0] = m_gnss->utc_time();
    m_reals[1] = m_gnss->latitude();
    m_strings[2] = m_gnss->latitude_direction();
    m_reals[3] = m_gnss->longitude();
    m_strings[4] = m_gnss->longitude_direction();
    m_integers[5] = m_gnss->quality();
    m_integers[6] = m_gnss->number_of_satellites();
    m_reals[7] = m_gnss->horizontal_dilution();
    m_integers[8] = m_gnss->altitude();
    m_strings[9] = m_gnss->altitude_unit();
    m_integers[10] = m_gnss->height_geo_id();
    m_strings[11] = m_gnss->height_unit();
    m_reals[12] = m_gnss->update_time();
    m_integers[13] = m_gnss->station_id();

    m_reals[14] = m_gnss->rms_residual();
    m_reals[15] = m_gnss->error_ellipse_major();
    m_reals[16] = m_gnss->error_ellipse_minor();
    m_reals[17] = m_gnss->ellipse_orientation();
    m_reals[18] = m_gnss->lat_sigma_error();
    m_reals[19] = m_gnss->long_sigma_error();
    m_reals[20] = m_gnss->height_sigma_error();

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

    m_gnss->step(ned_state, step_size);

    m_reals[0] = m_gnss->utc_time();
    m_reals[1] = m_gnss->latitude();
    m_strings[2] = m_gnss->latitude_direction();
    m_reals[3] = m_gnss->longitude();
    m_strings[4] = m_gnss->longitude_direction();
    m_integers[5] = m_gnss->quality();
    m_integers[6] = m_gnss->number_of_satellites();
    m_reals[7] = m_gnss->horizontal_dilution();
    m_integers[8] = m_gnss->altitude();
    m_strings[9] = m_gnss->altitude_unit();
    m_integers[10] = m_gnss->height_geo_id();
    m_strings[11] = m_gnss->height_unit();
    m_reals[12] = m_gnss->update_time();
    m_integers[13] = m_gnss->station_id();

    m_reals[14] = m_gnss->rms_residual();
    m_reals[15] = m_gnss->error_ellipse_major();
    m_reals[16] = m_gnss->error_ellipse_minor();
    m_reals[17] = m_gnss->ellipse_orientation();
    m_reals[18] = m_gnss->lat_sigma_error();
    m_reals[19] = m_gnss->long_sigma_error();
    m_reals[20] = m_gnss->height_sigma_error();

    const auto north_noise_mean = m_reals[27];
    if(north_noise_mean != m_gnss->north_noise().mean()) {
        m_gnss->north_noise().mean(north_noise_mean);
    }

    const auto north_noise_std = m_reals[28];
    if(north_noise_std != m_gnss->north_noise().standard_deviation()) {
        m_gnss->north_noise().standard_deviation(north_noise_std);
    }

    const auto east_noise_mean = m_reals[29];
    if(east_noise_mean != m_gnss->east_noise().mean()) {
        m_gnss->east_noise().mean(east_noise_mean);
    }

    const auto east_noise_std = m_reals[30];
    if(east_noise_std != m_gnss->east_noise().standard_deviation()) {
        m_gnss->east_noise().standard_deviation(east_noise_std);
    }

    const auto down_noise_mean = m_reals[31];
    if(down_noise_mean != m_gnss->down_noise().mean()) {
        m_gnss->down_noise().mean(down_noise_mean);
    }

    const auto down_noise_std = m_reals[32];
    if(down_noise_std != m_gnss->down_noise().standard_deviation()) {
        m_gnss->down_noise().standard_deviation(down_noise_std);
    }

    m_gnss->antenna_position().x = m_reals[33];
    m_gnss->antenna_position().y = m_reals[34];
    m_gnss->antenna_position().z = m_reals[35];
}

void GpsComponent::reset() {
    m_gnss = std::make_unique<Gnss>(AntennaPosition{0.0, 0.0, 0.0});
}

void GpsComponent::enter_initialization() {   
}

void GpsComponent::exit_initialization() {
}