//
// Created by dzmitry on 29.11.2021.
//

#include "Sprite.hpp"
#include <ext/matrix_float3x3.hpp>
#include <gtx/string_cast.hpp>
#include <iostream>

Sprite::Sprite(std::shared_ptr<Engine> engine)
{
    printf("Sprite::Sprite%d\n", engine!=nullptr);
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
    //printf("start drawSprite %d\n", engine!=nullptr);
    std::shared_ptr<IWindow> win = engine->window();
    //printf("set screen size\n");
    node->value->screenSizeUniform->value.x = win->getWidth();
    node->value->screenSizeUniform->value.y = win->getHeight();

    glm::mat3 tr = this->getTransform(node);
    //std::cout << glm::to_string(tr);
    node->value->transformUniform->value = tr;

    //printf("run command\n");
    IRenderer::Command command;
    command.program = node->value->program;
    command.vertexBuffer = node->value->vertexBuffer;
    engine->renderer()->addCommand(std::move(command));
}

glm::mat3 Sprite::getTransform(std::shared_ptr<Node<SpriteData>> node)
{
    if (node->value->transformData.transform)
    {
        return node->parent ? (node->parent->value->transformData.getTransform() *
                               *node->value->transformData.transform) : *node->value->transformData.transform;
    } else
    {
        glm::mat3 trans(1.0f);

        trans = glm::translate(trans, node->value->transformData.position);
        trans = glm::scale(trans, node->value->transformData.scale);
        trans = glm::rotate(trans, glm::radians(node->value->transformData.rotation));

        trans = glm::translate(trans,
                               -glm::vec2(node->value->transformData.anchor.x * node->value->transformData.size.x,
                                          node->value->transformData.anchor.y * node->value->transformData.size.y));

        node->value->transformData.transform = trans;
        return node->parent ? (node->parent->value->transformData.getTransform() * trans) : trans;
    }
}

void Sprite::visit()
{

}
