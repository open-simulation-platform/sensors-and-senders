#pragma once

#include <string>
#include <common/Component.h>
#include <common/fmi/fmi2TypesPlatform.h>
#include "Vru.h"

class VruComponent : public Component {
public:

    VruComponent(std::string instance_name, const fmi2Type type, const fmi2String uuid, std::string resources_directory,
        const fmi2CallbackFunctions* callback_functions);

    ~VruComponent() = default;

    void enter_initialization() override;
    void step(double step_size) override;
    
private:

    Vru _vru;
};