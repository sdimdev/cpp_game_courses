//
// Created by dzmitry on 21.11.2021.
//

#ifndef GAME_TIMEINTERACTOR_HPP
#define GAME_TIMEINTERACTOR_HPP


#include <cstdint>

class TimeInteractor
{


public:
    void tick(int64_t* tickTime, bool* frameEnd);
    static int64_t currentTimeMillisecond();
    void play();
    void pause();
private:
    bool paused = true;
    int64_t frameTime = 50;
    int64_t lastTime = TimeInteractor::currentTimeMillisecond();
    int64_t dtime = 0;
};


#endif //GAME_TIMEINTERACTOR_HPP
