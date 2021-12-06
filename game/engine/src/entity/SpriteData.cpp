//
// Created by dzmitry on 01.12.2021.
//

#include "SpriteData.hpp"
#include <bitmap/Bitmap.hpp>

SpriteData::SpriteData(std::shared_ptr<Engine> engine, std::string_view filepath)
{
    this->engine = std::move(engine);
    Bitmap bitmap(filepath);
    transformData.size = bitmap.getSize();

    MeshData meshData;

    meshData.points.emplace_back();
    meshData.points.back().position = {0.0, 0.0};
    meshData.points.back().textCoord = {0.0, 0.0};

    meshData.points.emplace_back();
    meshData.points.back().position = {0.0, bitmap.getSize().y};
    meshData.points.back().textCoord = {0.0, 1.0};

    meshData.points.emplace_back();
    meshData.points.back().position = {bitmap.getSize().x, bitmap.getSize().y};
    meshData.points.back().textCoord = {1.0, 1.0};

    meshData.points.emplace_back();
    meshData.points.back().position = {bitmap.getSize().x, 0.0};
    meshData.points.back().textCoord = {1.0, 0.0};

    meshData.indexes.emplace_back(0);
    meshData.indexes.emplace_back(2);
    meshData.indexes.emplace_back(3);

    meshData.indexes.emplace_back(0);
    meshData.indexes.emplace_back(1);
    meshData.indexes.emplace_back(2);

    vertexBuffer = engine->renderer()->createVertexBuffer(std::move(meshData));
    program = engine->renderer()->createProgram("draw");

    _textureUniform = program->createTextureUniform("uTexture");
    _textureUniform->texture = engine.renderer().createTexture(std::move(bitmap));

    _screenSizeUniform = program->createVec2Uniform("uScreenSize");
    _transformUniform = program->createMat3Uniform("uTransform");
}

void SpriteData::draw()
{
    const auto& win = _engine.window();
    _screenSizeUniform->value.x = win.getWidth();
    _screenSizeUniform->value.y = win.getHeight();
    _transformUniform->value = this->transformData.getTransform();

    Renderer::Command command;
    command.program = _program;
    command.vertexBuffer = _vertexBuffer;
    _engine.renderer().addCommand(std::move(command));
}
