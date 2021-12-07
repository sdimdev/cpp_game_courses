//
// Created by dzmitry on 20.11.2021.
//

#ifndef GAME_WINDOWEVENTMANAGERIMPL_HPP
#define GAME_WINDOWEVENTMANAGERIMPL_HPP


#include <scenes/SceneManager.hpp>
#include "common/IWindowEventManager.hpp"

class WindowEventManagerImpl : public IWindowEventManager
{
public:
    WindowEventManagerImpl(std::shared_ptr<SceneManager> sceneManager);

    bool handleEvents() override;

    ~WindowEventManagerImpl() override = default;

private:
    std::shared_ptr<SceneManager> sceneManager;
};


#endif //GAME_WINDOWEVENTMANAGERIMPL_HPP
