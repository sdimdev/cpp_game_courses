//
// Created by dzmitry on 05.12.2021.
//

#ifndef GAME_SPRITESSCENE_HPP
#define GAME_SPRITESSCENE_HPP


#include <entity/Sprite.hpp>
#include "IScene.hpp"

class SpritesScene : public IScene
{
public:
    std::shared_ptr<Sprite> sprite = nullptr;
    std::shared_ptr<Engine> engine = nullptr;
    explicit SpritesScene(std::shared_ptr<Engine> engine);
    void draw() override;
    std::shared_ptr<Node<SpriteData>> node();
    bool handleEvent(EventType eventType) override;
    ~SpritesScene() override;
};


#endif //GAME_SPRITESSCENE_HPP
