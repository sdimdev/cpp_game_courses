//
// Created by dzmitry on 20.11.2021.
//

#ifndef GAME_WINDOWEVENTMANAGERIMPL_HPP
#define GAME_WINDOWEVENTMANAGERIMPL_HPP


#include <scenes/SceneManager.hpp>
#include <vector>
#include "common/IWindowEventManager.hpp"

class WindowEventManagerImpl : public IWindowEventManager
{
public:
    WindowEventManagerImpl() = default;

    void add(IEventListener const &listener) override;

    void remove(IEventListener const &listener) override;

    void handleEvents() override;

    ~WindowEventManagerImpl() override = default;

private:
    std::vector<IEventListener> listeners;
};


#endif //GAME_WINDOWEVENTMANAGERIMPL_HPP
