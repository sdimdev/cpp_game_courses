//
// Created by dzmitry on 01.12.2021.
//

#ifndef GAME_NODE_HPP
#define GAME_NODE_HPP


#include <memory>
#include <vector>

template<typename T>
class Node : public std::enable_shared_from_this<Node<T>>
{
public:
    Node();

    Node(std::shared_ptr<T> value);

    ~Node() = default;

    std::vector<std::shared_ptr<Node<T>>> childs;
    std::shared_ptr<T> value;
    std::shared_ptr<Node<T>> parent;

    void addChild(std::shared_ptr<Node<T>>);
};

template<typename T>
Node<T>::Node()
{

}

template<typename T>
void Node<T>::addChild(std::shared_ptr<Node<T>> child)
{
    child-> parent = this->shared_from_this();
    childs.push_back(child);
}

template<typename T>
Node<T>::Node(std::shared_ptr<T> value)
{
    this->value = value;
}


#endif //GAME_NODE_HPP
