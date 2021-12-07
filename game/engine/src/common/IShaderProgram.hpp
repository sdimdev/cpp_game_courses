//
// Created by dzmitry on 04.12.2021.
//

#ifndef GAME_ISHADERPROGRAM_HPP
#define GAME_ISHADERPROGRAM_HPP

#include <memory>
#include <vector>
#include <string_view>
#include <ext/matrix_float3x3.hpp>
#include "ITexture.hpp"

class Uniform
{
public:
    virtual void activate() = 0;

    virtual ~Uniform() = default;
};

class TextureUniform : public Uniform
{
public:
    std::shared_ptr<ITexture> texture;
};

class Mat3Uniform : public Uniform
{
public:
    glm::mat3 value;
};

class Vec2Uniform : public Uniform
{
public:
    glm::vec2 value;
};

class IShaderProgram : public std::enable_shared_from_this<IShaderProgram>
{
public:
    virtual uint32_t getProgram() = 0;

    virtual void activate();

    virtual std::shared_ptr<TextureUniform> createTextureUniform(std::string_view name) = 0;

    virtual std::shared_ptr<Mat3Uniform> createMat3Uniform(std::string_view name) = 0;

    virtual std::shared_ptr<Vec2Uniform> createVec2Uniform(std::string_view name) = 0;

protected:
    std::vector<std::shared_ptr<Uniform>> _uniforms;
};

inline void IShaderProgram::activate()
{
    for (const auto &uniform: _uniforms)
    {
        uniform->activate();
    }
}

#endif //GAME_ISHADERPROGRAM_HPP
