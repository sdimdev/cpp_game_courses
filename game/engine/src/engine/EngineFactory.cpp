//
// Created by dzmitry on 19.11.2021.
//

#include "EngineFactory.hpp"
#include <scenes/SceneManager.hpp>
#include <OpenGL/window/GL_Window.hpp>
#include "utils/CommandLineUtil.cpp"

std::shared_ptr<Engine>
EngineFactory::create(std::string_view window_name, int width, int height, int argc, char **argv)
{
    std::shared_ptr<IWindow> w = nullptr;
    w = std::make_unique<GL_Window>(window_name, width, height);
    std::shared_ptr<IRenderer> renderer = w->getRenderer();
    return std::make_shared<Engine>(w, renderer);
}
