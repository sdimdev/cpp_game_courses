//
// Created by dzmitry on 01.12.2021.
//

#ifndef GAME_TRANSFORMDATA_HPP
#define GAME_TRANSFORMDATA_HPP


#include <vec2.hpp>
#include <ext/matrix_float3x3.hpp>
#include <optional>
#include "gtx/matrix_transform_2d.hpp"


class TransformData
{
public:
    std::optional<glm::mat3> transform;

    glm::vec2 position = {0.0f, 0.0f};
    glm::vec2 anchor = {0.0f, 0.0f};;
    float rotation = 0.0f;
    glm::vec2 scale = glm::vec2(1.0f);

    glm::vec2 size = {1.0f, 1.0f};

    glm::mat3 getTransform()
    {
        glm::mat3 trans(1.0f);
        trans = glm::translate(trans, position);
        trans = glm::scale(trans, glm::vec2(scale));
        trans = glm::rotate(trans, glm::radians(rotation));
        trans = glm::translate(trans, glm::vec2(anchor.x * size.x, anchor.y * size.y));
        return trans;
    }
};


#endif //GAME_TRANSFORMDATA_HPP
