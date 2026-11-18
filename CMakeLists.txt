cmake_minimum_required(VERSION 3.28)

project(DevCaddy 
    VERSION 0.1.0
    DESCRIPTION "A desktop toolkit for developers"
    LANGUAGES CXX)

add_executable(DevCaddy
    src/main.cpp
)

set_target_properties(DevCaddy PROPERTIES
    CXX_STANDARD 17
    CMAKE_CXX_STANDARD_REQUIRED ON
    CMAKE_CXX_EXTENSIONS OFF
)

if(MSVC)
    target_compile_options(DevCaddy PRIVATE /EHsc)
endif()

install(TARGETS DevCaddy
    RUNTIME DESTINATION bin
)