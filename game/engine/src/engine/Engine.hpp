//
// Created by dzmitry on 17.11.2021.
//
#ifndef ENGINE_ENGINE_H
#define ENGINE_ENGINE_H

#include <string_view>
#include <memory>
#include <common/window/IWindow.hpp>
#include <common/renderer/IRenderer.hpp>
#include <scenes/SceneManager.hpp>
#include <common/event/IWindowEventManager.hpp>

class Engine
{

public:
    explicit Engine(
            IWindow *window,
            IRenderer *renderer,
            SceneManager *sceneManager,
            IWindowEventManager *windowEventManager
            );

    ~Engine();

    bool isActive();

    void update();

private:
    struct Pimpl;
    std::unique_ptr<Pimpl> _pimpl;
    bool handleEvents();
};

#endif
