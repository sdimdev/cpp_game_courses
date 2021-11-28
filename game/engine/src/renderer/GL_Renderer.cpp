//
// Created by dzmitry on 22.11.2021.
//

#include "GL_Renderer.hpp"
#include <SDL.h>
#include <entity/RGBAColor.hpp>
#include <shader/IPixelShader.hpp>
#include <shader/IPoint3Shader.hpp>
#include <GL/glew.h>
#include <glm.hpp>
#include <gtc/type_ptr.hpp>
#include <iostream>

struct Point
{
    float x, y;
};

struct Triangle
{ //todo делаем массив
    Point p1, p2, p3;
};

static std::string v_shader = "#version 330 core\n"
                              "layout (location = 0) in vec2 position;\n"
                              "out vec2 oPos;\n"
                              "uniform vec2 screenSize;\n"
                              "void main()\n"
                              "{\n"
                              "oPos = position / screenSize * 2.0 - vec2(1.0);\n"
                              "gl_Position = vec4(oPos.x, oPos.y, 1.0, 1.0);\n"
                              "}";

static std::string p_shader = "#version 330 core\n"
                              "in vec2 oPos;\n"
                              "out vec4 color;\n"
                              "void main()\n"
                              "{\n"
                              "color = vec4(oPos.x * 0.5 + 0.5, oPos.y * 0.5 + 0.5, 1.0, 1.0);\n"
                              "}";

struct GL_Renderer::Pimpl
{
    SDL_GLContext context;
    SDL_Window *window;
    bool flag = false;
    GLuint VAO;
    GLuint IBO;
    GLuint vertexShader;
    GLuint fragmentShader;
    GLuint program;
    GLint uniform;
    int w, h;
    Triangle triangle{{0, 0},
                      {640, 480},
                      {400, 100}};
    //SDL_Renderer *renderer = nullptr;
};


void GL_Renderer::startDrawing()
{
    if (_pimpl->flag)
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    }
    glClear(GL_COLOR_BUFFER_BIT);
    _pimpl->flag = !_pimpl->flag;


    glUseProgram(_pimpl->program);
    std::cout << _pimpl->w << " :" << _pimpl->h;
    glUniform2f(_pimpl->uniform, _pimpl->w, _pimpl->h);

    glBindVertexArray(_pimpl->VAO);
    glDrawElements(GL_TRIANGLES,
                   3, //количество индексов
                   GL_UNSIGNED_INT,
                   0
    );
    checkErrors();

    /*  glColor4ub( 0,0,255,255);
      glLineWidth( 5 );
      glBegin(GL_LINES);
      glVertex2i(500,0);
      glVertex2i(0,500);
      glEnd();
      glLineWidth( 1.0f );*/

/*    glBegin(GL_TRIANGLES);
    glColor3f(1, 1, 1);
    glVertex2d(10, 100);
    glVertex2d(100, 100);
    glVertex2d(200, 200);
    glEnd();*/
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

        fprintf(stderr, "Failed to init GLEW\n");
        SDL_GL_DeleteContext(sdlWindow);
        SDL_DestroyWindow(sdlWindow);
        SDL_Quit();
    }


    glGenVertexArrays(1, &_pimpl->VAO);
    glBindVertexArray(_pimpl->VAO); //

    checkErrors();

    glGenBuffers(1, &_pimpl->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, _pimpl->VAO);
    glBufferData(GL_ARRAY_BUFFER, 1 * //количество
                                  sizeof(Triangle),
                 static_cast<void *>(&_pimpl->triangle),
                 GL_STATIC_DRAW
    );

    checkErrors();

    //указываем выравнивае видеокарте
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
            0, //номер поля
            2, // сколько в поле компонентов
            GL_FLOAT, //тип
            GL_FALSE, // нормализация обрезка от [-1,1]
            sizeof(Point),//страйт? расстояние между двумя соседними элементами в массиве
            reinterpret_cast<void *> (offsetof(Point, x))
            //reinterpret_cast<void *>(0) //смещение от начала структуры offsetof(Vertex, x);
    );


    checkErrors();
    //заполняем индексы
    std::uint32_t mass[3] = {0, 1, 2};
    glGenBuffers(1, &_pimpl->IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _pimpl->IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 sizeof(mass)//количество индексов   3* sizeof(std::uint32_t)
            ,
                 &mass,//static_cast<void*>(&mass),
                 GL_STATIC_DRAW
    );
    checkErrors();

    GLint success;
    GLchar infoLog[512];

    _pimpl->vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char *c_v_shader = v_shader.c_str();
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
    const char *c_f_shader = p_shader.c_str();
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

    //printf("drawLine %d %d %d %d\n", x0, y0, x1, y1);
    glColor3f(color.getRed() / 255, color.getGreen() / 255, color.getBlue() / 255);
    glLineWidth(2);
    glBegin(GL_LINES);
    glVertex2f(x0, y0);
    glVertex2f(x1, y1);
    glEnd();
    /* //copied from https://habr.com/ru/post/248153/
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
     }*/
}

void GL_Renderer::checkErrors()
{
    GLenum err(glGetError());
    while (err != GL_NO_ERROR)
    {
        std::string error;
        switch (err)
        {
            case GL_INVALID_OPERATION:
                error = "INVALID_OPERATION";
                break;

            case GL_INVALID_ENUM:
                error = "GL_INVALID_ENUM";
                break;

            case GL_INVALID_VALUE:
                error = "GL_INVALID_VALUE";
                break;

            case GL_OUT_OF_MEMORY:
                error = "GL_OUT_OF_MEMORY";
                break;

            case GL_INVALID_FRAMEBUFFER_OPERATION:
                error = "GL_INVALID_FRAMEBUFFER_OPERATION";
                break;
            default:
                error = "INVALID_OPERATION";
        }
        std::cerr << "GL_" << error << " : 0x" << std::hex << err << std::dec << " - " << ":" << std::endl;
        //todo add file and line of code
        err = glGetError();
    }

};
