//
// Created by dzmitry on 29.11.2021.
//

#include "Sprite.hpp"

Sprite::Sprite( std::shared_ptr<Engine> engine, std::string_view filepath)
{
    node.value = std::make_shared<SpriteData>(engine, filepath);
}

void Sprite::draw()
{

}
