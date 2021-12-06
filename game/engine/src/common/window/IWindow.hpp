//
// Created by dzmitry on 20.11.2021.
//

#ifndef GAME_IWINDOW_HPP
#define GAME_IWINDOW_HPP


#include <common/renderer/IRenderer.hpp>

class IWindow
{
public:
    virtual void close() = 0;
    virtual std::shared_ptr<IRenderer> getRenderer() = 0;
    virtual ~IWindow() = default;
};


#endif //GAME_IWINDOW_HPP
