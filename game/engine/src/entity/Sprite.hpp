//
// Created by dzmitry on 29.11.2021.
//

#ifndef GAME_SPRITE_HPP
#define GAME_SPRITE_HPP


#include <vec2.hpp>
#include <engine/Engine.hpp>
#include "SpriteData.hpp"
#include "Node.hpp"

class Sprite
{
public:
    Sprite(const Engine& engine, std::string_view filepath);
    Node<SpriteData> node{};
    void draw();
private:
    const Engine& _engine;
};


#endif //GAME_SPRITE_HPP
