//
// Created by dzmitry on 07.01.2022.
//

#ifndef GAME_PERSON_HPP
#define GAME_PERSON_HPP


#include "entity/Sprite.hpp"
#include "entity/TextureController.hpp"

class Person : public Sprite
{
public:
    using IEventListener = std::function<bool(std::shared_ptr<IWindowEvent>)>;
    explicit Person(std::shared_ptr<Engine> engine, std::string_view filepath);
    ~Person();

private:
    struct Pimpl;
    std::unique_ptr<Pimpl> _pimpl;
};


#endif //GAME_PERSON_HPP
