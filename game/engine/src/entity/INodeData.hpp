//
// Created by dzmitry on 03.01.2022.
//

#ifndef GAME_INODEDATA_HPP
#define GAME_INODEDATA_HPP


#include "TransformData.hpp"

class INodeData
{
public :
    explicit INodeData()= default;

    virtual ~INodeData() = default;

    TransformData transform;
};


#endif //GAME_INODEDATA_HPP
