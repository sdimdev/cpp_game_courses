cmake_minimum_required(VERSION 3.20)
project(engine)

set(CMAKE_CXX_STANDARD 17)
set(OpenGL_GL_PREFERENCE LEGACY) #todo change to other one?

#include(${CMAKE_CURRENT_SOURCE_DIR}/CMakeSources.txt)

file(GLOB_RECURSE ENGINE_SOURCES CONFIGURE_DEPENDS src/*)
add_library(engine STATIC ${ENGINE_SOURCES} src/entity/Vec4.cpp src/entity/Vec4.hpp src/utils/FileUtils.cpp)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/SDL2)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/glew)

#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/glm)

#find_package(OpenGL REQUIRED)
#find_package(GLEW REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS})

set(SDL2MAIN_LIBRARY SDL2main)
set(SDL2_LIBRARY SDL2-static)
set(GLEW_LIBRARY libglew-static)
set(GLEW_INCLUDE_DIR, "/libs/glew/include/")
set(GLEW_LIBRARY, "/libs/glew")
#set(GLM_LIBRARY, "/libs/glm")


find_package(OpenGL REQUIRED)
target_link_libraries(engine )
target_include_directories(engine PUBLIC ${OPENGL_INCLUDE_DIR})

find_package(GLEW REQUIRED)
#target_link_libraries(engine ${GLEW_LIBRARIES})
target_include_directories(engine PUBLIC ${GLEW_INCLUDE_DIR})


target_link_libraries(engine PRIVATE
        ${SDL2MAIN_LIBRARY}
        ${SDL2_LIBRARY}
        ${OPENGL_gl_LIBRARY}
       #${GLM_LIBRARY}
        ${GLEW_LIBRARIES}
        #${GLEW_LIBRARY}
        )

target_include_directories(engine
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/glm
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/SDL2/include
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/glew/include)

