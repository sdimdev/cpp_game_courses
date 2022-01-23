//
// Created by dzmitry on 10.01.2022.
//

#include <unordered_set>
#include <utility>
#include <chrono>
#include "Scheduler.hpp"
//using namespace std::chrono_literals;

void Scheduler::schedule(
        Scheduler::IRunnable runnable,
        fseconds delay,
        fseconds interval,
        uint32_t count,
        uint64_t key)
{
    ScheduleData data;
    data.runnable = std::move(runnable);
    data.delay = delay;
    data.delta = interval;
    data.count = count;
    data.key = key;
    data.lastTime = std::chrono::high_resolution_clock::now();
    runnableVector.push_back(data);
}

Scheduler::Scheduler()
{
    prevTime = std::chrono::high_resolution_clock::now();
}

void Scheduler::visit()
{
    if (_isFirstRun)
    {
        prevTime = std::chrono::high_resolution_clock::now();
        _isFirstRun = false;
    }

    auto now = std::chrono::high_resolution_clock::now();
    this->delta = now - prevTime;
    prevTime = now;
    std::unordered_set<size_t> removeKeys;
    for (auto &item: runnableVector)
    {
        bool needRun = true;
        if (item.delay.count() > 0.0f)
        {
            auto runnableDelta = now - item.lastTime;
            if (runnableDelta >= item.delay)
            {
                item.delay = 0s;
            } else
            {
                needRun = false;
            }
        }

        if (item.delta.count() > 0 && needRun && (now - item.lastTime) < item.delta)
        {
            needRun = false;
        }

        if (needRun)
        {
            item.lastTime = now;
            item.runnable(this->delta);
        }

        if (item.count != 0)
        {
            --item.count;

            if (item.count == 0)
            {
                removeKeys.insert(item.key);
            }
        }
    }
    std::remove_if(runnableVector.begin(), runnableVector.end(), [&](const ScheduleData &item)
    {
        return removeKeys.find(item.key) != removeKeys.end();
    });
}

void Scheduler::stop(uint64_t key)
{
    std::remove_if(runnableVector.begin(), runnableVector.end(), [&](const ScheduleData &item)
    {
        return key == item.key;
    });
}
