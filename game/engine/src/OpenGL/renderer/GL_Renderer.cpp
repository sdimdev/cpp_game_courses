//
// Created by dzmitry on 22.11.2021.
//

#include "GL_Renderer.hpp"
#include <GL/glew.h>
#include <SDL.h>
#include <shader/IPixelShader.hpp>
#include <shader/IPoint3Shader.hpp>
#include <vec2.hpp>
#include <gtc/type_ptr.hpp>
#include <entity/Vertex.hpp>
#include <unistd.h>
#include <entity/Sprite.hpp>
#include <utils/FileUtils.cpp>
#include <utils/GLUtils.cpp>
#include <common/renderer/IShaderProgram.hpp>
#include <OpenGL/shader/SpriteShaderProgram.hpp>


struct GL_Renderer::Pimpl
{
    SDL_GLContext context;
    SDL_Window *window;
    //std::shared_ptr<SpriteShaderProgram> spriteShader;
    int w, h;
};

void GL_Renderer::startDrawing()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(_pimpl->spriteShader->getProgram());

/*
    _pimpl->spriteShader->setupScreenSize(_pimpl->w, _pimpl->h);
    _pimpl->spriteShader->setupTransformMat4(_pimpl->sprite.node.value.transformData.getTransform());
    _pimpl->spriteShader->setupTexture(_pimpl->tl.texture);*/

    //glEnableVertexArrayAttribEXT(_pimpl->sprite.node.value.VAO, 0);
    glBindVertexArray(_pimpl->sprite.node.value.VAO);
    //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glDrawElements(GL_TRIANGLES,
                   _pimpl->sprite.node.value.meshData.indexes.size(), //количество индексов
                   GL_UNSIGNED_INT,
                   0
    );
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glUseProgram(0);
    checkErrors(__FILE__, __LINE__);
}

void GL_Renderer::endDrawing()
{
    SDL_GL_SwapWindow(_pimpl->window);
}


GL_Renderer::GL_Renderer(SDL_Window *sdlWindow, int w, int h) : IRenderer()
{
    _pimpl = std::make_unique<GL_Renderer::Pimpl>();
    //_pimpl->spriteShader = std::make_shared<SpriteShaderProgram>();
    _pimpl->w = w;
    _pimpl->h = h;

/*
    _pimpl->sprite.node.value.meshData.points.push_back({glm::vec3(40.0f, 40.0f, 0.0f), glm::vec2(0.0f, 0.0f)});
    _pimpl->sprite.node.value.meshData.points.push_back({glm::vec3(400.0f, 40.0f, 0.0f), glm::vec2(1.0f, 0.0f)});
    _pimpl->sprite.node.value.meshData.points.push_back({glm::vec3(400.0f, 400.0f, 0.0f), glm::vec2(1.0f, 1.0f)});
    _pimpl->sprite.node.value.meshData.points.push_back({glm::vec3(40.0f, 400.0f, 0.0f), glm::vec2(0.0f, 1.0f)});

    _pimpl->sprite.node.value.meshData.indexes.push_back(0);
    _pimpl->sprite.node.value.meshData.indexes.push_back(1);
    _pimpl->sprite.node.value.meshData.indexes.push_back(2);
    _pimpl->sprite.node.value.meshData.indexes.push_back(0);
    _pimpl->sprite.node.value.meshData.indexes.push_back(2);
    _pimpl->sprite.node.value.meshData.indexes.push_back(3);
*/

  /*  Node<SpriteData> child;
    _pimpl->sprite.node.childs.push_back(std::make_shared<Node<SpriteData>>(child));
    _pimpl->sprite.node.value.transformData.ancor = glm::vec2(0.2f, 0.2f);*/

    //todo move stpite initialisation to other class

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
        fprintf(stderr, "Failed to init GLEW\n");
        SDL_GL_DeleteContext(sdlWindow);
        SDL_DestroyWindow(sdlWindow);
        SDL_Quit();
    }

    _pimpl->tl.load("../engine/src/picture.jpeg");
    checkErrors(__FILE__, __LINE__);


    glGenVertexArrays(1, &_pimpl->sprite.node.value.VAO);
    glBindVertexArray(_pimpl->sprite.node.value.VAO);

    checkErrors(__FILE__, __LINE__);

    glGenBuffers(1, &_pimpl->sprite.node.value.VAO);
    glBindBuffer(GL_ARRAY_BUFFER, _pimpl->sprite.node.value.VAO);
    glBufferData(GL_ARRAY_BUFFER,
                 _pimpl->sprite.node.value.meshData.points.size() * //количество
                 sizeof(Vertex),
                 static_cast<void *>(_pimpl->sprite.node.value.meshData.points.data()),
                 GL_STATIC_DRAW
    );

    checkErrors(__FILE__, __LINE__);

    //указываем выравнивае видеокарте
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
            0, //номер поля
            3, // сколько в поле компонентов
            GL_FLOAT, //тип
            GL_FALSE, // нормализация обрезка от [-1,1]
            sizeof(Vertex),//страйт? расстояние между двумя соседними элементами в массиве
            reinterpret_cast<void *> (offsetof(Vertex, position))
            //reinterpret_cast<void *>(0) //смещение от начала структуры offsetof(Vertex, x);
    );

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(
            1, //номер поля
            2, // сколько в поле компонентов
            GL_FLOAT, //тип
            GL_FALSE, // нормализация обрезка от [-1,1]
            sizeof(Vertex),//страйт? расстояние между двумя соседними элементами в массиве
            reinterpret_cast<void *> (offsetof(Vertex, textCoord))
    );

    checkErrors(__FILE__, __LINE__);
    //заполняем индексы
    glGenBuffers(1, &_pimpl->sprite.node.value.IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _pimpl->sprite.node.value.IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 _pimpl->sprite.node.value.meshData.indexes.size() *
                 sizeof(std::uint32_t)//количество индексов   3* sizeof(std::uint32_t)
            ,
                 _pimpl->sprite.node.value.meshData.indexes.data(),//static_cast<void*>(&mass),
                 GL_STATIC_DRAW
    );
    checkErrors(__FILE__, __LINE__);

    _pimpl->spriteShader->loadProgram();
}

GL_Renderer::~GL_Renderer()
{
    SDL_GL_DeleteContext(_pimpl->context);
};