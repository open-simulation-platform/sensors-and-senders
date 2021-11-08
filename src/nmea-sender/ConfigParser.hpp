#pragma once
#include <vector>

#include "NmeaTelegram.hpp"

struct NmeaConfig {
    std::string remoteIp;
    int remotePort;
    std::vector<Nmea::Telegram> telegrams;
};

NmeaConfig parseNmeaConfig(const std::string& path);
