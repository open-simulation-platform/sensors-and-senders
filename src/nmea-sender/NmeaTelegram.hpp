#pragma once

#include <string>
#include <vector>
#include <variant>
#include <optional>

struct NmeaField {
    std::string name;
    std::variant<int, double, bool, std::string> value;
    std::optional<int> decimals;
    std::optional<int> length;
};

//Holds a list of variables names that should be extracted from the modelDescription.xml and encoded into an NMEA string
class NmeaTelegram {
public:

    NmeaTelegram(std::string talkerId);

    std::string encode() const;
    void addField(const NmeaField& field);

    std::vector<NmeaField>::iterator begin();
    std::vector<NmeaField>::iterator end();

    std::string talkerId() const;

private:

    std::string talkerId_;
    std::vector<NmeaField> fields_;
};


