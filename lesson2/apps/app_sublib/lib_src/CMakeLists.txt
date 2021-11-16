cmake_minimum_required(VERSION 3.20)
project(lib_sublib)

set(CMAKE_CXX_STANDARD 17)

#[[

set(SUB_INSTALL_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(SUB_INSTALL_BIN_DIR ${PROJECT_SOURCE_DIR}/bin)
set(SUB_INSTALL_LIB_DIR ${PROJECT_SOURCE_DIR}/lib)
set(SUB_HEADERS_DIR ${PROJECT_SOURCE_DIR}/lib_src)
]]

set(SOURCE_FILES
        library.cpp
        library.hpp
        )

include_directories(${SUB_INSTALL_INCLUDE_DIR})
include_directories(${SUB_HEADERS_DIR})

add_library(lib_sublib STATIC ${SOURCE_FILES})

install(TARGETS lib_sublib DESTINATION ${SUB_INSTALL_LIB_DIR})
install(FILES library.hpp DESTINATION ${SUB_INSTALL_INCLUDE_DIR})