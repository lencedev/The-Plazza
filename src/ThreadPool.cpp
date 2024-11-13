/*
** EPITECH PROJECT, 2023
** Plazza
** File description:
** ThreadPool
*/

#include "ThreadPool.hpp"

namespace Plazza {
    ThreadPool::ThreadPool(size_t threads) : stop(false), maxThreads(threads)
    {
        for (size_t i = 0; i < threads; ++i) {
            workers.emplace_back([this]() {
                while (true) {
                    std::function<void()> task;
                    {
                        std::unique_lock<std::mutex> lock(queue_mutex);
                        condition.wait(lock, [this] { return stop || !tasks.empty(); });
                        if (stop && tasks.empty()) return;
                        task = std::move(tasks.front());
                        tasks.pop();
                    }
                    task();
                }
            });
        }
    }

    ThreadPool::~ThreadPool()
    {
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            stop = true;
        }
        condition.notify_all();
        for (std::thread &worker : workers) worker.join();
    }

    void ThreadPool::limitThreads(size_t newLimit)
    {
        if (newLimit > maxThreads) throw std::runtime_error("Cannot increase thread limit");
        std::unique_lock<std::mutex> lock(queue_mutex);
        maxThreads = newLimit;
        while (workers.size() > maxThreads) {
            workers.pop_back();
        }
    }

    size_t ThreadPool::getThreadNumber()
    {
        return workers.size();
    }

    size_t ThreadPool::getMaxThreadNumber()
    {
        return maxThreads;
    }
}
