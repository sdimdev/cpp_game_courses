cmake_minimum_required(VERSION 3.20)
project(app_dynamic)

set(CMAKE_CXX_STANDARD 17)


add_executable(app_dynamic main.cpp)

target_link_libraries(app_dynamic ${CMAKE_DL_LIBS})

#doesn't work
#set_target_properties(app_dynamic PROPERTIES INSTALL_RPATH "${CMAKE_SOURCE_DIR}/../../output/shared/lib_src/")

target_link_directories(app_dynamic PUBLIC ${CMAKE_SOURCE_DIR}/../../output/shared/lib/)
