//
// Created by dzmitry on 01.12.2021.
//

#ifndef GAME_SPRITEDATA_HPP
#define GAME_SPRITEDATA_HPP


#include <memory>
#include <engine/Engine.hpp>
#include <common/IShaderProgram.hpp>
#include "TransformData.hpp"
#include "MeshData.hpp"
#include "IVertexBuffer.hpp"

class SpriteData
{
public:
    SpriteData(std::shared_ptr<Engine> engine, std::string_view filepath);

    ~SpriteData() = default;

    TransformData transformData;
    std::shared_ptr<IVertexBuffer> vertexBuffer;
    std::shared_ptr<IShaderProgram> program;

    std::shared_ptr<TextureUniform> textureUniform;
    std::shared_ptr<Vec2Uniform> screenSizeUniform;
    std::shared_ptr<Mat3Uniform> transformUniform;

private:
    std::shared_ptr<Engine> engine;
};


#endif //GAME_SPRITEDATA_HPP
