//
// Created by dzmitry on 17.11.2021.
//

#include "Engine.hpp"
#include "utils/TimeInteractor.hpp"
#include "res/ResourcesManager.hpp"
#include "common/Scheduler.hpp"
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
    std::shared_ptr<ResourcesManager> resourcesManager = nullptr;
    std::shared_ptr<IWindowEventManager> windowEventManager = nullptr;
    std::shared_ptr<SceneManager> sceneManager = nullptr;
    std::shared_ptr<Scheduler> scheduler = nullptr;
    bool active = true;
    TimeInteractor timeInteractor;
    int64_t tickTime;
    bool isFrame;
};

bool Engine::isActive()
{
    return _pimpl->active;
}

void setActive();

void Engine::setActive()
{
    _pimpl->active = false;
}


void Engine::update()
{
    _pimpl->timeInteractor.tick(&_pimpl->tickTime, &_pimpl->isFrame);
    _pimpl->scheduler->visit();
    if (handleEvents())
    {
        if (_pimpl->isFrame)
        {
            _pimpl->sceneManager->drawScene();
            _pimpl->renderer->startDrawing();
            _pimpl->renderer->draw();
            _pimpl->renderer->endDrawing();
        }
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
    std::shared_ptr<IWindowEventManager> evm = std::make_shared<WindowEventManagerImpl>();
    _pimpl->sceneManager = sceneManager;
    _pimpl->scheduler = std::make_shared<Scheduler>();
    _pimpl->windowEventManager = evm;
    _pimpl->resourcesManager = std::make_shared<ResourcesManager>();
    _pimpl->windowEventManager->add(
            [&](std::shared_ptr<IWindowEvent> event)
            {
                auto simpleEvent = std::dynamic_pointer_cast<SimpleWindowEvent>(event);
                if (simpleEvent && simpleEvent->eventType == QUIT)
                {
                    _pimpl->active = false;
                    return true;
                }
                return false;
            });
}

bool Engine::handleEvents()
{
    if (!_pimpl->active)
    {
        printf("DEACTIVATED\n");
        return false;
    }
    _pimpl->windowEventManager->handleEvents();
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

std::shared_ptr<IResourcesManager> Engine::resources()
{
    return _pimpl->resourcesManager;
}

std::shared_ptr<IWindowEventManager> Engine::eventManager()
{
    return _pimpl->windowEventManager;
}

std::shared_ptr<Scheduler> Engine::scheduler()
{
    return _pimpl->scheduler;
}

std::shared_ptr<IWindow> Engine::window()
{
    return _pimpl->window;
}

Engine::~Engine() = default;

