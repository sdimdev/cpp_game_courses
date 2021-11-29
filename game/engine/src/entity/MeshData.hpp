//
// Created by dzmitry on 29.11.2021.
//

#ifndef GAME_MESHDATA_HPP
#define GAME_MESHDATA_HPP


#include <vector>
#include <SDL_opengl.h>
#include "Vertex.hpp"

class MeshData
{
public:
    std::vector<Vertex> points;
    std::vector<GLint> indexes;
};


#endif //GAME_MESHDATA_HPP
