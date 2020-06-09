#pragma once

#include <memory>
#include "Gnss.h"
#include <common/Component.h>

class GpsComponent : public Component {
public:

    GpsComponent(std::string instance_name, const fmi2Type type, const fmi2String uuid, 
        std::string resource_directory, const fmi2CallbackFunctions* callback_functions);
    
    ~GpsComponent() = default;

    void enter_initialization() override;
    void step(double step_size) override;
    void reset();

private:

    std::unique_ptr<Gnss> _gnss;
};