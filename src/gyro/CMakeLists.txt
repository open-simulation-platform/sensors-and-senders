target_sources(gyro
    PRIVATE
    GyroComponent.cpp
    Gyro.cpp
    FmiInstantiate.cpp
    
    GyroComponent.h
    Gyro.h
    
    ../common/FmiFunctions.cpp
    )

target_link_libraries(gyro PRIVATE fmi_interface fmi_common math project_warnings)