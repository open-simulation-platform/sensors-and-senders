#include <string>
#include <fstream>

#include "ConfigParser.hpp"
#include "nlohmann/json.hpp"
#include "NmeaTelegram.hpp"

NmeaConfig parseNmeaConfig(const std::string& path) {

    std::ifstream configFile (path);
    nlohmann::json nmeaConfig;
    configFile >> nmeaConfig;

    NmeaConfig config;

    const auto telegramConfig = nmeaConfig["Telegrams"];

    auto createTelegrams = [](const nlohmann::json& element) {

        Nmea::Telegram telegram(element["TelegramName"]);

        auto telegramFields = element["Fields"];

        for (const auto& telegramField : telegramFields) {
            
            Nmea::Field field;
            field.name = telegramField["VariableName"];

            if (telegramField.find("Decimals") != telegramField.end()) {
                field.decimals = telegramField["Decimals"];
            }

            if (telegramField.find("Length") != telegramField.end()) {
                field.length = telegramField["Length"];
            }
            
            telegram.fields.push_back(field);
        }

        return telegram;
    };

    std::vector<Nmea::Telegram> telegrams;
    std::transform(telegramConfig.begin(), telegramConfig.end(), std::back_inserter(telegrams), createTelegrams);

    config.telegrams = telegrams;
    return config;
}

