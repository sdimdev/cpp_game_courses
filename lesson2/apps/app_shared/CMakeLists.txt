cmake_minimum_required(VERSION 3.20)
project(app_shared)

set(CMAKE_CXX_STANDARD 17)


add_executable(app_shared main.cpp)

target_include_directories(app_shared PUBLIC ${CMAKE_SOURCE_DIR}/../../output/shared/include)


find_library(lib_shared_location NAMES liblib_shared.so)
message(STATUS ${lib_shared_location})

target_link_directories(app_shared PUBLIC ${CMAKE_SOURCE_DIR}/../../output/shared/lib/)
target_link_libraries(app_shared liblib_shared.so)


#[[include_directories("/usr/local/lib/")
add_library(shared_lib SHARED IMPORTED)
target_link_libraries(shared_lib
        INTERFACE "/usr/local/lib//liblib_shared.so")]]

#[[add_executable(app_shared main.cpp)
target_link_libraries(app_shared lib_shared)]]
