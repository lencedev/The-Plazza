/*
** EPITECH PROJECT, 2023
** theo_pr
** File description:
** Order
*/

#include "Order.hpp"

namespace Plazza {
    Order::Order()
    {
    }

    Order::~Order()
    {
    }

    void Order::addPizza(const Pizza& pizza)
    {
        pizzas.push_back(pizza);
    }

    std::vector<Pizza> Order::getPizzas() const
    {
        return pizzas;
    }

    std::string removeSpaces(std::string str)
    {
        std::string result;

        for (char c : str) {
            if (!std::isspace(c)) {
                result += c;
            }
        }
        return result;
    }

    Order orderFromString(const std::string& orderString)
    {
        Order newOrder;

        size_t startPos = orderString.find("Pizzas: [");
        size_t endPos = orderString.find("]", startPos);
        if (startPos == std::string::npos || endPos == std::string::npos) {
            return newOrder;
        }

        std::string pizzaString = orderString.substr(startPos + 9, endPos - startPos - 10);
        std::istringstream iss(pizzaString);
        std::string pizzaToken;
        while (std::getline(iss, pizzaToken, ',')) {
            std::string typeStr, sizeStr, quantityStr, multiplierStr;
            size_t typePos = pizzaToken.find("Type: ");
            size_t sizePos = pizzaToken.find("Size: ");
            size_t quantityPos = pizzaToken.find("Quantity: ");
            size_t multiplierPos = pizzaToken.find("Multiplier: ");

            typeStr = pizzaToken.substr(typePos + 7, sizePos - typePos - 7);
            sizeStr = pizzaToken.substr(sizePos + 6, quantityPos - sizePos - 7);
            quantityStr = pizzaToken.substr(quantityPos + 10, multiplierPos - quantityPos - 11);
            multiplierStr = pizzaToken.substr(multiplierPos + 12);

            PizzaType pizzaType;
            std::transform(typeStr.begin(), typeStr.end(), typeStr.begin(), ::tolower);
            typeStr = removeSpaces(typeStr);
            if (typeStr == "regina")
                pizzaType = PizzaType::Regina;
            else if (typeStr == "margarita")
                pizzaType = PizzaType::Margarita;
            else if (typeStr == "americana")
                pizzaType = PizzaType::Americana;
            else if (typeStr == "fantasia")
                pizzaType = PizzaType::Fantasia;
            else {
                std::cerr << "Invalid pizza type: " << typeStr << std::endl;
                continue;
            }

            PizzaSize pizzaSize;
            if (sizeStr == "S")
                pizzaSize = PizzaSize::S;
            else if (sizeStr == "M")
                pizzaSize = PizzaSize::M;
            else if (sizeStr == "L")
                pizzaSize = PizzaSize::L;
            else if (sizeStr == "XL")
                pizzaSize = PizzaSize::XL;
            else if (sizeStr == "XXL")
                pizzaSize = PizzaSize::XXL;
            else {
                std::cerr << "Invalid pizza size: " << sizeStr << std::endl;
                continue;
            }

            int quantity = std::stoi(quantityStr);
            double multiplier = std::stod(multiplierStr);

            Pizza pizza(pizzaType, pizzaSize, quantity, multiplier);
            newOrder.addPizza(pizza);
        }
        return newOrder;
    }
}
