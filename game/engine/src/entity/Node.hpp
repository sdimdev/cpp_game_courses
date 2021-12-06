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
    Node();
    ~Node() = default;
    std::vector<std::shared_ptr<Node>> childs;
    std::shared_ptr<T> value;
    std::shared_ptr<Node> parent;
};

template<typename T>
Node<T>::Node()
{

}


#endif //GAME_NODE_HPP
