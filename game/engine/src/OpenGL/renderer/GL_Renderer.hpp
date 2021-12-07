//
// Created by dzmitry on 22.11.2021.
//

#ifndef GAME_GL_RENDERER_HPP
#define GAME_GL_RENDERER_HPP


#include <OpenGL/window/GL_Window.hpp>
#include "common/IRenderer.hpp"
#include <SDL.h>
#include <engine/Engine.hpp>

class GL_Renderer : public IRenderer
{
public:
    //is it right?
    explicit GL_Renderer(SDL_Window *sdlWindow, int w, int h);

    ~GL_Renderer();

    void startDrawing() override;

    void draw() override;

    void endDrawing() override;

    void setEngine(std::shared_ptr<Engine> engine);

    std::shared_ptr<IShaderProgram> createProgram(std::string_view name) override;

    std::shared_ptr<ITexture> createTexture(Bitmap bitmap) override;

    std::shared_ptr<IVertexBuffer> createVertexBuffer(MeshData data) override;

private:
    struct Pimpl;
    std::unique_ptr<Pimpl> _pimpl;
};

#endif //GAME_GL_RENDERER_HPP
