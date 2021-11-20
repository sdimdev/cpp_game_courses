//
// Created by dzmitry on 20.11.2021.
//

#include "SDLWindow.hpp"
#include <SDL.h>
#include <cassert>
#include <renderer/SDLRenderer.hpp>

struct SDLWindow::Pimpl
{
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
};

void SDLWindow::close()
{
    SDL_DestroyWindow(_pimpl->window);
    SDL_Quit();
}

SDLWindow::SDLWindow(std::string_view window_name, int width, int height) : IWindow()
{
    _pimpl = std::make_unique<SDLWindow::Pimpl>();
    bool success = true;
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        SDL_version version = {0, 0, 0};
        SDL_GetVersion(&version);
        printf("version %d.%d.%d\n", version.major, version.minor, version.patch);

        SDL_CreateWindowAndRenderer(width,
                                    height,
                                    0,
                                    &_pimpl->window,
                                    &_pimpl->renderer);
        if (_pimpl->window == nullptr)
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        } else
        {
            SDL_SetWindowTitle(_pimpl->window, std::string(window_name).c_str());
        }
    } else
    {
        printf("Window could not be created! SDL_Init return 0");
        success = false;
    }
    assert(success);

    //is it right?
    this->renderer = std::make_unique<SDLRenderer>(_pimpl->renderer);
}

IRenderer *SDLWindow::getRenderer()
{
    return this->renderer.get();
}

SDLWindow::~SDLWindow() = default;