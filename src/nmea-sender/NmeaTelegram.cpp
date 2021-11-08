#include "NmeaTelegram.hpp"

#include <numeric>
#include <sstream>
#include <iostream>
#include <iomanip>

NmeaTelegram::NmeaTelegram(std::string talker_id)
    : talker_id(std::move(talker_id)) {
}

std::string NmeaTelegram::encode() const {

    std::stringstream nmeaStream;
    nmeaStream << "$" << talker_id;

    for (const auto& field  : fields) {
        nmeaStream << ",";

        if(field.decimals.has_value()){
            nmeaStream << std::fixed;
            nmeaStream << std::setprecision(field.decimals.value());
        }

        if(field.length.has_value()) {
            nmeaStream.fill('0');
            nmeaStream.width(field.length.value());
        }
        
        nmeaStream << field.value;
    }

    auto nmeaMessage = nmeaStream.str();

    auto checksum = std::accumulate(std::next(nmeaMessage.begin()), nmeaMessage.end(), 0, std::bit_xor<>());

    nmeaMessage.append("*");
    std::stringstream stream;
    stream << std::setfill('0') << std::setw(2) << std::hex << std::uppercase << checksum;
    nmeaMessage.append(stream.str());
    nmeaMessage.append("\r\n");

    return nmeaMessage;
}