//
// Created by dzmitry on 01.12.2021.
//

#ifndef GAME_SPRITEDATA_HPP
#define GAME_SPRITEDATA_HPP


#include <memory>
#include <engine/Engine.hpp>
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

    //todo move to vertexBuffer
    GLuint VAO; //идентификатор вершин в видеокарте
    GLuint IBO; //идентификатор индексов в видеокарте
    //todo VBO

    MeshData meshData;//todo remove it here
protected:
    void draw();

private:
    std::shared_ptr<Engine> engine;
};


#endif //GAME_SPRITEDATA_HPP
