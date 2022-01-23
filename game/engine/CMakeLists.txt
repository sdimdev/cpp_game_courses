cmake_minimum_required(VERSION 3.10.2)
project(engine)

set(CMAKE_CXX_STANDARD 17)
set(OpenGL_GL_PREFERENCE LEGACY) #todo change to other one?


file(GLOB_RECURSE ENGINE_SOURCES CONFIGURE_DEPENDS src/*)
add_library(engine STATIC ${ENGINE_SOURCES} ${STBI_LIBRARY})

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/SDL2)


set(SDL2MAIN_LIBRARY SDL2main)
set(SDL2_LIBRARY SDL2-static)

target_link_libraries(engine)
if (ANDROID)
    find_library(libGLESv2 REQUIRED)
    set(OPENGL_LIBRARY GLESv2)
    target_link_libraries(engine PRIVATE ${OPENGL_LIBRARY})
else ()
    find_package(OpenGL REQUIRED)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/glew)
    target_include_directories(engine PUBLIC ${OPENGL_INCLUDE_DIR})
    include_directories(${OPENGL_INCLUDE_DIRS})
    target_link_libraries(engine PRIVATE ${OPENGL_gl_LIBRARY})
    target_include_directories(engine PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/libs/glew/include)
endif ()

if (ANDROID)
    target_link_libraries(engine PRIVATE
            ${SDL2MAIN_LIBRARY}
            ${SDL2_LIBRARY}
            ${STBI_LIBRARY}
            )
else ()
    target_link_libraries(engine PRIVATE
            ${SDL2MAIN_LIBRARY}
            ${SDL2_LIBRARY}

            ${GLEW_LIBRARY}
            libglew_static
            ${STBI_LIBRARY}
            )
endif ()

target_include_directories(engine
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/glm
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/SDL2/include
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/stbi)

