//
// Created by dzmitry on 19.11.2021.
//


#include "EngineFactory.hpp"
#include <window/SDLWindow.hpp>

Engine EngineFactory::create(std::string_view window_name, int width, int height, int argc, char **argv)
{
    IWindow *w = new SDLWindow(window_name, width, height);
    SceneManager sceneManager;
    return Engine(w, w->getRenderer(), &sceneManager);
}
