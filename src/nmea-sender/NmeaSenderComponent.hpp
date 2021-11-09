#pragma once

#include <unordered_map>
#include <string>
#include <vector>

#include "common/Component.hpp"
#include "NmeaTelegram.hpp"
#include "Enums.hpp"
#include "UdpSender.hpp"

struct Variable {
    Causality causality;
    fmi2ValueReference reference;
    Type type;
    std::string start;
};

class NmeaSenderComponent : public Component {
public:

    NmeaSenderComponent(const std::string& instance_name, const fmi2Type& type, const fmi2String& uuid, const std::string& resource_directory,
        const fmi2CallbackFunctions* callback_functions);

    void enter_initialization() override;
    void exit_initialization() override;
    void step(double step_size) override;

private:

    void parse_model_description();
    void parse_config();

    void update_telegrams();
    void send_telegrams();

    //Variables have unique names
    std::unordered_map<std::string, Variable> m_variables;

    std::vector<Nmea::Telegram> m_telegrams;

    std::string m_remote_ip = "127.0.0.1";
    int m_remote_port = 50555;
    UdpSender m_udp_sender;
};

