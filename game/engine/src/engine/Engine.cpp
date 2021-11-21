//
// Created by dzmitry on 17.11.2021.
//

#include "Engine.hpp"
#include <scenes/ScenesFactory.hpp>
#include <window/IWindow.hpp>
#include <scenes/SceneManager.hpp>
#include <window/IWindowEventManager.hpp>

struct Engine::Pimpl
{
    IWindow *window = nullptr;
    IRenderer *renderer = nullptr;
    IWindowEventManager *windowEventManager = nullptr;
    SceneManager *sceneManager = nullptr;
    bool active = true;
};

bool Engine::isActive()
{
    return _pimpl->active;
}

void Engine::update()
{
    if (handleEvents())
    {
        _pimpl->sceneManager->drawScene();
    }
}

Engine::Engine(
        IWindow *window,
        IRenderer *renderer,
        SceneManager *sceneManager,
        IWindowEventManager *windowEventManager)
{
    printf("creating\n");
    _pimpl = std::make_unique<Engine::Pimpl>();
    _pimpl->window = window;
    _pimpl->renderer = renderer;
    _pimpl->sceneManager = sceneManager;
    _pimpl->windowEventManager = windowEventManager;
}

bool Engine::handleEvents()
{
    if (!_pimpl->active)
    {
        printf("DEACTIVATED\n");
        return false;
    }
    _pimpl->active = _pimpl->windowEventManager->handleEvents();
    //printf("handled\n");
    if (!_pimpl->active)
    {
        printf("try to close\n");
//        _pimpl->active = false;
        _pimpl->window->close();
        return false;
    }
    return true;
}

Engine::~Engine() = default;

