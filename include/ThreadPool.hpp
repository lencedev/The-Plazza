/*
** EPITECH PROJECT, 2023
** Plazza
** File description:
** ThreadPool
*/

#ifndef THREADPOOL_HPP
    #define THREADPOOL_HPP

    #include <algorithm>
    #include <condition_variable>
    #include <functional>
    #include <future>
    #include <mutex>
    #include <queue>
    #include <thread>
    #include <vector>
    #include <semaphore.h>

    #define SHARED_MEMORY_SIZE 256

namespace Plazza {
    struct SharedMemory {
        pthread_mutex_t mutex;
        sem_t hasOrder;
        char buffer[SHARED_MEMORY_SIZE];
    };

    class ThreadPool {
        public:
            ThreadPool(size_t threads);
            ~ThreadPool();

            void limitThreads(size_t newLimit);

            template <class F, class... Args>
            auto enqueue(F&& f, Args&&... args) -> std::future<typename std::result_of<F(Args...)>::type>
            {
                using return_type = typename std::result_of<F(Args...)>::type;

                auto task = std::make_shared<std::packaged_task<return_type()>>(
                    std::bind(std::forward<F>(f), std::forward<Args>(args)...));

                std::future<return_type> res = task->get_future();
                {
                    std::unique_lock<std::mutex> lock(queue_mutex);

                    if (stop)
                        throw std::runtime_error("enqueue on stopped ThreadPool");

                    tasks.emplace([task]() { (*task)(); });
                }
                condition.notify_one();
                return res;
            }

            size_t getThreadNumber();
            size_t getMaxThreadNumber();

        private:
            size_t maxThreads;
            std::vector<std::thread> workers;
            std::queue<std::function<void()>> tasks;

            std::mutex queue_mutex;
            std::condition_variable condition;
            bool stop;
        };
}

#endif // THREADPOOL_HPP
