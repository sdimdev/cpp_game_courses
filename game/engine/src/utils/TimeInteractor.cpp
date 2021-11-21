//
// Created by dzmitry on 21.11.2021.
//

#include "TimeInteractor.hpp"
#include <chrono>

int64_t TimeInteractor::currentTimeMillisecond()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}
