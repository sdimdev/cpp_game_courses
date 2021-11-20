cmake_minimum_required(VERSION 3.20)
project(engine)

set(CMAKE_CXX_STANDARD 17)

#[[include(${CMAKE_CURRENT_SOURCE_DIR}/CMakeSources.txt)]]

#[[file(GLOB ENGINE_SOURCES  "*/*.h" "*/*.cpp")]]
file(GLOB_RECURSE ENGINE_SOURCES CONFIGURE_DEPENDS src/*)
add_library(engine STATIC ${ENGINE_SOURCES} src/window/WindowEventManager.cpp src/window/WindowEventManager.hpp)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/SDL2)
set(SDL2MAIN_LIBRARY SDL2main)
set(SDL2_LIBRARY SDL2-static)


target_link_libraries(engine PRIVATE
        ${SDL2MAIN_LIBRARY} ${SDL2_LIBRARY})

target_include_directories(engine
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/SDL2/include)

