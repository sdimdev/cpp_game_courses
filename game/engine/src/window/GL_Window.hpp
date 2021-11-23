//
// Created by dzmitry on 22.11.2021.
//

#ifndef GAME_GL_WINDOW_HPP
#define GAME_GL_WINDOW_HPP


#include <memory>
#include "IWindow.hpp"

class GL_Window : public IWindow
{

public:
    GL_Window(std::string_view window_name, int width, int height);

    ~GL_Window() override;

    void close() override;

    IRenderer *getRenderer() override;

private:
    struct Pimpl;
    std::unique_ptr<Pimpl> _pimpl;
};


#endif //GAME_GL_WINDOW_HPP
