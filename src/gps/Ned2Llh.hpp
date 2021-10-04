#pragma once 

class Ned2LLH {
public:
    explicit Ned2LLH(double initial_latitude = 62.00 , double initial_longitude = 6.328221  , double initial_height = 0.0);
    
    double latitude(double north_position) const;
    double longitude(double east_position) const;
    double height(double height) const;

private:

    double delta_latitude(double north_position) const;
    double delta_longitude(double east_position) const;

    double rn() const;
    double rm() const;

    double _earth_eccentricity = 0.0818;
    double _equatorial_radius = 6378137;

    double _initial_latitude = 62.0;
    double _initial_longitude = 6.328221;
    double _initial_height = 0.0;

    double _rn;
    double _rm;
};

double rad2deg(double rad);
double deg2rad(double deg);