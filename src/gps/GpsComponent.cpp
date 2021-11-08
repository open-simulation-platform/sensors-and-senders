#include "GpsComponent.hpp"
#include <iostream>

GpsComponent::GpsComponent(std::string instance_name, const fmi2Type& type, const fmi2String& uuid,
    std::string resource_directory, const fmi2CallbackFunctions* callback_functions)
    : Component(std::move(instance_name), type, uuid, std::move(resource_directory), callback_functions)
{
    _gnss = std::make_unique<Gnss>(AntennaPosition{0.0, 0.0, 0.0});   

    values_[21].value = double{0.0};
    values_[22].value = double{0.0};
    values_[23].value = double{0.0};
    values_[24].value = double{0.0};
    values_[25].value = double{0.0};
    values_[26].value = double{0.0};

    values_[0].value = _gnss->utc_time();
    values_[1].value = _gnss->latitude();
    values_[2].value = _gnss->latitude_direction();
    values_[3].value = _gnss->longitude();
    values_[4].value = _gnss->longitude_direction();
    values_[5].value = _gnss->quality();
    values_[6].value = _gnss->number_of_satellites();
    values_[7].value = _gnss->horizontal_dilution();
    values_[8].value = _gnss->altitude();
    values_[9].value = _gnss->altitude_unit();
    values_[10].value = _gnss->height_geo_id();
    values_[11].value = _gnss->height_unit();
    values_[12].value = _gnss->update_time();
    values_[13].value = _gnss->station_id();

    values_[14].value = _gnss->rms_residual();
    values_[15].value = _gnss->error_ellipse_major();
    values_[16].value = _gnss->error_ellipse_minor();
    values_[17].value = _gnss->ellipse_orientation();
    values_[18].value = _gnss->lat_sigma_error();
    values_[19].value = _gnss->long_sigma_error();
    values_[20].value = _gnss->height_sigma_error();

    values_[27].value = double{0.0};
    values_[28].value = double{0.0};
    values_[29].value = double{0.0};
    values_[30].value = double{0.0};
    values_[31].value = double{0.0};
    values_[32].value = double{0.0};

    values_[33].value = double{0.0};
    values_[34].value = double{0.0};
    values_[35].value = double{0.0};
}

void GpsComponent::step(double step_size) {

    Gnss::ned_state ned_state;

    try {
        ned_state[0] = std::get<1>(values_[21].value);
        ned_state[1] = std::get<1>(values_[22].value);
        ned_state[2] = std::get<1>(values_[23].value);
        ned_state[3] = std::get<1>(values_[24].value);
        ned_state[4] = std::get<1>(values_[25].value);
        ned_state[5] = std::get<1>(values_[26].value);

        _gnss->step(ned_state, step_size);

        values_[0].value = _gnss->utc_time();
        values_[1].value = _gnss->latitude();
        values_[2].value = _gnss->latitude_direction();
        values_[3].value = _gnss->longitude();
        values_[4].value = _gnss->longitude_direction();
        values_[5].value = _gnss->quality();
        values_[6].value = _gnss->number_of_satellites();
        values_[7].value = _gnss->horizontal_dilution();
        values_[8].value = _gnss->altitude();
        values_[9].value = _gnss->altitude_unit();
        values_[10].value = _gnss->height_geo_id();
        values_[11].value = _gnss->height_unit();
        values_[12].value = _gnss->update_time();
        values_[13].value = _gnss->station_id();

        values_[14].value = _gnss->rms_residual();
        values_[15].value = _gnss->error_ellipse_major();
        values_[16].value = _gnss->error_ellipse_minor();
        values_[17].value = _gnss->ellipse_orientation();
        values_[18].value = _gnss->lat_sigma_error();
        values_[19].value = _gnss->long_sigma_error();
        values_[20].value = _gnss->height_sigma_error();

        const auto north_noise_mean = std::get<1>(values_[27].value);
        if(north_noise_mean != _gnss->north_noise().mean()) {
            _gnss->north_noise().mean(north_noise_mean);
        }

        const auto north_noise_std = std::get<1>(values_[28].value);
        if(north_noise_std != _gnss->north_noise().standard_deviation()) {
            _gnss->north_noise().standard_deviation(north_noise_std);
        }

        const auto east_noise_mean = std::get<1>(values_[29].value);
        if(east_noise_mean != _gnss->east_noise().mean()) {
            _gnss->east_noise().mean(east_noise_mean);
        }

        const auto east_noise_std = std::get<1>(values_[30].value);
        if(east_noise_std != _gnss->east_noise().standard_deviation()) {
            _gnss->east_noise().standard_deviation(east_noise_std);
        }

        const auto down_noise_mean = std::get<1>(values_[31].value);
        if(down_noise_mean != _gnss->down_noise().mean()) {
            _gnss->down_noise().mean(down_noise_mean);
        }

        const auto down_noise_std = std::get<1>(values_[32].value);
        if(down_noise_std != _gnss->down_noise().standard_deviation()) {
            _gnss->down_noise().standard_deviation(down_noise_std);
        }

        const auto antenna_x_pos = std::get<1>(values_[33].value);
        if(antenna_x_pos != _gnss->posref_offset().antenna_position().x) {
            _gnss->posref_offset().antenna_position().x = antenna_x_pos;
        }

        const auto antenna_y_pos = std::get<1>(values_[35].value);
        if(antenna_y_pos != _gnss->posref_offset().antenna_position().y) {
            _gnss->posref_offset().antenna_position().y = antenna_y_pos;
        }
        const auto antenna_z_pos = std::get<1>(values_[35].value);
        if(antenna_z_pos != _gnss->posref_offset().antenna_position().z) {
            _gnss->posref_offset().antenna_position().z = antenna_z_pos;
        }

    } catch (const std::bad_variant_access& err) {
        std::cerr << err.what();
    }
}

void GpsComponent::reset() {
    _gnss = std::make_unique<Gnss>(AntennaPosition{0.0, 0.0, 0.0});
}

void GpsComponent::enter_initialization() {   
}

void GpsComponent::exit_initialization() {
}