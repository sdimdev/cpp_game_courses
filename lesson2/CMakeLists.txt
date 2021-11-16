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
add_library(lib_static STATIC library.cpp)
set_target_properties(lib_static PROPERTIES PUBLIC_HEADER ${CMAKE_SOURCE_DIR}/library.h)
install(TARGETS lib_static
        PUBLIC_HEADER DESTINATION ${CMAKE_SOURCE_DIR}/output/static/include
        ARCHIVE DESTINATION ${CMAKE_SOURCE_DIR}/output/static/lib)

#shared library
add_library(lib_shared SHARED library.cpp)
set_target_properties(lib_shared PROPERTIES PUBLIC_HEADER ${CMAKE_SOURCE_DIR}/library.h)
install(TARGETS lib_shared
        PUBLIC_HEADER DESTINATION ${CMAKE_SOURCE_DIR}/output/shared/include
        ARCHIVE DESTINATION ${CMAKE_SOURCE_DIR}/output/shared/lib)

## CMake Error at cmake_install.cmake:88 (file):
#  file INSTALL cannot copy file
#  "/media/dzmitry/u2/projects/sdim/cpp/lessons/lesson2/liblib_shared.so" to
#  "/usr/local/lib/liblib_shared.so": Success.
# use that ^__^

# sudo cmake --build . --target install

# todo - change permission by https://apple.stackexchange.com/a/192232



