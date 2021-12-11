//
// Created by dzmitry on 20.11.2021.
//

#include <entity/event/IWindowEvent.hpp>
#include "WindowEventManagerImpl.hpp"
#include <SDL.h>
#include <scenes/IScene.hpp>
#include <cstdio>
#include <utility>

void WindowEventManagerImpl::handleEvents()
{
    SDL_Event e;
    SDL_PollEvent(&e);

    std::shared_ptr<IWindowEvent> windowEvent = nullptr;
    if (e.type == SDL_QUIT)
    {
        printf("QUIT in WEM\n");
        windowEvent = std::make_shared<SimpleWindowEvent>(QUIT);
    } else
    {
        windowEvent = std::make_shared<SimpleWindowEvent>(UNKNOWN);
        // printf("something WEM");
        // we = new WindowEvent();
    }

    for (const auto &listener: listeners)
    {
        if (listener(windowEvent))
        {
            break;
        }
    }
}

void WindowEventManagerImpl::add(const IWindowEventManager::IEventListener &listener)
{
    listeners.push_back(listener);
}

void WindowEventManagerImpl::remove(const IWindowEventManager::IEventListener &listener)
{
    //todo
}

