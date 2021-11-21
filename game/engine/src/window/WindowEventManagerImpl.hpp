//
// Created by dzmitry on 20.11.2021.
//

#ifndef GAME_WINDOWEVENTMANAGERIMPL_HPP
#define GAME_WINDOWEVENTMANAGERIMPL_HPP


#include <scenes/SceneManager.hpp>
#include "IWindowEventManager.hpp"

class WindowEventManagerImpl : public IWindowEventManager
{
public:
    WindowEventManagerImpl(SceneManager *sceneManager);

    bool handleEvents() override;

    ~WindowEventManagerImpl() override = default;

private:
    SceneManager *sceneManager;
};


#endif //GAME_WINDOWEVENTMANAGERIMPL_HPP
