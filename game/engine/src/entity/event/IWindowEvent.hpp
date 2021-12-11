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


#endif //GAME_IWINDOWEVENT_HPP
