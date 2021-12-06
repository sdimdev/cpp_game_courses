//
// Created by dzmitry on 19.11.2021.
//

#include "EngineFactory.hpp"
#include <scenes/SceneManager.hpp>
#include <OpenGL/window/GL_Window.hpp>
#include "utils/CommandLineUtil.cpp"

Engine EngineFactory::create(std::string_view window_name, int width, int height, int argc, char **argv)
{
    IWindow *w = nullptr;
    w = new GL_Window(window_name, width, height);
    std::shared_ptr<IRenderer> renderer = w->getRenderer();
    return Engine(w, renderer);
}
