/*
** EPITECH PROJECT, 2023
** Plazza
** File description:
** Kitchen
*/

#ifndef KITCHEN_HPP
    #define KITCHEN_HPP

#include <sys/wait.h>
#include <unistd.h>
#include <fstream>
#include "Order.hpp"
#include "Reception.hpp"
#include "ThreadPool.hpp"

namespace Plazza {
    class Kitchen {
        public:
            Kitchen(size_t nbThreads, SharedMemory* sharedMemory);

            void run();
            Order getOrder();
            bool hasOrder();
            bool isFull();
            void createProcess();
            void processOrder(const Order& order);
            void orderPizza(std::vector<Pizza> pizzas, SharedMemory* sharedMemory);

            std::vector<Order> getOrders();
            size_t getNbProcesses();
            SharedMemory* getSharedMemory();

        private:
            ThreadPool _pool;
            SharedMemory* _memory;
            std::vector<Order> _orders;
    };
}

#endif // KITCHEN_HPP
