//
// Created by dzmitry on 07.01.2022.
//

#include "Person.hpp"

struct Person::Pimpl
{
    std::shared_ptr<TextureController> textureController = nullptr;

    IKeyboardKeyListener listener([&](const std::shared_ptr<KeyboardKey> key, bool pressed)
    {
        swith(key)
        {
            case A:
                moveLeft = pressed;
            return true;
            case D:
                moveRight = pressed;
            return true;
            case W:
                moveUp = pressed;
            return true;
            case S:
                moveDown = pressed;
            return true;
        }
        return false;
    }

    );
    bool moveLeft = false;
    bool moveRight = false;
    bool moveUp = false;
    bool moveDown = false;

};

Person::Person(std::shared_ptr<Engine> engine, std::string_view filepath)
        : Sprite(engine, filepath)
{
    _pimpl = std::make_unique<Person::Pimpl>();
    _pimpl->textureController = std::make_shared<TextureController>(4, 1);
    engine->eventManager()->add(_pimpl->listener);
}

Person::~Person()
{
    engine->eventManager()->remove(_pimpl->listener);
}
