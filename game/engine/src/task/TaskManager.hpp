//
// Created by dzmitry on 26.01.2022.
//

#ifndef GAME_TASKMANAGER_HPP
#define GAME_TASKMANAGER_HPP

#include <functional>
#include <queue>

struct Task
{
    bool isDone;
    std::function<void()> body;

};

class Handler{
public:
    explicit Handler();
    void add(std::shared_ptr<Task> task);
private:
    std::queue<std::shared_ptr<Task>> tasks;
    std::thread thread;
    std::condition_variable cv;
    std::mutex mutex;
    std::atomic_bool isWork {true};
};

class TaskManager
{
public:
    explicit TaskManager();

    void add(std::shared_ptr<Task> task);

    ~TaskManager() = 0;

    using queue = std::queue<std::shared_ptr<Task>>;

    std::vector<Handler> handlers;
};


#endif //GAME_TASKMANAGER_HPP
