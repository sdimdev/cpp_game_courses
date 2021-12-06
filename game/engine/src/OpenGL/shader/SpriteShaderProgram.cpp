//
// Created by dzmitry on 04.12.2021.
//

#include "SpriteShaderProgram.hpp"
#include <utils/GLUtils.cpp>
#include <GL/glew.h>
#include <iostream>
#include <unistd.h>
#include <utils/FileUtils.cpp>
#include <gtc/type_ptr.hpp>

struct SpriteShaderProgram::Pimpl
{
    GLuint vertexShader;
    GLuint fragmentShader;
    GLuint program;
};

SpriteShaderProgram::SpriteShaderProgram()
{
    _pimpl = std::make_unique<SpriteShaderProgram::Pimpl>();
}

void SpriteShaderProgram::loadProgram()
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

    checkErrors(__FILE__, __LINE__);
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

    checkErrors(__FILE__, __LINE__);
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

    checkErrors(__FILE__, __LINE__);
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

GLint SpriteShaderProgram::getProgram()
{
    return _pimpl->program;
}

void SpriteShaderProgram::setupScreenSize(float w, float h)
{
    glUniform2f(screenSizeUniform(), w, h);
}

void SpriteShaderProgram::setupTransformMat4(glm::mat4 transformData)
{
    glUniformMatrix4fv(transformUniform(), 1, GL_FALSE, glm::value_ptr(transformData));
}

void SpriteShaderProgram::setupTexture(unsigned int texture)
{
    //bind texture
    glActiveTexture(GL_TEXTURE0);
    glUniform1i(textureUniform(), 0);
    //glUniform2i(_pimpl->textureSizeUniform, _pimpl->tl.width, _pimpl->tl.height);
    glBindTexture(GL_TEXTURE_2D, texture);

}

std::shared_ptr<TextureUniform> SpriteShaderProgram::createTextureUniform(std::string_view name)
{
    auto uniform = std::make_shared<GlTextureUniform>(std::static_pointer_cast<SpriteShaderProgram>(shared_from_this()), name);
    _uniforms.push_back(uniform);
    return uniform;
}

std::shared_ptr<Mat3Uniform> SpriteShaderProgram::createMat3Uniform(std::string_view name)
{
    auto uniform = std::make_shared<GlMat3Uniform>(std::static_pointer_cast<SpriteShaderProgram>(shared_from_this()), name);
    _uniforms.push_back(uniform);
    return uniform;
}

std::shared_ptr<Vec2Uniform> SpriteShaderProgram::createVec2Uniform(std::string_view name)
{
    auto uniform = std::make_shared<GlVec2Uniform>(std::static_pointer_cast<SpriteShaderProgram>(shared_from_this()), name);
    _uniforms.push_back(uniform);
    return uniform;
}

void SpriteShaderProgram::activate()
{
    GLProgram::activate();
}

void GlTextureUniform::activate()
{
    auto glTexture = std::dynamic_pointer_cast<GlTexture>(texture);
    if (glTexture)
    {
        //TODO: diff texture slots
        glActiveTexture(GL_TEXTURE0);
        glTexture->active();

        glUniform1i(_location, 0);
    }
}

GlTextureUniform::GlTextureUniform(const std::shared_ptr<SpriteShaderProgram>& program, std::string_view name)
{
    _location = glGetUniformLocation(program->getProgram(), name.data());
}

GlMat3Uniform::GlMat3Uniform(const std::shared_ptr<SpriteShaderProgram> &program, std::string_view name)
{
    _location = glGetUniformLocation(program->getProgram(), name.data());
}

void GlMat3Uniform::activate()
{
    glUniformMatrix3fv(_location, 1, GL_FALSE, glm::value_ptr(value));
}

GlVec2Uniform::GlVec2Uniform(const std::shared_ptr<SpriteShaderProgram> &program, std::string_view name)
{
    _location = glGetUniformLocation(program->getProgram(), name.data());
}

void GlVec2Uniform::activate()
{
    glUniform2f(_location, value.x, value.y);
}

SpriteShaderProgram::~SpriteShaderProgram() = default;