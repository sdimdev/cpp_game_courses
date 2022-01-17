//
// Created by dzmitry on 20.11.2021.
//

#ifndef GAME_WINDOWEVENTMANAGERIMPL_HPP
#define GAME_WINDOWEVENTMANAGERIMPL_HPP


#include <unordered_set>
#include <scenes/SceneManager.hpp>
#include <vector>
#include <list>
#include "common/IWindowEventManager.hpp"

class WindowEventManagerImpl : public IWindowEventManager
{
public:
    WindowEventManagerImpl() = default;

    void add(IEventListener const &listener) override;

    void remove(IEventListener const &listener) override;

    void add(IKeyboardKeyListener listener) override;

    void remove(IKeyboardKeyListener listener) override;

    void handleEvents() override;

    ~WindowEventManagerImpl() override = default;

private:
    std::list<IEventListener> listeners={};
    std::list<IKeyboardKeyListener> pressChangedListeners;
    std::unordered_set<KeyboardKey> pressed = {};
};


#endif //GAME_WINDOWEVENTMANAGERIMPL_HPP
