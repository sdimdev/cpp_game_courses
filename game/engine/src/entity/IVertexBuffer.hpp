//
// Created by dzmitry on 05.12.2021.
//

#ifndef GAME_IVERTEXBUFFER_HPP
#define GAME_IVERTEXBUFFER_HPP

#include "IShaderBuffer.hpp"

class IVertexBuffer//: public IShaderBuffer
{
public:
    virtual ~IVertexBuffer() = default;
    //virtual MeshData* getMesh() = 0;
};

#endif //GAME_IVERTEXBUFFER_HPP
