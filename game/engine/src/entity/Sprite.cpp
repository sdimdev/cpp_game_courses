//
// Created by dzmitry on 29.11.2021.
//

#include "Sprite.hpp"
#include <ext/matrix_float3x3.hpp>
#include <gtx/string_cast.hpp>
#include <iostream>

Sprite::Sprite(std::shared_ptr<Engine> engine, std::string_view filepath)
{
    if (logDebug)printf("Sprite::Sprite%d\n", engine != nullptr);
    this->engine = engine;
    spriteData = std::make_shared<SpriteData>(engine, filepath);
}

void Sprite::drawNode()
{
    std::shared_ptr<IWindow> win = engine->window();
    if (logDebug)printf("screen %d %d\n", win->getWidth(), win->getHeight());
    spriteData->screenSizeUniform->value.x = win->getWidth();
    spriteData->screenSizeUniform->value.y = win->getHeight();

    glm::mat3 tr = this->getTransform();

    glm::vec3 p = {100, 100, 0};

    /*node->value->vertexBuffer*/

    p = tr * p;
    if (logDebug)printf("tr1=%f %f %f\n", p.x, p.y, p.z);

    spriteData->transformUniform->value = tr;
    IRenderer::Command command;
    command.program = spriteData->program;
    command.vertexBuffer = spriteData->vertexBuffer;
    engine->renderer()->addCommand(std::move(command));

    //printf("sprite draw childs\n");
}

glm::mat3 Sprite::getTransform()
{
    glm::mat3 trans = spriteData->transform.getTransform();
    return parent ? (parent->getTransform() * trans) : trans;
}

void Sprite::visitNode()
{

}
