//
// Created by dzmitry on 04.12.2021.
//

#include <GL/glew.h>
#include "SpriteShader.hpp"

struct SpriteShader::Pimpl{
    GLuint vertexShader;
    GLuint fragmentShader;
    GLuint program;
    GLint uniform;
    GLint transformUniform;
    GLint texturesUniform;
    GLint textureSizeUniform;
};

SpriteShader::SpriteShader(){
    _pimpl = std::make_unique<SpriteShader::Pimpl>();
}
void SpriteShader::loadProgram()
{

}

SpriteShader::~SpriteShader() = default;