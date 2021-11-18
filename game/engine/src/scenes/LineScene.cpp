//
// Created by dzmitry on 18.11.2021.
//

#include <SDL_render.h>
#include "LineScene.hpp"

struct LineScene::Pimpl
{
    SDL_Renderer *renderer = NULL;
};

void LineScene::draw()
{
    SDL_SetRenderDrawColor(_pimpl->renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(_pimpl->renderer);
 /*   SDL_SetRenderDrawColor(_pimpl->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_SetRenderDrawBlendMode(_pimpl->renderer, SDL_BLENDMODE_ADD);
    SDL_RenderDrawLine(_pimpl->renderer, 120, 0, 100, 40);
    SDL_RenderDrawLine(_pimpl->renderer, 100, 40, 140, 40);
    SDL_RenderDrawLine(_pimpl->renderer, 140, 40, 120, 0);*/
    // SDL_RenderPresent(_pimpl->renderer);
}

LineScene::LineScene(SDL_Window *window)
{
    _pimpl = std::make_unique<LineScene::Pimpl>();
    //_pimpl->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    _pimpl->renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_RendererInfo info;
    SDL_GetRendererInfo(_pimpl->renderer, &info);
    printf(info.name);
}

LineScene::~LineScene()
{
    SDL_DestroyRenderer(_pimpl->renderer);
};
