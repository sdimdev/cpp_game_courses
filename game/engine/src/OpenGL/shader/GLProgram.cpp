//
// Created by dzmitry on 06.12.2021.
//

#include <GL/glew.h>
#include <iostream>
#include <gtc/type_ptr.hpp>
#include "GLProgram.hpp"
#include <utils/GLUtils.cpp>
#include "GlTexture.hpp"
#include "engine/Engine.hpp"

void GLProgram::activate()
{
    if(logDebug)printf("glUseProgram %d\n", program);
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

std::shared_ptr<FloatUniform> GLProgram::createFloatUniform(std::string_view name)
{
    auto uniform = std::make_shared<GlFloatUniform>(std::static_pointer_cast<GLProgram>(shared_from_this()), name);
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
        if(logDebug)printf("GlTextureUniform active %d\n", location);
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
    if(logDebug)printf("GlTextureUniform create %d %s\n", location, name.data());
}

GlMat3Uniform::GlMat3Uniform(const std::shared_ptr<GLProgram> &program, std::string_view name)
{
    location = glGetUniformLocation(program->getProgram(), name.data());
    if(logDebug)printf("GlMat3Uniform create %d %s\n", location, name.data());
}

GlMat4Uniform::GlMat4Uniform(const std::shared_ptr<GLProgram> &program, std::string_view name)
{
    location = glGetUniformLocation(program->getProgram(), name.data());
    if(logDebug)printf("GlMat4Uniform create %d %s\n", location, name.data());
}

void GlMat3Uniform::activate()
{
    glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(value));
    if(logDebug) printf("GlMat3Uniform activate %d \n", location);
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
    if(logDebug) printf("GlVec2Uniform create %d %s\n", location, name.data());
}

void GlVec2Uniform::activate()
{
    glUniform2f(location, value.x, value.y);
    if(logDebug)printf("GlVec2Uniform activate %d \n", location);
}

GlVec3Uniform::GlVec3Uniform(const std::shared_ptr<GLProgram> &program, std::string_view name)
{
    location = glGetUniformLocation(program->getProgram(), name.data());
    if(logDebug)printf("GlVec3Uniform create %d %s\n", location, name.data());
}

void GlVec3Uniform::activate()
{
    glUniform3f(location, value.x, value.y, value.z);
    if(logDebug)printf("GlVec3Uniform activate %d \n", location);
}

GlFloatUniform::GlFloatUniform(const std::shared_ptr<GLProgram> &program, std::string_view name)
{
    location = glGetUniformLocation(program->getProgram(), name.data());
    if(logDebug)printf("GlFloatUniform create %d %s\n", location, name.data());
}

void GlFloatUniform::activate()
{
    glUniform1f(location, value);
    if(logDebug)printf("GlFloatUniform activate %d \n", location);
}
