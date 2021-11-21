//
// Created by dzmitry on 20.11.2021.
//

#include "WindowImpl.hpp"
#include "IWindow.hpp"
#include <SDL.h>
#include <cassert>
#include <renderer/SDLRenderer.hpp>

struct WindowImpl::Pimpl
{
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    SDLRenderer *r = nullptr;
};

void WindowImpl::close()
{
    printf("close");
    SDL_DestroyWindow(_pimpl->window);
    SDL_Quit();
}

WindowImpl::WindowImpl(std::string_view window_name, int width, int height)
{
    _pimpl = std::make_unique<WindowImpl::Pimpl>();
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
            printf("set Title %s\n", window_name.data());
            SDL_SetWindowTitle(_pimpl->window, window_name.data());
        }
    } else
    {
        printf("Window could not be created! SDL_Init return 0\n");
        success = false;
    }
    assert(success);
    _pimpl->r = new SDLRenderer(_pimpl->renderer);
}

IRenderer *WindowImpl::getRenderer()
{
    return _pimpl->r;
}

WindowImpl::~WindowImpl()  {
    SDL_DestroyRenderer(_pimpl->renderer);
};