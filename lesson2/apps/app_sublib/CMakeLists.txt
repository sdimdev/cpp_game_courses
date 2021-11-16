cmake_minimum_required(VERSION 3.20)
project(app_sublib)

set(CMAKE_CXX_STANDARD 17)

set(SUB_INSTALL_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(SUB_INSTALL_BIN_DIR ${PROJECT_SOURCE_DIR}/bin)
set(SUB_INSTALL_LIB_DIR ${PROJECT_SOURCE_DIR}/lib)
set(SUB_HEADERS_DIR ${PROJECT_SOURCE_DIR}/lib_src)

message(STATUS "INSTALL_INCLUDE_DIR" ${SUB_INSTALL_INCLUDE_DIR})
message(STATUS "INSTALL_BIN_DIR" ${SUB_INSTALL_BIN_DIR})
message(STATUS "INSTALL_LIB_DIR" ${SUB_INSTALL_LIB_DIR})
message(STATUS "HEADERS_DIR" ${SUB_HEADERS_DIR})

add_subdirectory(lib_src)

set(SOURCE_FILES main.cpp)
add_executable(app_sublib ${SOURCE_FILES})

target_link_libraries(app_sublib lib_sublib)

include_directories(${SUB_INSTALL_INCLUDE_DIR})
include_directories(${SUB_HEADERS_DIR})

install(TARGETS app_sublib DESTINATION ${SUB_INSTALL_BIN_DIR})