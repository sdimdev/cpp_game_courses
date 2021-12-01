//
// Created by dzmitry on 29.11.2021.
//

#ifndef GAME_SPRITE_HPP
#define GAME_SPRITE_HPP


#include <vec2.hpp>
#include "SpriteData.hpp"
#include "Node.hpp"

class Sprite
{
public:
    Node<SpriteData> node;


    /// glsl
    /// scaledPos = (transform * vec3(scalerdPOs, 1.0)).xy
    //transform через Uniform
};


#endif //GAME_SPRITE_HPP
