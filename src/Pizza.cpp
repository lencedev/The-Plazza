/*
** EPITECH PROJECT, 2023
** Plazza
** File description:
** Pizza
*/

#include "Pizza.hpp"

namespace Plazza {
    Pizza::Pizza()
    {
    }

    Pizza::Pizza(PizzaType type, PizzaSize size, int quantity, double multiplier) : type(type), size(size), quantity(quantity), multiplier(multiplier)
    {
    }

    Pizza::~Pizza()
    {
    }

    void Pizza::preparePizza() const
    {
        int cookingTime;
        std::cout << "\nPreparing: " << toString() << std::endl;

        if (type == Regina)
            cookingTime = 2;
        else if (type == Margarita)
            cookingTime = 1;
        else if (type == Americana)
               cookingTime = 2;
        else if (type == Fantasia)
            cookingTime = 4;

        std::cout << "Cooking time: " << multiplier << std::endl;

        std::this_thread::sleep_for(std::chrono::duration<double, std::ratio<1, 1>>(cookingTime * multiplier));
        std::cout << "Finished: " << toString() << std::endl;
    }

    PizzaType Pizza::getType() const
    {
        return type;
    }

    PizzaSize Pizza::getSize() const
    {
        return size;
    }

    int Pizza::getQuantity() const
    {
        return quantity;
    }

    double Pizza::getMultiplier() const
    {
        return multiplier;
    }

    std::string Pizza::toString() const
    {
        return "Pizza: " + std::to_string(type) + " " + std::to_string(size);
    }
}
