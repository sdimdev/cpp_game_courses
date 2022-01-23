//
// Created by dzmitry on 22.12.2021.
//

#include "GLParticalProgram.hpp"


//
// Created by dzmitry on 06.12.2021.
//

#include "../GLHeaders.hpp"
#include <iostream>
#include <utils/GLUtils.cpp>
#include "engine/Engine.hpp"

GLParticalProgram::GLParticalProgram(const char* vs)
{
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

    program = glCreateProgram();
    if(logDebug) printf("glCreateProgram %d\n", program);
    checkErrors(__FILE__, __LINE__);
    glAttachShader(program, vertexShader);
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
    if(logDebug) printf("Active Attributes: %d\n", count);

    for (i = 0; i < count; i++)
    {
        glGetActiveAttrib(program, (GLuint)i, bufSize, &length, &size, &type, name);
        if(logDebug)printf("Attribute #%d Type: %u Name: %s\n", i, type, name);
        checkErrors(__FILE__, __LINE__);
    }
    checkErrors(__FILE__, __LINE__);
    glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &count);
    if(logDebug)printf("Active Uniforms: %d\n", count);
    checkErrors(__FILE__, __LINE__);
    for (i = 0; i < count; i++)
    {
        glGetActiveUniform(program, (GLuint)i, bufSize, &length, &size, &type, name);
        if(logDebug)printf("Uniform #%d Type: %u Name: %s\n", i, type, name);
        checkErrors(__FILE__, __LINE__);
    }
    checkErrors(__FILE__, __LINE__);
}

GLParticalProgram::~GLParticalProgram(){
    if(logDebug)printf("glDeleteProgram %d\n", program);
    glDeleteProgram(program);
    glDeleteShader(vertexShader);
}


void GLProgram::activate()
{
    if(logDebug)printf("glUseProgram %d\n", program);
    glUseProgram(program);
    IShaderProgram::activate();
}

uint32_t GLProgram::getProgram()
{
    return program;
}