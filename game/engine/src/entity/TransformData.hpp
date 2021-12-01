//
// Created by dzmitry on 01.12.2021.
//

#ifndef GAME_TRANSFORMDATA_HPP
#define GAME_TRANSFORMDATA_HPP


#include <vec2.hpp>
#include <ext/matrix_float3x3.hpp>
#include "gtx/matrix_transform_2d.hpp"


class TransformData
{
public:
    glm::vec2 position;
    glm::vec2 size;
    glm::vec3 ancor;
    float rotation;
    float scale;

    glm::mat4 getTransform()
    {
        glm::mat3 trans(1.0f);
        trans = glm::translate(trans, position);
        trans = glm::scale(trans, glm::vec2(scale));
        trans = glm::rotate(trans, glm::radians(rotation));
        trans = glm::translate(trans, glm::vec2(ancor.x * size.x, ancor.y * size.y));
        return trans;
    }
};


#endif //GAME_TRANSFORMDATA_HPP
