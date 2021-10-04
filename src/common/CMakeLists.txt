add_subdirectory(fmi)
add_subdirectory(math)

target_sources(fmi_common 
    PRIVATE 
    Component.hpp
    Component.cpp)

target_link_libraries(fmi_common PRIVATE project_warnings)