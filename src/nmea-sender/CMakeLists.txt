target_sources(nmea_sender
    PRIVATE

    NmeaSenderComponent.cpp
    NmeaSenderComponent.h

    ConfigParser.cpp
    ConfigParser.h

    Enums.cpp
    Enums.h

    FmiInstantiate.cpp
    NmeaTelegram.cpp
    NmeaTelegram.h
    UdpSender.cpp
    UdpSender.h
    ../common/FmiFunctions.cpp
)

if(WIN32)
    target_link_libraries(nmea_sender PRIVATE wsock32 ws2_32)
endif()

target_link_libraries(nmea_sender PUBLIC ${Boost_LIBRARIES} PRIVATE fmi_interface fmi_common project_warnings)