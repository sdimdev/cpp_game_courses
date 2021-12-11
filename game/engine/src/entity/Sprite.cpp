//
// Created by dzmitry on 29.11.2021.
//

#include "Sprite.hpp"
#include <ext/matrix_float3x3.hpp>
#include <gtx/string_cast.hpp>
#include <iostream>

Sprite::Sprite(std::shared_ptr<Engine> engine)
{
    if (logDebug)printf("Sprite::Sprite%d\n", engine != nullptr);
    this->engine = engine;
    node = std::make_shared<Node<SpriteData>>();
}

void Sprite::draw()
{
    if (node != nullptr)
    {
        drawSprite(node);
        //printf("sprite draw childs\n");
        for (int i = 0; i < node->childs.size(); i++)
        {
            drawSprite(node->childs[i]);
        }
    }
}

void Sprite::drawSprite(std::shared_ptr<Node<SpriteData>> node)
{
    std::shared_ptr<IWindow> win = engine->window();
    node->value->screenSizeUniform->value.x = win->getWidth();
    node->value->screenSizeUniform->value.y = win->getHeight();

    glm::mat3 tr = this->getTransform(node);

    glm::vec3 p = {100, 100, 0};
    p = tr * p;
    if (logDebug)printf("tr1=%f %f %f\n", p.x, p.y, p.z);

    node->value->transformUniform->value = tr;
    IRenderer::Command command;
    command.program = node->value->program;
    command.vertexBuffer = node->value->vertexBuffer;
    engine->renderer()->addCommand(std::move(command));
}

glm::mat3 Sprite::getTransform(std::shared_ptr<Node<SpriteData>> node)
{
    glm::mat3 trans = node->value->transformData.getTransform();
    return node->parent ? (node->parent->value->transformData.getTransform() * trans) : trans;
}

void Sprite::visit()
{
    if (node != nullptr)
    {
        visitSprite(node);
        //printf("sprite draw childs\n");
        for (int i = 0; i < node->childs.size(); i++)
        {
            visitSprite(node->childs[i]);
        }
    }
}

void Sprite::visitSprite(std::shared_ptr<Node<SpriteData>> node)
{

}
