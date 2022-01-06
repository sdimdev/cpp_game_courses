//
// Created by dzmitry on 17.11.2021.
//
#ifndef ENGINE_ENGINE_H
#define ENGINE_ENGINE_H

#include <string_view>
#include <memory>
#include <common/IWindow.hpp>
#include <common/IRenderer.hpp>
#include <scenes/SceneManager.hpp>
#include <common/IWindowEventManager.hpp>
#include "common/IResourcesManager.hpp"

//todo remove or change it to settings
const static bool logDebug = false;

//todo remove or change it to settings
static void logMessage(char* message)
{
    if(logDebug)
        printf("%s\n", message);
}
class Engine : public std::enable_shared_from_this<Engine>
{

public:


    explicit Engine(
            std::shared_ptr<IWindow> window,
            std::shared_ptr<IRenderer> renderer
    );

    ~Engine();

    std::shared_ptr<SceneManager> sceneManager();

    bool isActive();
    void setActive();

    void update();

    std::shared_ptr<IRenderer> renderer();

    std::shared_ptr<IResourcesManager> resources();

    std::shared_ptr<IWindowEventManager> eventManager();

    std::shared_ptr<IWindow> window();

private:
    struct Pimpl;
    std::unique_ptr<Pimpl> _pimpl;

    bool handleEvents();
};

#endif
