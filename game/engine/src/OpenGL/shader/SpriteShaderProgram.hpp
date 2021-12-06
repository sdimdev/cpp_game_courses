//
// Created by dzmitry on 04.12.2021.
//

#ifndef GAME_SPRITESHADERPROGRAM_HPP
#define GAME_SPRITESHADERPROGRAM_HPP


#include <memory>
#include <entity/TransformData.hpp>
#include "common/renderer/IShaderProgram.hpp"

class SpriteShaderProgram: public IShaderProgram
{
public:
    explicit SpriteShaderProgram();

    std::shared_ptr<TextureUniform> createTextureUniform(std::string_view name) override;
    std::shared_ptr<Mat3Uniform> createMat3Uniform(std::string_view name) override;
    std::shared_ptr<Vec2Uniform> createVec2Uniform(std::string_view name) override;

    void activate() override;

    int getProgram() override;
    void loadProgram() override;
    ~SpriteShaderProgram();
protected:
    std::vector<std::shared_ptr<Uniform>> uniforms;
private:
    struct Pimpl;
    std::unique_ptr<Pimpl> _pimpl;
};

class GlTextureUniform : public TextureUniform
{
public:
    explicit GlTextureUniform(const std::shared_ptr<SpriteShaderProgram>& program, std::string_view name);
    void activate() override;

private:
    int32_t _location;
};

class GlMat3Uniform : public Mat3Uniform
{
public:
    explicit GlMat3Uniform(const std::shared_ptr<SpriteShaderProgram>& program, std::string_view name);
    void activate() override;

private:
    int32_t _location;
};

class GlVec2Uniform : public Vec2Uniform
{
public:
    explicit GlVec2Uniform(const std::shared_ptr<SpriteShaderProgram>& program, std::string_view name);
    void activate() override;

private:
    int32_t _location;
};



#endif //GAME_SPRITESHADERPROGRAM_HPP
