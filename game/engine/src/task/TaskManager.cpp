//
// Created by dzmitry on 26.01.2022.
//

#include <memory>
#include <mutex>
#include "TaskManager.hpp"

void Handler::add(std::shared_ptr<Task> task)
{

}

Handler::Handler() : thread(
        [this]()
        {
            while (isWork)
            {
                std::unique_lock<std::mutex> lk(mutex);
                cv.wait(lk, [this]
                { return !tasks.empty(); });
                if (!tasks.empty())
                {
                    auto task = tasks.front();
                    task->body();
                    tasks.pop();
                }
                lk.unlock();
            }
        }
)
{
thread.detach();
}
