//
// Created by dzmitry on 29.11.2021.
//

#ifndef GAME_SPRITE_HPP
#define GAME_SPRITE_HPP


#include <vec2.hpp>

class Sprite
{
    //todo to mesh
public:
    glm::vec2 position;
    std::uint32_t rotation;
    float scale;

    //todo вставь в Node
    /// glsl
    /// scaledPos = (transform * vec3(scalerdPOs, 1.0)).xy
    //transform через Uniform

    //vec2 - якорная точка. Вокруг которой происходят все тран ancrPoint

 /*   s cos - sin + tx
    sin + s cos + ty
    0 0 1*/
};


#endif //GAME_SPRITE_HPP
