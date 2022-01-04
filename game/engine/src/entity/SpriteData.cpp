//
// Created by dzmitry on 01.12.2021.
//

#include "SpriteData.hpp"
#include <bitmap/Bitmap.hpp>
#include <utils/GLUtils.cpp>

SpriteData::SpriteData(std::shared_ptr<Engine> engine, std::string_view filepath)
{
    this->engine = engine;
    Bitmap bitmap(filepath);
    transform.size = bitmap.getSize();

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


    vertexBuffer = this->engine->renderer()->createVertexBuffer(std::move(meshData));
    checkErrors(__FILE__, __LINE__);
    program = this->engine->renderer()->createProgram("");
    checkErrors(__FILE__, __LINE__);
    textureUniform = program->createTextureUniform("uTexture");
    checkErrors(__FILE__, __LINE__);
    textureUniform->texture = this->engine->renderer()->createTexture(std::move(bitmap));
    checkErrors(__FILE__, __LINE__);
    screenSizeUniform = program->createVec2Uniform("screenSize");
    transformUniform = program->createMat3Uniform("transform");
    checkErrors(__FILE__, __LINE__);
}

/*void SpriteData::draw()
{
    const auto &win = engine->window();
    screenSizeUniform->value.x = win->getWidth();
    screenSizeUniform->value.y = win->getHeight();
    transformUniform->value = this->transformData.getTransform();

    IRenderer::Command command;
    command.program = program;
    command.vertexBuffer = vertexBuffer;
    engine->renderer()->addCommand(std::move(command));
}*/
