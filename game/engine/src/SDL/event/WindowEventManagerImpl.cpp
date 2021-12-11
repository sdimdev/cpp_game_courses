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
    }
    else if(e.type == SDL_KEYDOWN || e.type == SDL_KEYUP){
        KeyboardKey key;
        KeyboardAction action;
        if(e.type == SDL_KEYDOWN){
            action = DOWN;
        }
        else{
            action = UP;
        }
        switch (e.key.keysym.sym)
        {
            case SDLK_w:
                key = W;
                break;
            case SDLK_s:
                key = S;
                break;
        }
        windowEvent = std::make_shared<KeyboardEvent>(key, action);
    }
    else
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

