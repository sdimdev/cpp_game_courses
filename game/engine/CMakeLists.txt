cmake_minimum_required(VERSION 3.20)
project(engine)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES
        src/Engine.cpp
        src/Engine.hpp
        src/IScene.hpp
        src/scenes/LineScene.cpp
        src/scenes/LineScene.hpp
        src/scenes/ScenesFactory.cpp
        src/scenes/ScenesFactory.hpp
        src/utils/CommandLineUtil.cpp)

add_library(engine STATIC ${SOURCES}
        #[[ src/Engine.cpp
         src/Engine.hpp src/Scene.cpp src/Scene.hpp]])

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

