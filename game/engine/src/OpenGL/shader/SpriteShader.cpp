//
// Created by dzmitry on 04.12.2021.
//

#include "SpriteShader.hpp"
#include <utils/GLUtils.cpp>
#include <GL/glew.h>
#include <iostream>
#include <unistd.h>
#include <utils/FileUtils.cpp>

struct SpriteShader::Pimpl
{
    GLuint vertexShader;
    GLuint fragmentShader;
    GLuint program;
    GLint screenSizeUniform;
    GLint transformUniform;
    GLint texturesUniform;
    GLint textureSizeUniform;
};

SpriteShader::SpriteShader()
{
    _pimpl = std::make_unique<SpriteShader::Pimpl>();
}

void SpriteShader::loadProgram()
{
    GLint success;
    GLchar infoLog[512];
    char tmp[256];
    getcwd(tmp, 256);
    printf("%s", tmp);
    _pimpl->vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char *c_v_shader =
            loadFromFile("../engine/src/v_shader.glsl");
    printf("\n VERTEX SHADER %s\n", c_v_shader);
    glShaderSource(_pimpl->vertexShader, 1, &c_v_shader, nullptr);
    glCompileShader(_pimpl->vertexShader);

    checkErrors();
    glGetShaderiv(_pimpl->vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(_pimpl->vertexShader, 512, nullptr, infoLog);
        std::cerr << infoLog << std::endl;
    }

    _pimpl->fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char *c_f_shader =
            loadFromFile("../engine/src/f_shader.glsl");
    printf("\n FRAGMENT SHADER: %s\n", c_f_shader);
    glShaderSource(_pimpl->fragmentShader, 1, &c_f_shader, nullptr);
    glCompileShader(_pimpl->fragmentShader);

    checkErrors();
    glGetShaderiv(_pimpl->fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(_pimpl->fragmentShader, 512, nullptr, infoLog);
        std::cerr << infoLog << std::endl;
    }

    //линкуем шейдера
    _pimpl->program = glCreateProgram();

    glAttachShader(_pimpl->program, _pimpl->vertexShader);
    glAttachShader(_pimpl->program, _pimpl->fragmentShader);
    glLinkProgram(_pimpl->program);

    checkErrors();
    glGetShaderiv(_pimpl->fragmentShader, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(_pimpl->fragmentShader, 512, nullptr, infoLog);
        std::cerr << infoLog << std::endl;
    }

    glUseProgram(_pimpl->program);

    //задаем униформу
    _pimpl->screenSizeUniform = glGetUniformLocation(_pimpl->program, "screenSize");
    _pimpl->transformUniform = glGetUniformLocation(_pimpl->program, "transform");
    _pimpl->texturesUniform = glGetUniformLocation(_pimpl->program, "uTexture");
    _pimpl->textureSizeUniform = glGetUniformLocation(_pimpl->program, "textureSize");
}

GLint SpriteShader::getProgram()
{
    return _pimpl->program;
}

GLint SpriteShader::screenSizeUniform()
{
    return _pimpl->screenSizeUniform;
}

GLint SpriteShader::transformUniform()
{
    return _pimpl->transformUniform;
}

GLint SpriteShader::textureUniform()
{
    return _pimpl->texturesUniform;
}

SpriteShader::~SpriteShader() = default;