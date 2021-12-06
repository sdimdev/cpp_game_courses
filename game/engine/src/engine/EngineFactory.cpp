//
// Created by dzmitry on 19.11.2021.
//


#include "EngineFactory.hpp"
#include <SDL/window/WindowImpl.hpp>
#include <scenes/SceneManager.hpp>
#include <common/event/IWindowEventManager.hpp>
#include <SDL/event/WindowEventManagerImpl.hpp>
#include <OpenGL/window/GL_Window.hpp>
#include "utils/CommandLineUtil.cpp"

Engine EngineFactory::create(std::string_view window_name, int width, int height, int argc, char **argv)
{
    IWindow *w = nullptr;
    if (cmdOptionExists(argv, argv + argc, "-gl"))
    {
        w = new GL_Window(window_name, width, height);
    } else
    {
        w = new WindowImpl(window_name, width, height);
    }
    std::shared_ptr<IRenderer> renderer = w->getRenderer();
    return Engine(w, renderer);
}
