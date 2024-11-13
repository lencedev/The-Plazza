/*
** EPITECH PROJECT, 2023
** Plazza
** File description:
** Pizza
*/

#ifndef PIZZA_HPP
    #define PIZZA_HPP

#include <iostream>
#include <string>
#include <thread>

namespace Plazza {
    enum PizzaType {
        Regina = 1,
        Margarita = 2,
        Americana = 4,
        Fantasia = 8
    };

    enum PizzaSize {
        S = 1,
        M = 2,
        L = 4,
        XL = 8,
        XXL = 16
    };

    class Pizza {
        public:
            Pizza();
            Pizza(PizzaType type, PizzaSize size, int quantity, double multiplier);
            ~Pizza();

            void preparePizza() const;

            PizzaType getType() const;
            PizzaSize getSize() const;
            int getQuantity() const;
            double getMultiplier() const;
            std::string toString() const;
        private:
            PizzaType type;
            PizzaSize size;
            int quantity;
            double multiplier;
    };
}

#endif // PIZZA_HPP
