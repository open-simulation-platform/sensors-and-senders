#include "NmeaTelegram.hpp"

#include <numeric>
#include <sstream>
#include <iostream>
#include <iomanip>

namespace Nmea {

Telegram::Telegram(std::string talker_id)
    : talker_id(std::move(talker_id)) {
}

std::string encode(const Nmea::Telegram& telegram) {

    std::stringstream nmeaStream;
    nmeaStream << "$" << telegram.talker_id;

    for (const auto& field  : telegram.fields) {
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

}