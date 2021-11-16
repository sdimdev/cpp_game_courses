cmake_minimum_required(VERSION 3.20)
project(sdl2_example)


set(CMAKE_CXX_STANDARD 17)

add_executable(sdl2_example main.cpp)
target_include_directories(sdl2_example PUBLIC ${CMAKE_SOURCE_DIR}/../sdl2/SDL2-2.0.16/include/)
#target_link_directories(sdl2_example PUBLIC ${CMAKE_SOURCE_DIR}/../sdl2_build)
target_link_libraries(sdl2_example libSDL2.a)
