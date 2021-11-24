//
// Created by dzmitry on 22.11.2021.
//

#include "GL_Window.hpp"
#include "IWindow.hpp"
#include <SDL.h>
#include <cassert>
#include <renderer/SDLRenderer.hpp>
#include <renderer/GL_Renderer.hpp>

struct GL_Window::Pimpl
{
    SDL_Window *window = nullptr;
    IRenderer *r = nullptr;
};

void GL_Window::close()
{
    printf("close");
    SDL_DestroyWindow(_pimpl->window);
    SDL_Quit();
}

GL_Window::GL_Window(std::string_view window_name, int width, int height)
{
    _pimpl = std::make_unique<GL_Window::Pimpl>();
    bool success = true;
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        SDL_version version = {0, 0, 0};
        SDL_GetVersion(&version);
        printf("version %d.%d.%d\n", version.major, version.minor, version.patch);

        _pimpl->window = SDL_CreateWindow(window_name.data(),
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          width,
                                          height,
                                          SDL_WINDOW_OPENGL);
        if (_pimpl->window == nullptr)
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        }
    } else
    {
        printf("Window could not be created! SDL_Init return 0\n");
        success = false;
    }
    assert(success);
    _pimpl->r = new GL_Renderer(_pimpl->window);
}

IRenderer *GL_Window::getRenderer()
{
    return _pimpl->r;
}

GL_Window::~GL_Window()
{
   // SDL_DestroyRenderer(_pimpl->renderer);
};