//
// Created by dzmitry on 22.11.2021.
//

#include "GL_Renderer.hpp"
#include <SDL.h>
#include <shader/IPixelShader.hpp>
#include <shader/IPoint3Shader.hpp>
#include <GL/glew.h>
#include <vec2.hpp>
#include <gtc/type_ptr.hpp>
#include <iostream>
#include <entity/Vertex.hpp>
#include <unistd.h>
#include <entity/Sprite.hpp>
#include <TextureLoader.hpp>
#include <utils/FileUtils.cpp>
#include <utils/GLUtils.cpp>

struct GL_Renderer::Pimpl
{
    SDL_GLContext context;
    SDL_Window *window;
    GLuint vertexShader;
    GLuint fragmentShader;
    GLuint program;
    GLint uniform;
    GLint transformUniform;
    GLint texturesUniform;
    GLint textureSizeUniform;
    int w, h;
    Sprite sprite;
    TextureLoader tl;
};

void GL_Renderer::startDrawing()
{
    _pimpl->sprite.node.value.transformData.rotation += 1.0f;
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(_pimpl->program);
    glUniform2f(_pimpl->uniform, _pimpl->w, _pimpl->h);
    glUniformMatrix4fv(_pimpl->transformUniform, 1, GL_FALSE, glm::value_ptr(_pimpl->sprite.node.value.transformData.getTransform()));
    //bind texture
    glActiveTexture(GL_TEXTURE0);
    glUniform1i(_pimpl->texturesUniform, 0);
    //glUniform2i(_pimpl->textureSizeUniform, _pimpl->tl.width, _pimpl->tl.height);
    glBindTexture(GL_TEXTURE_2D, _pimpl->tl.texture);

    //glEnableVertexArrayAttribEXT(_pimpl->sprite.node.value.VAO, 0);
    glBindVertexArray(_pimpl->sprite.node.value.VAO);
    //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glDrawElements(GL_TRIANGLES,
                   _pimpl->sprite.node.value.meshData.indexes.size(), //количество индексов
                   GL_UNSIGNED_INT,
                   0
    );
    glUseProgram(0);
    checkErrors();
}

void GL_Renderer::endDrawing()
{
    SDL_GL_SwapWindow(_pimpl->window);
}

void GL_Renderer::drawLine(Line3f line, IPoint3Shader *shader, IPixelShader *pixelShader)
{
    //todo
}

GL_Renderer::GL_Renderer(SDL_Window *sdlWindow, int w, int h) : IRenderer()
{
    _pimpl = std::make_unique<GL_Renderer::Pimpl>();
    _pimpl->w = w;
    _pimpl->h = h;

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

    Node<SpriteData> child;
    _pimpl->sprite.node.childs.push_back(std::make_shared<Node<SpriteData>>(child));
    _pimpl->sprite.node.value.transformData.ancor = glm::vec2(0.2f, 0.2f);

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
    checkErrors();


    glGenVertexArrays(1, &_pimpl->sprite.node.value.VAO);
    glBindVertexArray(_pimpl->sprite.node.value.VAO);

    checkErrors();

    glGenBuffers(1, &_pimpl->sprite.node.value.VAO);
    glBindBuffer(GL_ARRAY_BUFFER, _pimpl->sprite.node.value.VAO);
    glBufferData(GL_ARRAY_BUFFER,
                 _pimpl->sprite.node.value.meshData.points.size() * //количество
                 sizeof(Vertex),
                 static_cast<void *>(_pimpl->sprite.node.value.meshData.points.data()),
                 GL_STATIC_DRAW
    );

    checkErrors();

    //указываем выравнивае видеокарте

    glVertexAttribPointer(
            0, //номер поля
            3, // сколько в поле компонентов
            GL_FLOAT, //тип
            GL_FALSE, // нормализация обрезка от [-1,1]
            sizeof(Vertex),//страйт? расстояние между двумя соседними элементами в массиве
            reinterpret_cast<void *> (offsetof(Vertex, position))
            //reinterpret_cast<void *>(0) //смещение от начала структуры offsetof(Vertex, x);
    );
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(
            1, //номер поля
            2, // сколько в поле компонентов
            GL_FLOAT, //тип
            GL_FALSE, // нормализация обрезка от [-1,1]
            sizeof(Vertex),//страйт? расстояние между двумя соседними элементами в массиве
            reinterpret_cast<void *> (offsetof(Vertex, textCoord))
    );
    glEnableVertexAttribArray(1);


    checkErrors();
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
    checkErrors();

    GLint success;
    GLchar infoLog[512];

    char tmp[256];
    getcwd(tmp, 256);
    printf("%s", tmp);
    _pimpl->vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char *c_v_shader =
            loadFromFile("../engine/src/v_shader.glsl");
    printf("\n VERTEX SHADER %s\n", c_v_shader);
    glShaderSource(_pimpl->vertexShader, 1, &c_v_shader, nullptr);
    glCompileShader(_pimpl->vertexShader);

    checkErrors();
    glGetShaderiv(_pimpl->vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(_pimpl->vertexShader, 512, nullptr, infoLog);
        std::cerr << infoLog << std::endl;
    }

    _pimpl->fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char *c_f_shader =
            loadFromFile("../engine/src/f_shader.glsl");
    printf("\n FRAGMENT SHADER: %s\n", c_f_shader);
    glShaderSource(_pimpl->fragmentShader, 1, &c_f_shader, nullptr);
    glCompileShader(_pimpl->fragmentShader);

    checkErrors();
    glGetShaderiv(_pimpl->fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(_pimpl->fragmentShader, 512, nullptr, infoLog);
        std::cerr << infoLog << std::endl;
    }

    //линкуем шейдера
    _pimpl->program = glCreateProgram();

    glAttachShader(_pimpl->program, _pimpl->vertexShader);
    glAttachShader(_pimpl->program, _pimpl->fragmentShader);
    glLinkProgram(_pimpl->program);

    checkErrors();
    glGetShaderiv(_pimpl->fragmentShader, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(_pimpl->fragmentShader, 512, nullptr, infoLog);
        std::cerr << infoLog << std::endl;
    }
    glUseProgram(_pimpl->program);

    //задаем униформу
    _pimpl->uniform = glGetUniformLocation(_pimpl->program, "screenSize");
    _pimpl->transformUniform = glGetUniformLocation(_pimpl->program, "transform");
    _pimpl->texturesUniform = glGetUniformLocation(_pimpl->program, "uTexture");
    _pimpl->textureSizeUniform = glGetUniformLocation(_pimpl->program, "textureSize");
}

GL_Renderer::~GL_Renderer()
{
    SDL_GL_DeleteContext(_pimpl->context);
};