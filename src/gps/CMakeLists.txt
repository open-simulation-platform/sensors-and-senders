target_sources(gps
    PRIVATE
    GpsComponent.cpp
    FmiInstantiate.cpp
    Gnss.cpp
    Ned2Llh.cpp
    UtcTime.cpp
    
    GpsComponent.hpp
    Gnss.hpp
    Ned2Llh.hpp
    UtcTime.hpp
    
    ../common/FmiFunctions.cpp
)

target_link_libraries(gps PUBLIC fmi_interface PRIVATE fmi_common math project_warnings)