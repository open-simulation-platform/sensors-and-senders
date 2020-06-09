#include "ConfigParser.h"

#include <nlohmann/json.hpp>
#include "NmeaTelegram.h"
#include <string>
#include <istream>

NmeaConfig parseNmeaConfig(const boost::filesystem::path& path) {

    if(!boost::filesystem::exists(path)) {
        return {};
    }

    std::ifstream configFile (path.string());
    nlohmann::json nmeaConfig;
    configFile >> nmeaConfig;

    NmeaConfig config;
    config.remoteIp = nmeaConfig["RemoteIp"].get<std::string>();  
    config.remotePort = nmeaConfig["RemotePort"].get<int>();

    const auto telegramConfig = nmeaConfig["Telegrams"];

    auto createTelegrams = [](const nlohmann::json& element) {

        NmeaTelegram telegram(element["TelegramName"]);

        auto telegramFields = element["Fields"];

        for (const auto& telegramField : telegramFields) {
            
            NmeaField field;
            field.name = telegramField["VariableName"];

            if (telegramField.find("Decimals") != telegramField.end()) {
                field.decimals = telegramField["Decimals"];
            }

            if (telegramField.find("Length") != telegramField.end()) {
                field.length = telegramField["Length"];
            }
            
            telegram.addField(field);
        }

        return telegram;
    };

    std::vector<NmeaTelegram> telegrams;
    std::transform(telegramConfig.begin(), telegramConfig.end(), std::back_inserter(telegrams), createTelegrams);

    config.telegrams = telegrams;
    return config;
}

