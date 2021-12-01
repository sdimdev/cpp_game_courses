//
// Created by dzmitry on 01.12.2021.
//

#ifndef GAME_SPRITEDATA_HPP
#define GAME_SPRITEDATA_HPP


#include "TransformData.hpp"
#include "MeshData.hpp"

class SpriteData
{
public:
    TransformData transformData;

    GLuint VAO; //идентификатор вершин в видеокарте
    GLuint IBO; //идентификатор индексов в видеокарте
    //todo VBO
    MeshData meshData;
};


#endif //GAME_SPRITEDATA_HPP
