#pragma once

#include <string>
#include <vector>
#include <optional>

namespace Nmea {

struct Field {
    std::string name;
    std::string value;
    std::optional<int> decimals;
    std::optional<int> length;
};

//Holds a list of variables names that should be extracted from the modelDescription.xml and encoded into an NMEA string
class Telegram {
public:

    explicit Telegram(std::string talkerId);

    std::string talker_id;
    std::vector<Nmea::Field> fields;
};

std::string encode(const Nmea::Telegram&);

}

