//
// Created by dzmitry on 20.11.2021.
//

#ifndef GAME_IWINDOWEVENTMANAGER_HPP
#define GAME_IWINDOWEVENTMANAGER_HPP


#include <entity/event/IWindowEvent.hpp>
#include <functional>
#include <random>
#include "IKeyboardKeyListener.hpp"

class IWindowEventManager
{
public:
    using IEventListener = std::function<bool(std::shared_ptr<IWindowEvent>)>;
    //using KeyPressChangedListener = std::function<bool(KeyboardKey, bool)>;
    virtual void add(IEventListener const&listener) = 0;
    virtual void remove(IEventListener const&listener)  = 0;
    virtual void add(IKeyboardKeyListener listener) = 0;
    virtual void remove(IKeyboardKeyListener listener)  = 0;
    //return false if need to close app
    virtual void handleEvents() = 0;
    virtual ~IWindowEventManager() = default;
};

#endif //GAME_IWINDOWEVENTMANAGER_HPP
