//
// Created by dzmitry on 22.11.2021.
//
//#define GLEW_STATIC
#include <GL/glew.h>


#include "GL_Renderer.hpp"

#include <SDL.h>
#include <utils/FileUtils.cpp>
#include <OpenGL/shader/SpriteShaderProgram.hpp>
#include <OpenGL/vertex/VertexBuffer.hpp>

#include <utils/GLUtils.cpp>
#include <OpenGL/shader/GlTexture.hpp>

/*
 *
 * FOR WINDOWS
 *
 * #define GLEW_STATIC
#include <GL/glew.h>
#include <GL/gl.h>*/

struct GL_Renderer::Pimpl
{
    SDL_GLContext context;
    SDL_Window *window;
    std::shared_ptr<Engine> engine;
    int w, h;
};

void GL_Renderer::startDrawing()
{
    glClearColor(0.6f, 0.6f, 0.9f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    checkErrors(__FILE__, __LINE__);
}

void GL_Renderer::draw()
{
    for (int i = 0; i < commands.size(); i++)
    {
        auto glVertexBuffer = std::dynamic_pointer_cast<VertexBuffer>(commands[i].vertexBuffer);

        if (glVertexBuffer)
        {
            auto glProgram = std::dynamic_pointer_cast<GLProgram>(commands[i].program);
            if (glProgram)
            {
                glProgram->activate();
                glVertexBuffer->draw();
            }
        }
    }
    commands.clear();
    checkErrors(__FILE__, __LINE__);
}

void GL_Renderer::endDrawing()
{
    SDL_GL_SwapWindow(_pimpl->window);
}


GL_Renderer::GL_Renderer(SDL_Window *sdlWindow, int w, int h) : IRenderer()
{
    _pimpl = std::make_unique<GL_Renderer::Pimpl>();
    _pimpl->w = w;
    _pimpl->h = h;

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
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
        fprintf(stderr, "Failed to init GLEW\n %d", err);
        SDL_GL_DeleteContext(sdlWindow);
        SDL_DestroyWindow(sdlWindow);
        SDL_Quit();
        _pimpl->engine->isActive();
    }
    checkErrors(__FILE__, __LINE__);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

GL_Renderer::~GL_Renderer()
{
    SDL_GL_DeleteContext(_pimpl->context);
}

std::shared_ptr<IShaderProgram> GL_Renderer::createProgram(std::string_view name)
{
    return std::make_shared<SpriteShaderProgram>("../engine/src/v_shader.glsl", "../engine/src/f_shader.glsl");
}

std::shared_ptr<ITexture> GL_Renderer::createTexture(Bitmap bitmap)
{
    return std::make_shared<GlTexture>(bitmap);
}

std::shared_ptr<IVertexBuffer> GL_Renderer::createVertexBuffer(MeshData data)
{
    return std::make_shared<VertexBuffer>(data);
}

void GL_Renderer::setEngine(std::shared_ptr<Engine> engine)
{
    _pimpl->engine = engine;
};