//
// Created by dzmitry on 20.11.2021.
//

#ifndef GAME_IWINDOW_HPP
#define GAME_IWINDOW_HPP


#include <renderer/IRenderer.hpp>

class IWindow
{
public:
    virtual void close() = 0;
    virtual IRenderer *getRenderer() = 0;
    virtual ~IWindow() = 0;
};


#endif //GAME_IWINDOW_HPP
