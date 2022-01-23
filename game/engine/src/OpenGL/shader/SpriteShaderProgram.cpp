//
// Created by dzmitry on 04.12.2021.
//

#include "SpriteShaderProgram.hpp"
#include <utils/FileUtils.cpp>

#include "../GLHeaders.hpp"
#include <iostream>
#include <gtc/type_ptr.hpp>
#include <utils/GLUtils.cpp>
#include "GlTexture.hpp"
#include "engine/Engine.hpp"

SpriteShaderProgram::SpriteShaderProgram(
        std::string_view vpath,
        std::string_view fpath
)
{
    const char *vs = loadFromFile(vpath);
    const char *ps = loadFromFile(fpath);

    printf("\n VERTEX SHADER %s\n", vs);
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vs, nullptr);
    glCompileShader(vertexShader);
    checkErrors(__FILE__, __LINE__);

    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    printf("\n FRAGMENT SHADER %s\n", ps);
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &ps, nullptr);
    glCompileShader(fragmentShader);
    checkErrors(__FILE__, __LINE__);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    program = glCreateProgram();
    if (logDebug) printf("glCreateProgram %d\n", program);
    checkErrors(__FILE__, __LINE__);
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    glUseProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(program, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::LINKING_FAILED\n" << infoLog << std::endl;
    }

    GLint i;
    GLint count;

    GLint size; // size of the variable
    GLenum type; // type of the variable (float, vec3 or mat4, etc)

    const GLsizei bufSize = 16; // maximum name length
    GLchar name[bufSize]; // variable name in GLSL
    GLsizei length; // name length
    checkErrors(__FILE__, __LINE__);
    glGetProgramiv(program, GL_ACTIVE_ATTRIBUTES, &count);
    if (logDebug) printf("Active Attributes: %d\n", count);

    for (i = 0; i < count; i++)
    {
        glGetActiveAttrib(program, (GLuint) i, bufSize, &length, &size, &type, name);
        if (logDebug)printf("Attribute #%d Type: %u Name: %s\n", i, type, name);
        checkErrors(__FILE__, __LINE__);
    }
    checkErrors(__FILE__, __LINE__);
    glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &count);
    if (logDebug)printf("Active Uniforms: %d\n", count);
    checkErrors(__FILE__, __LINE__);
    for (i = 0; i < count; i++)
    {
        glGetActiveUniform(program, (GLuint) i, bufSize, &length, &size, &type, name);
        if (logDebug)printf("Uniform #%d Type: %u Name: %s\n", i, type, name);
        checkErrors(__FILE__, __LINE__);
    }
    checkErrors(__FILE__, __LINE__);
}

SpriteShaderProgram::~SpriteShaderProgram()
{
    if (logDebug)printf("glDeleteProgram %d\n", program);
    glDeleteProgram(program);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}
