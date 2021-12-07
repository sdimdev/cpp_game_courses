//
// Created by dzmitry on 20.11.2021.
//

#include <entity/event/WindowEvent.hpp>
#include "WindowEventManagerImpl.hpp"
#include <SDL.h>
#include <scenes/IScene.hpp>
#include <cstdio>
#include <utility>

bool WindowEventManagerImpl::handleEvents()
{
    SDL_Event e;
    SDL_PollEvent(&e);
    EventType event;
    //WindowEvent* we;

    if (e.type == SDL_QUIT)
    {
        printf("QUIT in WEM\n");
        event = QUIT;
        // we = new WindowEvent(QUIT);
    } else
    {
        // printf("something WEM");
        // we = new WindowEvent();
    }
    bool handled = false;

    //printf("getScene");
    std::shared_ptr<IScene> scene = sceneManager->getScene();
    if (scene != nullptr)
    {
        //printf("scene->handleEvent");
        handled = scene->handleEvent(event);
    }
    //delete we;
    if (!handled && event == QUIT)
    {
        printf("return QUIT\n");
        return false;
    }
    //printf("return NOTHING");
    return true;
}

WindowEventManagerImpl::WindowEventManagerImpl(std::shared_ptr<SceneManager> sceneManager)
{
    this->sceneManager = std::move(sceneManager);
}
