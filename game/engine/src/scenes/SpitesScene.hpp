//
// Created by dzmitry on 05.12.2021.
//

#ifndef GAME_SPRITESSCENE_HPP
#define GAME_SPRITESSCENE_HPP


#include "IScene.hpp"

class SpritesScene : public IScene
{
public:
    explicit SpritesScene();
    void draw() override;
    bool handleEvent(EventType eventType) override;
    ~SpritesScene() override;
};


#endif //GAME_SPRITESSCENE_HPP
