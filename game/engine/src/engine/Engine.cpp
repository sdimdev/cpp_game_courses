//
// Created by dzmitry on 17.11.2021.
//

#include <cstdio>
#include "Engine.hpp"
#include <SDL_version.h>
#include <SDL.h>
#include <scenes/ScenesFactory.hpp>
#include <window/IWindow.hpp>
#include <scenes/SceneManager.hpp>

struct Engine::Pimpl
{
    IWindow *window = nullptr;
    IRenderer *renderer = nullptr;
    SceneManager *sceneManager;
    bool quit = false;
};

/*
void Engine::init
{
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        _pimpl->quit = true;
    } else
    {
        bool shown = showWindow(window_name, width, height);
        if (shown)
        {
            initScene(argc, argv);
        }
        _pimpl->quit = !shown;
    }
}
*/

bool Engine::isActive()
{
    return !_pimpl->quit;
}

void Engine::update()
{
    if (handleEvents())
    {
        drawScene();
    }
}

Engine::Engine(
        IWindow *window,
        IRenderer *renderer,
        SceneManager *sceneManager
        )
{
    _pimpl = std::make_unique<Engine::Pimpl>();
    _pimpl->window = window;
    _pimpl->renderer = renderer;
}

/*void Engine::initScene(int argc, char **argv)
{
   *//* ScenesFactory factory{argc, argv};
    _pimpl->scene = factory.provideScene(_pimpl->renderer);*//*
}*/

void Engine::drawScene()
{
   // _pimpl->scene->draw();
}

bool Engine::handleEvents()
{
    if (_pimpl->quit)
    {
        return false;
    }

    SDL_Event e;
    SDL_PollEvent(&e);
    WindowEvent event;

    if (e.type == SDL_QUIT)
    {
        event = WindowEvent(QUIT);
    } else
    {
        event = WindowEvent();
    }

    bool handled = true;//_pimpl->scene->handleEvent(event);

    if (!handled && e.type == SDL_QUIT)
    {
        _pimpl->quit = true;
    }
    if (_pimpl->quit)
    {
        _pimpl->window->close();
        return false;
    }
    return true;
}

Engine::~Engine() = default;

