#pragma once

#include <string>

#include "Vru.hpp"

#include "common/Component.hpp"
#include "common/fmi/fmi2TypesPlatform.h"

class VruComponent : public Component {
public:

    VruComponent(std::string instance_name, const fmi2Type& type, const fmi2String& uuid, std::string resources_directory,
        const fmi2CallbackFunctions* callback_functions);

    void enter_initialization() override;
    void exit_initialization() override;
    void step(double step_size) override;
    
private:

    Vru _vru;
};