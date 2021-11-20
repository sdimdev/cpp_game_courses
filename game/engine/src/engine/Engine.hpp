//
// Created by dzmitry on 17.11.2021.
//
#ifndef ENGINE_ENGINE_H
#define ENGINE_ENGINE_H

#include <string_view>
#include <memory>
#include <window/IWindow.hpp>
#include <renderer/IRenderer.hpp>
#include <scenes/SceneManager.hpp>

class Engine
{

public:
    explicit Engine(
            IWindow *window,
            IRenderer *renderer,
            SceneManager *sceneManager
    );

    ~Engine();

    bool isActive();

    void update();

private:
    struct Pimpl;
    std::unique_ptr<Pimpl> _pimpl;

   // bool showWindow(std::string_view window_name, int width, int height);

   // void initScene(int argc, char **argv);

    bool handleEvents();

    void drawScene();
};

#endif
