//
// Created by dzmitry on 05.12.2021.
//

#include <cstdio>
#include "NodeScene.hpp"

void NodeScene::draw()
{
    drawNode(this->value);
}

bool NodeScene::handleEvent(EventType eventType)
{
    return false;
}

NodeScene::NodeScene(std::shared_ptr<Engine> engine)
{
    printf("SpritesScene::SpritesScene%d\n", engine != nullptr);
    this->engine = engine;
    this->value = std::make_shared<Node>();
}

std::shared_ptr<Node> NodeScene::node()
{
    return value;
}

void NodeScene::setNode(std::shared_ptr<Node> node)
{
    this->value = node;
}

void NodeScene::drawNode(std::shared_ptr<Node> node)
{
    if (node != nullptr)
    {
        node->drawNode();
        for (auto child: node->childs)
        {
            drawNode(child);
        }
    }
}

NodeScene::~NodeScene() = default;

