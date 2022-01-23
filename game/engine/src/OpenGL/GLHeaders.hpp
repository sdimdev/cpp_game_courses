//
// Created by dzmitry on 17.01.2022.
//

#ifndef GAME_GLHEADERS_HPP
#define GAME_GLHEADERS_HPP


#if defined __ANDROID__

#define GL_GLEXT_PROTOTYPES
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#define GLES20 1
#define GL33 0
#else
#define GL_SILENCE_DEPRECATION

#include <GL/glew.h>
#include <GL/gl.h>

# define __gl_h_
# define GL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED

/*#include <GL/gl3.h>
#include <OpenGL/gl3ext.h>*/
#define GLES20 0
#define GL33 1
#endif

#endif //GAME_GLHEADERS_HPP
