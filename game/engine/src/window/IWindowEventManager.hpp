//
// Created by dzmitry on 20.11.2021.
//

#ifndef GAME_IWINDOWEVENTMANAGER_HPP
#define GAME_IWINDOWEVENTMANAGER_HPP


#include <entity/event/WindowEvent.hpp>

class IWindowEventManager
{
public:
    virtual bool handleEvents() = 0;
    virtual ~IWindowEventManager();
};

#endif //GAME_IWINDOWEVENTMANAGER_HPP
