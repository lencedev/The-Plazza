/*
** EPITECH PROJECT, 2023
** Plazza
** File description:
** Order
*/

#ifndef ORDER_HPP
    #define ORDER_HPP

    #include <vector>
    #include <unistd.h>
    #include <fstream>
    #include <sstream>
    #include <iostream>
    #include <algorithm>
    #include "Pizza.hpp"

namespace Plazza {
    class Order {
        public:
            Order();
            ~Order();

            void addPizza(const Pizza& pizza);
            std::vector<Pizza> getPizzas() const;
        private:
            std::vector<Pizza> pizzas;
    };
    Order orderFromString(const std::string& order);
}

#endif  // ORDER_HPP
