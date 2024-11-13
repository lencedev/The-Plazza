/*
** EPITECH PROJECT, 2023
** Plazza
** File description:
** main
*/

#include "Reception.hpp"

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: ./plazza multiplier cooksPerKitchen restockTime" << std::endl;
        return 84;
    }
    if (std::stod(argv[1]) <= 0 || std::stoi(argv[2]) <= 0 || std::stoi(argv[3]) <= 0) {
        std::cerr << "Error: multiplier, cooksPerKitchen and restockTime must be positive numbers." << std::endl;
        return 84;
    }
    Plazza::Reception reception;
    reception.run(std::stod(argv[1]), std::stoi(argv[2]), std::stoi(argv[3]));
    return 0;
}
