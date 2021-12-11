//
// Created by dzmitry on 19.11.2021.
//

#include "IWindowEvent.hpp"

SimpleWindowEvent::SimpleWindowEvent()
{
    this->eventType = UNKNOWN;
}

SimpleWindowEvent::SimpleWindowEvent(EventType type)
{
    this->eventType = type;
}

KeyboardEvent::KeyboardEvent(KeyboardKey key, KeyboardAction action)
{
    this->key = key;
    this->action = action;
}
