#pragma once

#include <string>
#include <vector>
#include <optional>

struct NmeaField {
    std::string name;
    std::string value;
    std::optional<int> decimals;
    std::optional<int> length;
};

//Holds a list of variables names that should be extracted from the modelDescription.xml and encoded into an NMEA string
class NmeaTelegram {
public:

    explicit NmeaTelegram(std::string talkerId);

    std::string encode() const;

    std::string talker_id;
    std::vector<NmeaField> fields;
};


