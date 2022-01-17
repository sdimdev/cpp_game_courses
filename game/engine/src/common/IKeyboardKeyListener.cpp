//
// Created by dzmitry on 10.01.2022.
//

#include "IKeyboardKeyListener.hpp"


IKeyboardKeyListener::IKeyboardKeyListener(std::function<bool(KeyboardKey, bool)> &listener)
{
    this->listener = listener;
}

bool IKeyboardKeyListener::onKeyboardKeyPressChanged(KeyboardKey key, bool pressed)
{
    return listener(key, pressed);
}

bool IKeyboardKeyListener::operator==(const IKeyboardKeyListener &rhs) const
{
    return hashcode == rhs.hashcode;
}

bool IKeyboardKeyListener::operator!=(const IKeyboardKeyListener &rhs) const
{
    return !(rhs == *this);
}