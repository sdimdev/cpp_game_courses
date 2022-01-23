cmake_minimum_required(VERSION 3.10.2)
project(game)

set(CMAKE_CXX_STANDARD 17)

#set(GAME_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/person)

add_subdirectory(engine)

set(GAME_SRC main.cpp)
if (ANDROID)
    add_library(game SHARED ${GAME_SRC})
else()
    add_executable(game ${GAME_SRC})
endif ()

#add_executable(game main.cpp)

target_include_directories(
        game
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/person
)
target_link_libraries(game PUBLIC engine)
