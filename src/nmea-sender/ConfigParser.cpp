#include <string>
#include <fstream>

#include "ConfigParser.hpp"
#include "nlohmann/json.hpp"
#include "NmeaTelegram.hpp"

NmeaConfig parse_nmea_config(const std::string& path) {

    std::ifstream config_file (path);
    nlohmann::json nmea_config;
    config_file >> nmea_config;

    NmeaConfig config;

    const auto telegram_config = nmea_config["Telegrams"];

    auto create_telegrams = [](const nlohmann::json& element) {

        Nmea::Telegram telegram(element["TelegramName"]);

        auto telegram_fields = element["Fields"];

        for (const auto& telegram_field : telegram_fields) {
            
            Nmea::Field field;
            field.name = telegram_field["VariableName"];

            if (telegram_field.find("Decimals") != telegram_field.end()) {
                field.decimals = telegram_field["Decimals"];
            }

            if (telegram_field.find("Length") != telegram_field.end()) {
                field.length = telegram_field["Length"];
            }
            
            telegram.fields.push_back(field);
        }

        return telegram;
    };

    std::vector<Nmea::Telegram> telegrams;
    std::transform(telegram_config.begin(), telegram_config.end(), std::back_inserter(telegrams), create_telegrams);

    config.telegrams = telegrams;
    return config;
}

