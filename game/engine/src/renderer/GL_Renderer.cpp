//
// Created by dzmitry on 22.11.2021.
//

#include "GL_Renderer.hpp"
#include <SDL.h>
#include <domain/RGBAColor.hpp>
#include <shader/IPixelShader.hpp>
#include <shader/IPoint3Shader.hpp>
#include <GL/glew.h>
#include <glm.hpp>
#include <gtc/type_ptr.hpp>

struct GL_Renderer::Pimpl
{
    SDL_GLContext context;
    SDL_Window *window;
    //SDL_Renderer *renderer = nullptr;
};

void GL_Renderer::startDrawing()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_TRIANGLES);
    glColor3f(1, 1, 1);
    glVertex2d(10, 100);
    glVertex2d(100, 100);
    glVertex2d(200, 200);
    glEnd();
}

void GL_Renderer::endDrawing()
{
    SDL_GL_SwapWindow(_pimpl->window);
}

void GL_Renderer::drawLine(Line3f line, IPoint3Shader *shader, IPixelShader *pixelShader)
{
    Point3f p1 = line.getP1();
    Point3f p2 = line.getP2();
    RGBAColor c(0, 255, 0, 255);
    if (shader != nullptr)
    {
        p1 = shader->apply(p1);
        p2 = shader->apply(p2);
    }
    drawLine((int) p1.getX(),
             (int) p1.getY(),
             (int) p2.getX(),
             (int) p2.getY(),
             c,
             pixelShader);
}

GL_Renderer::GL_Renderer(SDL_Window *sdlWindow) : IRenderer()
{
    _pimpl = std::make_unique<GL_Renderer::Pimpl>();
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(
            SDL_GL_CONTEXT_PROFILE_MASK,
            SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    _pimpl->context = SDL_GL_CreateContext(sdlWindow);
    _pimpl->window = sdlWindow;
    if (_pimpl->context == nullptr)
    {
        fprintf(stderr, "Failed to init GL_Context\n");
        SDL_DestroyWindow(sdlWindow);
        SDL_Quit();
    }

    SDL_GL_SetSwapInterval(1); // Use VSYNC

    // Initialize GL Extension Wrangler (GLEW)
    GLenum err;
    glewExperimental = GL_TRUE; // Please expose OpenGL 3.x+ interfaces
    err = glewInit();

    if (err != GLEW_OK)
    {

        fprintf(stderr, "Failed to init GLEW\n");
        SDL_GL_DeleteContext(sdlWindow);
        SDL_DestroyWindow(sdlWindow);
        SDL_Quit();
    }

    // _pimpl->renderer = renderer;
}

GL_Renderer::~GL_Renderer()
{
    SDL_GL_DeleteContext(_pimpl->context);
};

void GL_Renderer::drawPoint(int x, int y, RGBAColor color)
{
    glBegin(GL_POINTS);
    glColor3b(color.getRed(), color.getGreen(), color.getBlue());
    glVertex2d(x, y);
    glEnd();
}

void GL_Renderer::drawLine(int x0, int y0, int x1, int y1, RGBAColor color, IPixelShader *pixelShader)
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
