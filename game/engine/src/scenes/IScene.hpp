//
// Created by dzmitry on 18.11.2021.
//

#ifndef GAME_SCENE_HPP
#define GAME_SCENE_HPP

#include <entity/event/IWindowEvent.hpp>

class IScene
{
public:
    virtual ~IScene() = default;
    virtual void draw() = 0;
    virtual bool handleEvent(EventType eventType) = 0;
};


#endif //GAME_SCENE_HPP
