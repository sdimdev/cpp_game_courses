//
// Created by dzmitry on 05.12.2021.
//

#ifndef GAME_VERTEXBUFFER_HPP
#define GAME_VERTEXBUFFER_HPP


#include <entity/IVertexBuffer.hpp>
#include <engine/Engine.hpp>
#include <entity/MeshData.hpp>

class VertexBuffer final : public IVertexBuffer
{
public:
    explicit VertexBuffer(const Engine& engine,
                            MeshData data);

    virtual ~VertexBuffer();

    void draw();

private:
    uint32_t _VAO = 0;
    uint32_t _VBO = 0;
    uint32_t _IBO = 0;

    uint32_t _count;

    const Engine& _engine;
};


#endif //GAME_VERTEXBUFFER_HPP
