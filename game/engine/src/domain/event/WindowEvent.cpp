//
// Created by dzmitry on 19.11.2021.
//

#include "WindowEvent.hpp"

WindowEvent::WindowEvent() : WindowEvent(UNKNOWN)
{}

WindowEvent::WindowEvent(EventType type)
{
    eventType = type;
}
