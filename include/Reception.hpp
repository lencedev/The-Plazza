/*
** EPITECH PROJECT, 2023
** theo_pr
** File description:
** Reception
*/

#ifndef RECEPTION_HPP_
    #define RECEPTION_HPP_

    #include <sys/mman.h>
    #include <cstring>
    #include <iostream>
    #include <sstream>
    #include <vector>
    #include "Kitchen.hpp"
    #include "Order.hpp"
    #include "Pizza.hpp"

    #ifdef _WIN32
    #include <direct.h>
    #define CREATE_DIRECTORY(path) _mkdir(path)
    #else
    #include <sys/stat.h>
    #define CREATE_DIRECTORY(path) mkdir(path, 0755)
    #endif

namespace Plazza {
    class Kitchen;
    class Reception {
        public:
            Reception();
            ~Reception();

            void manageKitchen(Kitchen& kitchen);
            void displayStatus(Kitchen& kitchen);
            void orderPizzas(const std::vector<Pizza> pizzas, Kitchen& kitchen);
            std::vector<Pizza> parseOrder(std::string order, double multiplier);
            void run(double multiplier, int cooksPerKitchen, int restockTime);

        protected:
        private:
    };
    void printPizzas(const std::vector<Pizza>& pizzas, std::ostream& os = std::cout);
    std::string pizzaToString(Pizza& pizza);
    std::string pizzaToReceit(Pizza& pizza);
    std::string pizzaVectorToString(const std::vector<Pizza>& pizzas);
    bool directoryExists(const std::string& path);
    void fileExists(int& id);
    void printOrderCompleted(const Order& order);
}

#endif /* !RECEPTION_HPP_ */
