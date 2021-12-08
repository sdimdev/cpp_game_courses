//
// Created by dzmitry on 17.11.2021.
//

#include "Engine.hpp"
#include <scenes/ScenesFactory.hpp>
#include <common/IWindow.hpp>
#include <scenes/SceneManager.hpp>
#include <common/IWindowEventManager.hpp>
#include <utility>
#include <SDL/event/WindowEventManagerImpl.hpp>

struct Engine::Pimpl
{
    std::shared_ptr<IWindow> window = nullptr;
    std::shared_ptr<IRenderer> renderer = nullptr;
    std::shared_ptr<IWindowEventManager> windowEventManager = nullptr;
    std::shared_ptr<SceneManager> sceneManager = nullptr;
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
        _pimpl->renderer->draw();
    }
}

Engine::Engine(
        std::shared_ptr<IWindow> window,
        std::shared_ptr<IRenderer> renderer)
{
    printf("creating\n");
    _pimpl = std::make_unique<Engine::Pimpl>();
    _pimpl->window = window;
    _pimpl->renderer = renderer;
    std::shared_ptr<SceneManager> sceneManager = std::make_shared<SceneManager>();
    std::shared_ptr<IWindowEventManager> evm = std::make_shared<WindowEventManagerImpl>(sceneManager);
    _pimpl->sceneManager = sceneManager;
    _pimpl->windowEventManager = evm;
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

std::shared_ptr<SceneManager> Engine::sceneManager()
{
    return _pimpl->sceneManager;
}

std::shared_ptr<IRenderer> Engine::renderer()
{
    return _pimpl->renderer;
}

std::shared_ptr<IWindowEventManager> Engine::eventManager()
{
    return _pimpl->windowEventManager;
}

std::shared_ptr<IWindow> Engine::window()
{
    return _pimpl->window;
}

Engine::~Engine() = default;

