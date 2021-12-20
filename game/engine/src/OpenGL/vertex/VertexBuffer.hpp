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
    explicit VertexBuffer(MeshData data);

    virtual ~VertexBuffer();

    void draw();

   // MeshData* getMesh() override;

private:
    uint32_t _VAO = 0;
    uint32_t _VBO = 0;
    uint32_t _IBO = 0;

    uint32_t _count;

    struct Pimpl;
    std::shared_ptr<Pimpl> _pimpl;

};


#endif //GAME_VERTEXBUFFER_HPP
