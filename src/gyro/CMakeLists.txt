target_sources(gyro
    PRIVATE
    GyroComponent.cpp
    GyroComponent.hpp
    FmiInstantiate.cpp
    
    ../common/FmiFunctions.cpp
)

target_link_libraries(gyro PRIVATE fmi_interface fmi_common math project_warnings)