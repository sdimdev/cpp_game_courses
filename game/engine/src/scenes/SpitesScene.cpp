//
// Created by dzmitry on 05.12.2021.
//

#include <cstdio>
#include "SpitesScene.hpp"

void SpritesScene::draw()
{
    this->sprite->draw();
}

bool SpritesScene::handleEvent(EventType eventType)
{
    return false;
}

SpritesScene::SpritesScene(std::shared_ptr<Engine> engine)
{
    this->engine = std::move(engine);
    this->sprite = std::make_shared<Sprite>(engine);
}

std::shared_ptr<Node<SpriteData>> SpritesScene::node()
{
    return sprite->node;
}

SpritesScene::~SpritesScene() = default;

