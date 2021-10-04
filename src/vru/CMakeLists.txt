target_sources(vru
    PRIVATE
    VruComponent.cpp
    VruComponent.hpp
    FmiInstantiate.cpp
    Vru.cpp
    Vru.hpp
    ../common/FmiFunctions.cpp
)

target_link_libraries(vru PRIVATE fmi_common fmi_interface math project_warnings)