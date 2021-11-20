//
// Created by dzmitry on 18.11.2021.
//

#include <domain/Line3f.hpp>
#include <domain/Point3f.hpp>
#include "LineScene.hpp"

void LineScene::draw()
{
    renderer->startDrawing();
    std::list<Line3f>::iterator it;
    for (it = lp.begin(); it != lp.end(); ++it)
        renderer->drawLine(*it);
    /*SDL_SetRenderDrawColor(_pimpl->renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(_pimpl->renderer);
    SDL_Rect rect;
    rect.w = 100;
    rect.h = 100;
    rect.x = 100;
    rect.y = 100;*/
    renderer->endDrawing();
/*    SDL_SetRenderDrawColor(_pimpl->renderer, 255, 0, 0, 200);
    SDL_RenderDrawRect(_pimpl->renderer, &rect);
    SDL_RenderPresent(_pimpl->renderer);*/
}

bool LineScene::handleEvent(WindowEvent event)
{
    return false;
}

LineScene::LineScene(IRenderer *renderer)
{
    this->renderer = renderer;
    int lastI = 0;
    int lastJ = 0;
    for (int i = 0; i < 400; i += 20)
    {
        if (i != 0)
            for (int j = 0; j < 400; j += 20)
            {
                if (j != 0)
                {
                    lp.push_back(Line3f(
                            Point3f(i, j),
                            Point3f(lastI, lastJ)
                    ));
                }
                lastJ = j;
            }
        lastI = i;
    }
    /*  SDL_RendererInfo info;
      SDL_GetRendererInfo(_pimpl->renderer, &info);
      printf(info.name);*/
}

LineScene::~LineScene()
{
    /*SDL_DestroyRenderer(_pimpl->renderer);*/
}
