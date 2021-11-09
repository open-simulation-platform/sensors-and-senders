#pragma once
#include <vector>

#include "NmeaTelegram.hpp"

struct NmeaConfig {
    std::string remoteIp;
    int remotePort;
    std::vector<Nmea::Telegram> telegrams;
};

NmeaConfig parse_nmea_config(const std::string& path);
