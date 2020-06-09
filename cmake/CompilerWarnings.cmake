function(set_project_warnings project_name)
    option(WARNING_AS_ERRORS "Treat compiler warnings as errors" TRUE)
    
    set(CLANG_WARNINGS
        -Wall
        -Wextra
        -Wshadow
        -Wnon-virtual-dtor
        -Wold-style-cast
        -Wcast-align
        -Wunused
        -Woverloaded-virtual
        -Wpedantic
        -Wconversion
        -Wsign-conversion
        -Wnull-dereference
        -Wdouble-promotion
        -Wformat=2
    )

    if (WARNINGS_AS_ERRORS)
        set(CLANG_WARNINGS ${CLANG_WARNINGS} -Werror)
    endif()

    set(GCC_WARNINGS
        ${CLANG_WARNINGS}
        -Wmisleading-indentation
        -Wduplicated-cond
        -Wlogical-op
        -Wuseless-cast
    )

    if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        set(PROJECT_WARNINGS ${CLANG_WARNINGS})
    else()
        set(PROJECT_WARNINGS ${GCC_WARNINGS})
    endif()

    target_compile_options(${project_name} INTERFACE ${PROJECT_WARNINGS})
endfunction()