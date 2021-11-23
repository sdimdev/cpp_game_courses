//
// Created by dzmitry on 22.11.2021.
//

#ifndef GAME_GL_RENDERER_HPP
#define GAME_GL_RENDERER_HPP


#include <window/GL_Window.hpp>
#include "IRenderer.hpp"

class GL_Renderer : public IRenderer
{
public:
    //is it right?
    explicit GL_Renderer(GL_Window *glWindow);

    ~GL_Renderer();

    void startDrawing() override;

    void endDrawing() override;

    void drawLine(Line3f line, IPoint3Shader *shader, IPixelShader *pixelShader) override;

private:
    struct Pimpl;
    std::unique_ptr<Pimpl> _pimpl;

    void drawPoint(int x, int y, RGBAColor color);

    void drawLine(int x0, int y0, int x1, int y1, RGBAColor color, IPixelShader *pixelShader);
};


#endif //GAME_GL_RENDERER_HPP
