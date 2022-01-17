//
// Created by dzmitry on 10.01.2022.
//

#ifndef GAME_SCHEDULER_HPP
#define GAME_SCHEDULER_HPP

#include <functional>
#include <list>
#include <chrono>

using fseconds = std::chrono::duration<float>;
using namespace std::chrono_literals;

class Scheduler final
{
protected:
    using timePoint =std::chrono::system_clock::time_point;
    using IRunnable = std::function<void(fseconds time)>;
    struct ScheduleData
    {
        IRunnable runnable;

        fseconds delay;
        fseconds delta;

        size_t count;
        size_t exec_count;
        size_t key;
        std::chrono::system_clock::time_point lastTime;
    };

    std::chrono::system_clock::time_point prevTime;
    fseconds delta{};
    std::vector<ScheduleData> runnableVector;
    bool _isFirstRun = true;
public:
    explicit Scheduler();

    void visit();

    void schedule(IRunnable runnable,
                  fseconds delay,
                  fseconds interval,
                  uint32_t count,
                  uint64_t key);
    void stop(uint64_t key);
};


#endif //GAME_SCHEDULER_HPP
