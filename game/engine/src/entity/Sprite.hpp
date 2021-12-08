//
// Created by dzmitry on 29.11.2021.
//

#ifndef GAME_SPRITE_HPP
#define GAME_SPRITE_HPP


#include <vec2.hpp>
#include <engine/Engine.hpp>
#include "SpriteData.hpp"
#include <ext/matrix_float3x3.hpp>
#include "Node.hpp"

class Sprite
{
public:
    Sprite(std::shared_ptr<Engine> engine);

    std::shared_ptr<Node<SpriteData>> node = nullptr;

    void visit();

    void draw();

    glm::mat3 getTransform(std::shared_ptr<Node<SpriteData>> node);

    void drawSprite(std::shared_ptr<Node<SpriteData>> node);


private:
    std::shared_ptr<Engine> engine;
};


#endif //GAME_SPRITE_HPP
