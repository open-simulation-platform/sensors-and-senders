add_library(math STATIC)
target_include_directories(math PRIVATE .)
set_property(TARGET math PROPERTY POSITION_INDEPENDENT_CODE ON)

add_library(fmi_interface INTERFACE)

add_library(fmi_common STATIC)
target_include_directories(fmi_common PRIVATE .)
set_property(TARGET fmi_common PROPERTY POSITION_INDEPENDENT_CODE ON)

add_subdirectory(common)

if(BUILD_GYRO)
    add_library(gyro SHARED)
    target_include_directories(gyro PRIVATE .)
    add_subdirectory(gyro)
endif()

if(BUILD_GPS)
    add_library(gps SHARED)
    target_include_directories(gps PRIVATE .)
    add_subdirectory(gps)
endif()

if(BUILD_WIND_SENSOR)
    add_library(wind_sensor SHARED) 
    target_include_directories(wind_sensor PRIVATE .)
    add_subdirectory(wind_sensor)
endif()

if(BUILD_VRU)
    add_library(vru SHARED)
    target_include_directories(vru PRIVATE .)
    add_subdirectory(vru)
endif()

if(BUILD_NMEA_SENDER)
    add_library(nmea_sender SHARED)
    target_include_directories(nmea_sender PRIVATE .)
    add_subdirectory(nmea-sender)
endif()