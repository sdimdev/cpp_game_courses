//
// Created by dzmitry on 19.11.2021.
//

#ifndef GAME_SDLRENDERER_HPP
#define GAME_SDLRENDERER_HPP


#include <memory>
#include "IRenderer.hpp"
#include <SDL.h>

class SDLRenderer : public IRenderer
{
public:
    //is it right?
    explicit SDLRenderer(SDL_Renderer *renderer);
    ~SDLRenderer();

    void startDrawing() override;

    void endDrawing() override;

    void drawLine(Line3f line, IPoint3Shader* shader) override;

private:
    struct Pimpl;
    std::unique_ptr<Pimpl> _pimpl;
};


#endif //GAME_SDLRENDERER_HPP
