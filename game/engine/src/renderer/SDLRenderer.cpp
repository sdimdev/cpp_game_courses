//
// Created by dzmitry on 19.11.2021.
//

#include <SDL.h>
#include "SDLRenderer.hpp"

struct SDLRenderer::Pimpl
{
    SDL_Renderer *renderer = nullptr;
};

void SDLRenderer::startDrawing()
{

}

void SDLRenderer::endDrawing()
{

}

void SDLRenderer::drawLine(Line3f line)
{

}

SDLRenderer::SDLRenderer(SDL_Renderer *renderer)
{
    _pimpl->renderer= renderer;
}
