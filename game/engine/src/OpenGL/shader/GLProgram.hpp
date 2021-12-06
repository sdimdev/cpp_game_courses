//
// Created by dzmitry on 06.12.2021.
//

#ifndef GAME_GLProgram_HPP
#define GAME_GLProgram_HPP

#include <common/renderer/IShaderProgram.hpp>

class GLProgram : public IShaderProgram
{
public:
    GLProgram(const char* vs, const char* ps);
    ~GLProgram() = default;

    std::shared_ptr<TextureUniform> createTextureUniform(std::string_view name) override;
    std::shared_ptr<Mat3Uniform> createMat3Uniform(std::string_view name) override;
    std::shared_ptr<Vec2Uniform> createVec2Uniform(std::string_view name) override;

    void activate() override;

    uint32_t getProgramId() const {return program;}

protected:
    uint32_t vertexShader;
    uint32_t fragmentShader;
    uint32_t program;
};

class GlTextureUniform : public TextureUniform
{
public:
    explicit GlTextureUniform(const std::shared_ptr<GLProgram>& program, std::string_view name);
    void activate() override;

private:
    int32_t location;
};

class GlMat3Uniform : public Mat3Uniform
{
public:
    explicit GlMat3Uniform(const std::shared_ptr<GLProgram>& program, std::string_view name);
    void activate() override;

private:
    int32_t location;
};

class GlVec2Uniform : public Vec2Uniform
{
public:
    explicit GlVec2Uniform(const std::shared_ptr<GLProgram>& program, std::string_view name);
    void activate() override;

private:
    int32_t location;
}; 


#endif //GAME_GLProgram_HPP
