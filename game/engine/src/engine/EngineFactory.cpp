//
// Created by dzmitry on 19.11.2021.
//


#include "EngineFactory.hpp"
#include <window/WindowImpl.hpp>
#include <scenes/SceneManager.hpp>
#include <window/IWindowEventManager.hpp>
#include <window/WindowEventManagerImpl.hpp>

Engine EngineFactory::create(std::string_view window_name, int width, int height, int argc, char **argv)
{
    IWindow *w = new WindowImpl(window_name, width, height);
    IRenderer *renderer = w->getRenderer();
    ScenesFactory *factory = new ScenesFactory(renderer, argc, argv);
    SceneManager *sceneManager = new SceneManager(factory);
    IWindowEventManager *evm = new WindowEventManagerImpl(sceneManager);
    return Engine(w, renderer, sceneManager, evm);
}
