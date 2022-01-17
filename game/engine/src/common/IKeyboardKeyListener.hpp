//
// Created by dzmitry on 10.01.2022.
//

#ifndef GAME_IKEYBOARDKEYLISTENER_HPP
#define GAME_IKEYBOARDKEYLISTENER_HPP

#include <entity/event/IWindowEvent.hpp>
#include <functional>
#include <random>

class IKeyboardKeyListener
{
public:
    explicit IKeyboardKeyListener(std::function<bool(KeyboardKey, bool)> &listener);
    ~IKeyboardKeyListener() = default;
    bool onKeyboardKeyPressChanged(KeyboardKey key, bool pressed);

    bool operator==(const IKeyboardKeyListener &rhs) const;

    bool operator!=(const IKeyboardKeyListener &rhs) const;

private:
    std::function<bool(KeyboardKey, bool)> listener;
    inline size_t getRandInt() {
        static size_t i;
        return ++i;
    };
    uint32_t hashcode = getRandInt();
};


#endif //GAME_IKEYBOARDKEYLISTENER_HPP
