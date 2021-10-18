#include "NmeaTelegram.hpp"

#include <numeric>
#include <sstream>
#include <iostream>
#include <iomanip>

NmeaTelegram::NmeaTelegram(std::string talkerId)
    : talkerId_(std::move(talkerId)) {
}

std::string NmeaTelegram::encode() const {

    std::stringstream nmeaStream;
    nmeaStream << "$" << talkerId_;

    for (const auto& field  : fields_) {
        nmeaStream << ",";

        if(field.decimals.has_value()){
            nmeaStream << std::fixed;
            nmeaStream << std::setprecision(field.decimals.value());
        }

        if(field.length.has_value()) {
            nmeaStream.fill('0');
            nmeaStream.width(field.length.value());
        }
        
        if (auto float_value = std::get_if<double>(&field.value)) {
            nmeaStream << *float_value;
        } else if (auto int_value = std::get_if<int>(&field.value)) {
            nmeaStream << *int_value;
        } else if (auto bool_value = std::get_if<bool>(&field.value)) {
            nmeaStream << *bool_value;
        } else if (auto string_value = std::get_if<std::string>(&field.value)) {
            nmeaStream << *string_value;
        }

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

void NmeaTelegram::addField(const NmeaField& field) {
    fields_.push_back(field);
}

std::vector<NmeaField>::iterator NmeaTelegram::begin() {
    return fields_.begin();
}

std::vector<NmeaField>::iterator NmeaTelegram::end() {
    return fields_.end();
}

std::string NmeaTelegram::talkerId() const {
    return talkerId_;
}
