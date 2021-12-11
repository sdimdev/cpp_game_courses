//
// Created by dzmitry on 06.12.2021.
//

#include <GL/glew.h>
#include <iostream>
#include <gtc/type_ptr.hpp>
#include "GLProgram.hpp"
#include <utils/GLUtils.cpp>
#include "GlTexture.hpp"

GLProgram::GLProgram(const char* vs, const char* ps)
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
    printf("glCreateProgram %d\n", program);
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
    printf("Active Attributes: %d\n", count);

    for (i = 0; i < count; i++)
    {
        glGetActiveAttrib(program, (GLuint)i, bufSize, &length, &size, &type, name);
        printf("Attribute #%d Type: %u Name: %s\n", i, type, name);
        checkErrors(__FILE__, __LINE__);
    }
    checkErrors(__FILE__, __LINE__);
    glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &count);
    printf("Active Uniforms: %d\n", count);
    checkErrors(__FILE__, __LINE__);
    for (i = 0; i < count; i++)
    {
        glGetActiveUniform(program, (GLuint)i, bufSize, &length, &size, &type, name);
        printf("Uniform #%d Type: %u Name: %s\n", i, type, name);
        checkErrors(__FILE__, __LINE__);
    }
    checkErrors(__FILE__, __LINE__);
}

GLProgram::~GLProgram()
{
    printf("glDeleteProgram %d\n", program);
    glDeleteProgram(program);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}


void GLProgram::activate()
{
    printf("glUseProgram %d\n", program);
    glUseProgram(program);
    IShaderProgram::activate();
}

std::shared_ptr<TextureUniform> GLProgram::createTextureUniform(std::string_view name)
{
    auto uniform = std::make_shared<GlTextureUniform>(std::static_pointer_cast<GLProgram>(shared_from_this()), name);
    _uniforms.push_back(uniform);
    return uniform;
}

std::shared_ptr<Mat3Uniform> GLProgram::createMat3Uniform(std::string_view name)
{
    auto uniform = std::make_shared<GlMat3Uniform>(std::static_pointer_cast<GLProgram>(shared_from_this()), name);
    _uniforms.push_back(uniform);
    return uniform;
}

std::shared_ptr<Mat4Uniform> GLProgram::createMat4Uniform(std::string_view name)
{
    auto uniform = std::make_shared<GlMat4Uniform>(std::static_pointer_cast<GLProgram>(shared_from_this()), name);
    _uniforms.push_back(uniform);
    return uniform;
}

std::shared_ptr<Vec2Uniform> GLProgram::createVec2Uniform(std::string_view name)
{
    auto uniform = std::make_shared<GlVec2Uniform>(std::static_pointer_cast<GLProgram>(shared_from_this()), name);
    _uniforms.push_back(uniform);
    return uniform;
}

std::shared_ptr<Vec3Uniform> GLProgram::createVec3Uniform(std::string_view name)
{
    auto uniform = std::make_shared<GlVec3Uniform>(std::static_pointer_cast<GLProgram>(shared_from_this()), name);
    _uniforms.push_back(uniform);
    return uniform;
}

uint32_t GLProgram::getProgram()
{
    return program;
}

void GlTextureUniform::activate()
{
    auto glTexture = std::static_pointer_cast<GlTexture>(texture);
    if (glTexture)
    {
        //TODO: diff texture slots
        printf("GlTextureUniform active %d\n", location);
        glActiveTexture(GL_TEXTURE0);
        checkErrors(__FILE__, __LINE__);
        glUniform1i(location, 0);
        checkErrors(__FILE__, __LINE__);
        glTexture->active();
        checkErrors(__FILE__, __LINE__);
    }
}

GlTextureUniform::GlTextureUniform(const std::shared_ptr<GLProgram>& program, std::string_view name)
{
    location = glGetUniformLocation(program->getProgram(), name.data());
    printf("GlTextureUniform create %d %s\n", location, name.data());
}

GlMat3Uniform::GlMat3Uniform(const std::shared_ptr<GLProgram> &program, std::string_view name)
{
    location = glGetUniformLocation(program->getProgram(), name.data());
    printf("GlMat3Uniform create %d %s\n", location, name.data());
}

GlMat4Uniform::GlMat4Uniform(const std::shared_ptr<GLProgram> &program, std::string_view name)
{
    location = glGetUniformLocation(program->getProgram(), name.data());
    printf("GlMat4Uniform create %d %s\n", location, name.data());
}

void GlMat3Uniform::activate()
{
    glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(value));
    printf("GlMat3Uniform activate %d \n", location);
    checkErrors(__FILE__, __LINE__);
}

void GlMat4Uniform::activate()
{
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
    printf("GlMat4Uniform activate %d \n", location);
    checkErrors(__FILE__, __LINE__);
}

GlVec2Uniform::GlVec2Uniform(const std::shared_ptr<GLProgram> &program, std::string_view name)
{
    location = glGetUniformLocation(program->getProgram(), name.data());
    printf("GlVec2Uniform create %d %s\n", location, name.data());
}

void GlVec2Uniform::activate()
{
    glUniform2f(location, value.x, value.y);
    printf("GlVec2Uniform activate %d \n", location);
}

GlVec3Uniform::GlVec3Uniform(const std::shared_ptr<GLProgram> &program, std::string_view name)
{
    location = glGetUniformLocation(program->getProgram(), name.data());
    printf("GlVec3Uniform create %d %s\n", location, name.data());
}

void GlVec3Uniform::activate()
{
    glUniform3f(location, value.x, value.y, value.z);
    printf("GlVec3Uniform activate %d \n", location);
}
