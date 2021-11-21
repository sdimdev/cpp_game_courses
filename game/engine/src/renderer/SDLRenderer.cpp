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
    SDL_SetRenderDrawColor(_pimpl->renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(_pimpl->renderer);
    SDL_SetRenderDrawColor(_pimpl->renderer, 255, 0, 0, 200);
}

void SDLRenderer::endDrawing()
{
    SDL_RenderPresent(_pimpl->renderer);
}

void SDLRenderer::drawLine(Line3f line, IPoint3Shader *shader)
{
    Point3f p1 = line.getP1();
    Point3f p2 = line.getP2();
    if (shader != nullptr)
    {
        p1 = shader->apply(p1);
        p2 = shader->apply(p2);
    }
    SDL_RenderDrawLine(_pimpl->renderer,
                       (int) p1.getX(),
                       (int) p1.getY(),
                       (int) p2.getX(),
                       (int) p2.getY());
}

SDLRenderer::SDLRenderer(SDL_Renderer *renderer) : IRenderer()
{
    _pimpl = std::make_unique<SDLRenderer::Pimpl>();
    _pimpl->renderer = renderer;
}

SDLRenderer::~SDLRenderer() = default;
