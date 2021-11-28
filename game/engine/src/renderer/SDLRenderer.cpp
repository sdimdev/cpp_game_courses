//
// Created by dzmitry on 19.11.2021.
//

#include <SDL.h>
#include <entity/RGBAColor.hpp>
#include <shader/IPixelShader.hpp>
#include <shader/IPoint3Shader.hpp>
#include "SDLRenderer.hpp"

struct SDLRenderer::Pimpl
{
    SDL_Renderer *renderer = nullptr;
};

void SDLRenderer::startDrawing()
{
    SDL_SetRenderDrawColor(_pimpl->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(_pimpl->renderer);
}

void SDLRenderer::endDrawing()
{
    SDL_RenderPresent(_pimpl->renderer);
}

void SDLRenderer::drawLine(Line3f line, IPoint3Shader *shader, IPixelShader *pixelShader)
{
    Point3f p1 = line.getP1();
    Point3f p2 = line.getP2();
    RGBAColor c(0, 255, 0, 255);
    if (shader != nullptr)
    {
        p1 = shader->apply(p1);
        p2 = shader->apply(p2);
    }
    //SDL_SetRenderDrawColor(_pimpl->renderer, 255, 0, 0, 200);
    /*  SDL_RenderDrawLine(_pimpl->renderer,
                         (int) p1.getX(),
                         (int) p1.getY(),
                         (int) p2.getX(),
                         (int) p2.getY());*/

    drawLine((int) p1.getX(),
             (int) p1.getY(),
             (int) p2.getX(),
             (int) p2.getY(),
             c,
             pixelShader);
}

SDLRenderer::SDLRenderer(SDL_Renderer *renderer) : IRenderer()
{
    _pimpl = std::make_unique<SDLRenderer::Pimpl>();
    _pimpl->renderer = renderer;
}

SDLRenderer::~SDLRenderer() = default;

void SDLRenderer::drawPoint(int x, int y, RGBAColor color)
{
    SDL_SetRenderDrawColor(_pimpl->renderer, color.getRed(), color.getGreen(), color.getBlue(), color.getAlpha());
    SDL_RenderDrawPoint(_pimpl->renderer, x, y);
}

void SDLRenderer::drawLine(int x0, int y0, int x1, int y1, RGBAColor color, IPixelShader *pixelShader)
{
    //copied from https://habr.com/ru/post/248153/
    RGBAColor c = color;
    bool steep = false;
    if (std::abs(x0 - x1) < std::abs(y0 - y1))
    {
        std::swap(x0, y0);
        std::swap(x1, y1);
        steep = true;
    }
    if (x0 > x1)
    {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }
    //todo do not create it each time?
    int dx = x1 - x0;
    int dy = y1 - y0;
    int derror2 = std::abs(dy) * 2;
    int error2 = 0;
    int y = y0;
    for (int x = x0; x <= x1; x++)
    {
        if (steep)
        {
            if (pixelShader != nullptr)
            {
                //todo point2d
                c = pixelShader->apply(Point3f(y, x), color);
            }
            drawPoint(y, x, c);
        } else
        {
            if (pixelShader != nullptr)
            {
                //todo point2d
                c = pixelShader->apply(Point3f(x, y), color);
            }
            drawPoint(x, y, c);
        }
        error2 += derror2;

        if (error2 > dx)
        {
            y += (y1 > y0 ? 1 : -1);
            error2 -= dx * 2;
        }
    }
}
