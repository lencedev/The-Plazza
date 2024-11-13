/*
** EPITECH PROJECT, 2023
** Plazza
** File description:
** Kitchen
*/

#include "Kitchen.hpp"
#include <cstring>

namespace Plazza {
    Kitchen::Kitchen(size_t nbThreads, SharedMemory* sharedMemory) : _pool(nbThreads), _memory(sharedMemory)
    {
    }

    void Kitchen::run()
    {
        while (true) {
            if (hasOrder()) {
                Order order = getOrder();
                _orders.push_back(order);
                processOrder(order);
                printOrderCompleted(order);
            }
            sleep(1);
        }
    }

    Order Kitchen::getOrder()
    {
        pthread_mutex_lock(&_memory->mutex);
        Order order;
        order = orderFromString(std::string(_memory->buffer));
        pthread_mutex_unlock(&_memory->mutex);
        return order;
    }

    bool Kitchen::hasOrder()
    {
        return sem_trywait(&_memory->hasOrder) == 0;
    }

    void Kitchen::processOrder(const Order& order)
    {
        std::vector<Pizza> pizzas = order.getPizzas();
        std::vector<std::future<void>> futures;

        if (2 * _pool.getThreadNumber() < pizzas.size()) {
            throw std::runtime_error("Not enough threads to process order");
        }

        for (const auto& pizza : pizzas) {
            futures.push_back(_pool.enqueue([pizza] {
                pizza.preparePizza();
            }));
        }

        for (auto& future : futures) {
            std::chrono::milliseconds timeout(3000);
            auto status = future.wait_for(timeout);

            if (status == std::future_status::timeout) {
            } else if (status == std::future_status::ready) {
                future.get();
            }
        }
    }

    bool Kitchen::isFull()
    {
        return (_pool.getThreadNumber() >= _pool.getMaxThreadNumber());
    }

    void Kitchen::createProcess()
    {
        size_t newLimit = _pool.getMaxThreadNumber() + 1;
        _pool.limitThreads(newLimit);
    }

    std::vector<Order> Kitchen::getOrders()
    {
        return _orders;
    }

    size_t Kitchen::getNbProcesses()
    {
        return _pool.getThreadNumber();
    }

    void Kitchen::orderPizza(std::vector<Pizza> pizzas, SharedMemory* sharedMemory)
    {
        std::string orderString = pizzaVectorToString(pizzas);

        if (orderString.size() >= SHARED_MEMORY_SIZE) {
            std::cerr << "Order too large for buffer" << std::endl;
            return;
        }
        pthread_mutex_lock(&sharedMemory->mutex);
        strncpy(sharedMemory->buffer, orderString.c_str(), SHARED_MEMORY_SIZE);
        pthread_mutex_unlock(&sharedMemory->mutex);
        sem_post(&sharedMemory->hasOrder);
    }

    SharedMemory* Kitchen::getSharedMemory()
    {
        return _memory;
    }
}
