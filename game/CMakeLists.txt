cmake_minimum_required(VERSION 3.20)
project(game)

set(CMAKE_CXX_STANDARD 17)

#set(GAME_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/person)

add_subdirectory(engine)

add_executable(game main.cpp)

target_include_directories(
        game
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/person
)
target_link_libraries(game PUBLIC engine)
