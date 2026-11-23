cmake_minimum_required(VERSION 3.28)

project(DevCaddy 
    VERSION 0.1.0
    DESCRIPTION "A desktop toolkit for developers"
    LANGUAGES CXX)

include(FetchContent)

set(SDL_SHARED OFF)
set(SDL_STATIC ON)
set(SDL_TEST_LIBRARY OFF)
set(SDL_INSTALL OFF)

FetchContent_Declare(SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-3.4.4
    GIT_SHALLOW TRUE
)

FetchContent_Declare(imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG v1.92.6
    GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(SDL3 imgui)
find_package(OpenGL REQUIRED)

add_library(imgui STATIC
    "${imgui_SOURCE_DIR}/imgui.cpp"
    "${imgui_SOURCE_DIR}/imgui_draw.cpp"
    "${imgui_SOURCE_DIR}/imgui_tables.cpp"
    "${imgui_SOURCE_DIR}/imgui_widgets.cpp"
    "${imgui_SOURCE_DIR}/imgui_demo.cpp"
    "${imgui_SOURCE_DIR}/backends/imgui_impl_sdl3.cpp"
    "${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp"
)

target_include_directories(imgui PUBLIC
    "${imgui_SOURCE_DIR}"
    "${imgui_SOURCE_DIR}/backends"
)

target_link_libraries(imgui PRIVATE SDL3::SDL3 ${CMAKE_DL_LIBS})

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

target_link_libraries(DevCaddy PRIVATE imgui SDL3::SDL3 OpenGL::GL)

install(TARGETS DevCaddy
    RUNTIME DESTINATION bin
)