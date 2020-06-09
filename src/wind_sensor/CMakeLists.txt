target_sources(wind_sensor
    PRIVATE
    WindSensorComponent.cpp
    WindSensorComponent.h
    FmiInstantiate.cpp
    WindSensor.cpp
    WindSensor.h
    ../common/FmiFunctions.cpp
)

target_link_libraries(wind_sensor PRIVATE fmi_interface fmi_common math project_warnings)