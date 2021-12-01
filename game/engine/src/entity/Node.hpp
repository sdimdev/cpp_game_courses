//
// Created by dzmitry on 01.12.2021.
//

#ifndef GAME_NODE_HPP
#define GAME_NODE_HPP


#include <memory>
#include <vector>

template<typename T>
class Node
{
public:
    std::vector<std::shared_ptr<Node>> childs;
    T value;
    std::shared_ptr<Node> parent;
};


#endif //GAME_NODE_HPP
