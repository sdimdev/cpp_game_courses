//
// Created by dzmitry on 19.11.2021.
//

#ifndef GAME_IRENDERER_HPP
#define GAME_IRENDERER_HPP


#include <domain/Line3f.hpp>
#include <shader/IPoint3Shader.hpp>

class IRenderer
{
public:
    virtual void startDrawing() = 0;

    virtual void endDrawing() = 0;

    virtual void drawLine(Line3f line, IPoint3Shader* shader) = 0;
};


#endif //GAME_IRENDERER_HPP
