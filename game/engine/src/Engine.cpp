//
// Created by dzmitry on 17.11.2021.
//

#include <cstdio>
#include "Engine.hpp"
#include <SDL_version.h>
#include <SDL.h>
#include <scenes/ScenesFactory.hpp>

struct Engine::Pimpl
{
    SDL_Window *window = nullptr;
    bool quit = false;
    std::unique_ptr<IScene> scene;
};

void Engine::init(std::string_view window_name, int width, int height, int argc, char **argv)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        _pimpl->quit = true;
    } else
    {
        SDL_version version = {0, 0, 0};
        SDL_GetVersion(&version);
        printf("version %d.%d.%d\n", version.major, version.minor, version.patch);

        bool shown = showWindow(window_name, width, height);
        if (shown)
        {
            initScene(argc, argv);
        }
        _pimpl->quit = !shown;
    }
}

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

Engine::Engine()
{
    _pimpl = std::make_unique<Engine::Pimpl>();
}

bool Engine::showWindow(std::string_view window_name, int width, int height)
{
    bool success = true;
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        _pimpl->window = SDL_CreateWindow(std::string(window_name).c_str(),
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          width,
                                          height,
                                          SDL_WINDOW_SHOWN);
        if (_pimpl->window == nullptr)
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        }
    } else
    {
        printf("Window could not be created! SDL_Init return 0");
        success = false;
    }
    return success;
}

void Engine::initScene(int argc, char **argv)
{
    ScenesFactory factory{argc, argv};
    _pimpl->scene = factory.provideScene(_pimpl->window);
}

void Engine::drawScene()
{
    _pimpl->scene->draw();
}

bool Engine::handleEvents()
{
    SDL_Event e;
    SDL_PollEvent(&e);
    if (e.type == SDL_QUIT)
    {
        _pimpl->quit = true;
    }

    if (_pimpl->quit)
    {
        SDL_DestroyWindow(_pimpl->window);
        SDL_Quit();
        return false;
    }
    return true;
}

Engine::~Engine() = default;

