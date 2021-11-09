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

    double m_earth_eccentricity = 0.0818;
    double m_equatorial_radius = 6378137;

    double m_initial_latitude = 62.0;
    double m_initial_longitude = 6.328221;
    double m_initial_height = 0.0;

    double m_rn;
    double m_rm;
};