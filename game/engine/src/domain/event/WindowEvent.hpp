//
// Created by dzmitry on 19.11.2021.
//

#ifndef GAME_WINDOWEVENT_HPP
#define GAME_WINDOWEVENT_HPP


#include "EventType.hpp"


enum EventType
{
    QUIT, UNKNOWN
};

class WindowEvent
{
public:
    WindowEvent();
    WindowEvent(EventType type);
};


#endif //GAME_WINDOWEVENT_HPP
