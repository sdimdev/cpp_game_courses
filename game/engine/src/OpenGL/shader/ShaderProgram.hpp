//
// Created by dzmitry on 04.12.2021.
//

#ifndef GAME_SHADERPROGRAM_HPP
#define GAME_SHADERPROGRAM_HPP


#include <GL/glew.h>

class ShaderProgram
{
public:
    virtual GLint getProgram() = 0;
    virtual void loadProgram() = 0;
};


#endif //GAME_SHADERPROGRAM_HPP
