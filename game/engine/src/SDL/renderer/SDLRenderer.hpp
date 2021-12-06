//
// Created by dzmitry on 19.11.2021.
//

#ifndef GAME_SDLRENDERER_HPP
#define GAME_SDLRENDERER_HPP


#include <memory>
#include "common/renderer/IRenderer.hpp"
#include "entity/RGBAColor.hpp"
#include <SDL.h>
#include <shader/IPixelShader.hpp>
#include <shader/IPoint3Shader.hpp>

class [[deprecated("Use GL_Renderer")]]SDLRenderer : public IRenderer
{
public:
    //is it right?
    explicit SDLRenderer(SDL_Renderer *renderer);

    ~SDLRenderer();

    void startDrawing() override;

    void endDrawing() override;

private:
    struct Pimpl;
    std::unique_ptr<Pimpl> _pimpl;

    void drawPoint(int x, int y, RGBAColor color);

    void drawLine(int x0, int y0, int x1, int y1, RGBAColor color, IPixelShader *pixelShader);
};


#endif //GAME_SDLRENDERER_HPP
