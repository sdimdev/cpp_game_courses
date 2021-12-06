//
// Created by dzmitry on 20.11.2021.
//

#ifndef GAME_WINDOWIMPL_HPP
#define GAME_WINDOWIMPL_HPP


#include <memory>
#include <SDL/renderer/SDLRenderer.hpp>
#include <common/renderer/IRenderer.hpp>
#include "common/window/IWindow.hpp"

class WindowImpl : public IWindow
{
public:
    WindowImpl(std::string_view window_name, int width, int height);

    ~WindowImpl() override;

    void close() override;

    std::shared_ptr<IRenderer> getRenderer() override;

private:
    struct Pimpl;
    std::unique_ptr<Pimpl> _pimpl;
};


#endif //GAME_WINDOWIMPL_HPP
