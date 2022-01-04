//
// Created by dzmitry on 01.12.2021.
//

#include "Node.hpp"

void Node::addChild(std::shared_ptr<Node> child)
{
    child->parent = this->shared_from_this();
    childs.push_back(child);
}