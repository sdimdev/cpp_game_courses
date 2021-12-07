//
// Created by dzmitry on 04.12.2021.
//

#include <iostream>
#include <GL/glew.h>


static void checkErrors(const char *file, size_t line)
{
#ifndef NDEBUG
    GLenum err(glGetError());
    while (err != GL_NO_ERROR)
    {
        std::string error;
        switch (err)
        {
            case GL_INVALID_OPERATION:
                error = "INVALID_OPERATION";
                break;

            case GL_INVALID_ENUM:
                error = "GL_INVALID_ENUM";
                break;

            case GL_INVALID_VALUE:
                error = "GL_INVALID_VALUE";
                break;

            case GL_OUT_OF_MEMORY:
                error = "GL_OUT_OF_MEMORY";
                break;

            case GL_INVALID_FRAMEBUFFER_OPERATION:
                error = "GL_INVALID_FRAMEBUFFER_OPERATION";
                break;
            default:
                error = "INVALID_OPERATION";
        }
        std::cerr << "GL_" << error << " : 0x" << std::hex << err << std::dec << " - " << file << ":" << line
                  << std::endl;
        try
        { throw 0; }
        catch (...)
        {}
        err = glGetError();
    }
#endif
}

