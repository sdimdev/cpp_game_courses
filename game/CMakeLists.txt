cmake_minimum_required(VERSION 3.20)
project(game)

set(CMAKE_CXX_STANDARD 17)

#set(SOURCES main.cpp)

add_subdirectory(engine)

add_executable(game main.cpp)
target_link_libraries(game PUBLIC engine)
