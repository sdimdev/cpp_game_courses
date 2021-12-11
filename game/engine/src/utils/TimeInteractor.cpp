//
// Created by dzmitry on 21.11.2021.
//

#include "TimeInteractor.hpp"
#include <chrono>

int64_t TimeInteractor::currentTimeMillisecond()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()).count();
}

void TimeInteractor::tick(int64_t *tickTime, bool *isFrame)
{
    int64_t currTime = currentTimeMillisecond();
    int64_t dt = currTime - lastTime;
    dtime += dt; //always calc dtime and try to flush frame
    if (paused)
    {
        *tickTime = 0;
    } else
    {
        *tickTime = dt;
    }

    if (dtime > frameTime)
    {
        *isFrame = true;
        dtime -= frameTime;
    } else
    {
        *isFrame = false;
    }
    lastTime = currTime;
}

void TimeInteractor::pause()
{
    paused = true;
}

void TimeInteractor::play()
{
    lastTime = currentTimeMillisecond();
    paused = false;
}
