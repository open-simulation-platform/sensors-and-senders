#include "NmeaTelegram.hpp"

#include <numeric>
#include <sstream>
#include <iostream>
#include <iomanip>

namespace Nmea {

Telegram::Telegram(std::string id)
    : talker_id(std::move(id)) {
}

std::string encode(const Nmea::Telegram& telegram) {

    std::stringstream nmea_stream;
    nmea_stream << "$" << telegram.talker_id;

    for (const auto& field  : telegram.fields) {
        nmea_stream << ",";

        if(field.decimals.has_value()){
            nmea_stream << std::fixed;
            nmea_stream << std::setprecision(field.decimals.value());
        }

        if(field.length.has_value()) {
            nmea_stream.fill('0');
            nmea_stream.width(field.length.value());
        }
        
        nmea_stream << field.value;
    }

    auto nmea_message = nmea_stream.str();

    auto checksum = std::accumulate(std::next(nmea_message.begin()), nmea_message.end(), 0, std::bit_xor<>());

    nmea_message.append("*");
    std::stringstream stream;
    stream << std::setfill('0') << std::setw(2) << std::hex << std::uppercase << checksum;
    nmea_message.append(stream.str());
    nmea_message.append("\r\n");

    return nmea_message;
}

}