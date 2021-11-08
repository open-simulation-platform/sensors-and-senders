cmake_minimum_required(VERSION 3.15)
project(SensorsAndSenders)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(Boost REQUIRED COMPONENTS system)

add_library(project_warnings INTERFACE)
include(cmake/CompilerWarnings.cmake)
include_directories(thirdparty)
set_project_warnings(project_warnings)

if(NOT WIN32)
    set(CMAKE_BUILD_RPATH_USE_ORIGIN TRUE)
endif()

#====
#Project Options
#====
option(BUILD_GPS "Build GPS FMU" ON)
option(BUILD_GYRO "Build Gyro FMU" ON)
option(BUILD_VRU "Build Vru FMU" ON)
option(BUILD_WIND_SENSOR "Build Wind Sensor FMU" ON)
option(BUILD_NMEA_SENDER "Build nmea sender" ON)

add_subdirectory(src)