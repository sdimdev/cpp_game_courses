cmake_minimum_required(VERSION 3.20)
project(app_header)

set(CMAKE_CXX_STANDARD 17)

add_executable(app_header main.cpp main2.cpp)
target_include_directories(app_header PUBLIC ${CMAKE_SOURCE_DIR}/../../output/header/include)