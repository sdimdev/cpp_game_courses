//
// Created by dzmitry on 20.11.2021.
//

#ifndef GAME_SDLWINDOW_HPP
#define GAME_SDLWINDOW_HPP


#include <memory>
#include <renderer/SDLRenderer.hpp>
#include "IWindow.hpp"

class SDLWindow: public IWindow
{
public:
    SDLWindow(std::string_view window_name, int width, int height);
    ~SDLWindow() override;
    void close() override;
    IRenderer *getRenderer() override;
private:
    struct Pimpl;
    std::unique_ptr<Pimpl> _pimpl;
    std::unique_ptr<SDLRenderer> renderer;
};


#endif //GAME_SDLWINDOW_HPP
