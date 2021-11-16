cmake_minimum_required(VERSION 3.20)
project(lesson2)

set(CMAKE_CXX_STANDARD 17)

#header library
add_library(lib_header INTERFACE bestLib.ipp)
set_target_properties(lib_header PROPERTIES PUBLIC_HEADER bestLib.ipp)
install(TARGETS lib_header
        PUBLIC_HEADER
        DESTINATION ${CMAKE_SOURCE_DIR}/output/header/include)

#static library
add_library(lib_static STATIC
        library.hpp
        library.cpp)
set_target_properties(lib_static
        PROPERTIES
        PUBLIC_HEADER ${CMAKE_SOURCE_DIR}/library.hpp
        LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/output/static/lib)

install(TARGETS lib_static
        PUBLIC_HEADER DESTINATION ${CMAKE_SOURCE_DIR}/output/static/include
        ARCHIVE DESTINATION ${CMAKE_SOURCE_DIR}/output/static/lib)

#shared library
add_library(lib_shared SHARED library.cpp library.hpp)

set_target_properties(lib_shared
        PROPERTIES
        PUBLIC_HEADER ${CMAKE_SOURCE_DIR}/library.hpp)

install(TARGETS lib_shared
        PUBLIC_HEADER DESTINATION ${CMAKE_SOURCE_DIR}/output/shared/include/
        ARCHIVE DESTINATION ${CMAKE_SOURCE_DIR}/output/shared/lib/
        LIBRARY DESTINATION ${CMAKE_SOURCE_DIR}/output/shared/lib/)




