//
// Created by dzmitry on 01.12.2021.
//

#ifndef GAME_NODE_HPP
#define GAME_NODE_HPP


#include <memory>
#include <vector>
#include "glm.hpp"

class Node : public std::enable_shared_from_this<Node>
{
public:
    Node()
    {};

    ~Node() = default;

    std::vector<std::shared_ptr<Node>> childs;
    std::shared_ptr<Node> parent;

    virtual glm::mat3 getTransform()
    {
        return glm::mat3(1.0f);
    };

    virtual void drawNode()
    {};

    virtual void visitNode()
    {};

    void addChild(std::shared_ptr<Node>);
};



#endif //GAME_NODE_HPP
