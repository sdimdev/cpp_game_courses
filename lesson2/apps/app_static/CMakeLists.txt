cmake_minimum_required(VERSION 3.20)
project(app_static)

set(CMAKE_CXX_STANDARD 17)

add_executable(app_static main.cpp main2.cpp)

target_include_directories(app_static PUBLIC ${CMAKE_SOURCE_DIR}/../../output/static/include)
target_link_directories(app_static PUBLIC ${CMAKE_SOURCE_DIR}/../../output/static/lib/)
target_link_libraries(app_static liblib_static.a)