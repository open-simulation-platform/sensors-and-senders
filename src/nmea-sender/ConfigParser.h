#pragma once
#include <vector>
#include <boost/filesystem.hpp>
#include "NmeaTelegram.h"

struct NmeaConfig {
    std::string remoteIp;
    int remotePort;
    std::vector<NmeaTelegram> telegrams;
};

NmeaConfig parseNmeaConfig(const boost::filesystem::path& path);
