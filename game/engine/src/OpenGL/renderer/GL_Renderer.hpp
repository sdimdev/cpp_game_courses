//
// Created by dzmitry on 22.11.2021.
//

#ifndef GAME_GL_RENDERER_HPP
#define GAME_GL_RENDERER_HPP


#include <OpenGL/window/GL_Window.hpp>
#include "common/renderer/IRenderer.hpp"
#include <SDL.h>

class GL_Renderer : public IRenderer
{
public:
    //is it right?
    explicit GL_Renderer(SDL_Window *sdlWindow, int w, int h);

    ~GL_Renderer();

    void startDrawing() override;

    void endDrawing() override;

    void drawLine(Line3f line, IPoint3Shader *shader, IPixelShader *pixelShader) override;

private:
    struct Pimpl;
    std::unique_ptr<Pimpl> _pimpl;
};


#endif //GAME_GL_RENDERER_HPP
