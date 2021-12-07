//
// Created by dzmitry on 29.11.2021.
//

#ifndef GAME_MESHDATA_HPP
#define GAME_MESHDATA_HPP


#include <vector>
#include "Vertex.hpp"

class MeshData
{
public:
    std::vector<Vertex> points;
    std::vector<uint32_t> indexes;
};


#endif //GAME_MESHDATA_HPP
