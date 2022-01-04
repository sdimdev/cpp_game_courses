cmake_minimum_required(VERSION 3.20)
project(engine)

set(CMAKE_CXX_STANDARD 17)
set(OpenGL_GL_PREFERENCE LEGACY) #todo change to other one?


file(GLOB_RECURSE ENGINE_SOURCES CONFIGURE_DEPENDS src/*)
add_library(engine STATIC ${ENGINE_SOURCES} ${STBI_LIBRARY} src/entity/IParticleBuffer.cpp src/entity/IParticleBuffer.hpp src/OpenGL/vertex/ParticleBuffer.cpp src/OpenGL/vertex/ParticleBuffer.hpp src/entity/IShaderBuffer.cpp src/entity/IShaderBuffer.hpp src/entity/ParticleEmmiter.cpp src/entity/ParticleEmmiter.hpp src/OpenGL/shader/GLParticalProgram.cpp src/OpenGL/shader/GLParticalProgram.hpp)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/SDL2)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/glew)

include_directories(${OPENGL_INCLUDE_DIRS})

set(SDL2MAIN_LIBRARY SDL2main)
set(SDL2_LIBRARY SDL2-static)
#set(GLEW_INCLUDE_DIR, "/libs/glew/include/")
#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/glew)
#set(GLEW_LIBRARY, "/libs/glew")
#set(GLEW_LIBRARY, libglew_static)


find_package(OpenGL REQUIRED)
target_link_libraries(engine )
target_include_directories(engine PUBLIC ${OPENGL_INCLUDE_DIR})

#find_package(GLEW REQUIRED)
#target_include_directories(engine PUBLIC ${GLEW_INCLUDE_DIR})

#[[

set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/imgui)

set(IMGUI_SOURCES )
add_library(IMGUI STATIC)

target_sources( IMGUI
        PRIVATE
        ${IMGUI_DIR}/imgui_demo.cpp
        ${IMGUI_DIR}/imgui_draw.cpp
        ${IMGUI_DIR}/imgui_tables.cpp
        ${IMGUI_DIR}/imgui_widgets.cpp
        ${IMGUI_DIR}/imgui.cpp

        PRIVATE
        ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
        ${IMGUI_DIR}/backends/imgui_impl_sdl.cpp
        )

target_include_directories( IMGUI
        PUBLIC ${IMGUI_DIR}
        PUBLIC ${IMGUI_DIR}/backends
        PUBLIC ${SDL2_DIR}/include
        )]]

target_link_libraries(engine PRIVATE
        ${SDL2MAIN_LIBRARY}
        ${SDL2_LIBRARY}
        ${OPENGL_gl_LIBRARY}
#        ${GLEW_LIBRARY}
        libglew_static
        ${STBI_LIBRARY}
        )

target_include_directories(engine
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/glm
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/SDL2/include
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/stbi
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/glew/include)

