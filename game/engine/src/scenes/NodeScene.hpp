//
// Created by dzmitry on 05.12.2021.
//

#ifndef GAME_SPRITESSCENE_HPP
#define GAME_SPRITESSCENE_HPP


#include <entity/Sprite.hpp>
#include "IScene.hpp"

class NodeScene : public IScene
{
public:
    std::shared_ptr<Node> value = nullptr;
    std::shared_ptr<Engine> engine = nullptr;

    explicit NodeScene(std::shared_ptr<Engine> engine);

    void draw() override;

    std::shared_ptr<Node> node();

    void setNode(std::shared_ptr<Node> node);

    bool handleEvent(EventType eventType) override;

    ~NodeScene() override;

private:
    void drawNode(std::shared_ptr<Node> node);
};


#endif //GAME_SPRITESSCENE_HPP
