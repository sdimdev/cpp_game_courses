//
// Created by dzmitry on 19.11.2021.
//

#ifndef GAME_IWINDOWEVENT_HPP
#define GAME_IWINDOWEVENT_HPP


enum EventType
{
    QUIT,
    UNKNOWN
};

enum KeyboardKey
{
    A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,R,S,T,Q,V,W,X,Y,Z,
    LEFT, RIGHT, UP, DOWN, ENTER, SPACE,
    UNKNOWN_KEY
};

enum KeyboardAction
{
    KEY_DOWN,
    KEY_UP
};

class IWindowEvent
{
public:
    virtual ~IWindowEvent() = default;
};

class SimpleWindowEvent : public IWindowEvent
{
public:
    explicit SimpleWindowEvent();

    explicit SimpleWindowEvent(EventType type);

    ~SimpleWindowEvent() override = default;

    EventType eventType;
};

class KeyboardEvent : public IWindowEvent
{
public:

    explicit KeyboardEvent(KeyboardKey key, KeyboardAction action);

    ~KeyboardEvent() override = default;

    KeyboardKey key;
    KeyboardAction action;
};


#endif //GAME_IWINDOWEVENT_HPP
