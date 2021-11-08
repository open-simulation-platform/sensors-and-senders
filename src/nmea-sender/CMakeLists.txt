target_sources(nmea_sender
    PRIVATE

    NmeaSenderComponent.cpp
    NmeaSenderComponent.hpp

    ConfigParser.cpp
    ConfigParser.hpp

    Enums.cpp
    Enums.hpp

    FmiInstantiate.cpp
    NmeaTelegram.cpp
    NmeaTelegram.hpp
    UdpSender.cpp
    UdpSender.hpp
    ../common/FmiFunctions.cpp
)

if(WIN32)
    target_link_libraries(nmea_sender PRIVATE wsock32 ws2_32)
endif()

target_link_libraries(nmea_sender PUBLIC ${Boost_LIBRARIES} PRIVATE fmi_interface fmi_common pthread project_warnings)