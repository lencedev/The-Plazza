/*
** EPITECH PROJECT, 2023
** theo_pr
** File description:
** Reception
*/

#include "Reception.hpp"

namespace Plazza {
    Reception::Reception()
    {
    }

    Reception::~Reception()
    {
    }

    void Reception::manageKitchen(Kitchen& kitchen)
    {
        while (true) {
            if (kitchen.isFull()) {
                std::cout << "Kitchen is full. Creating a new process..." << std::endl;
                kitchen.createProcess();
            }
            std::this_thread::sleep_for(std::chrono::seconds(5));
        }
    }

    void Reception::displayStatus(Kitchen& kitchen)
    {
        std::cout << "Kitchen Status" << std::endl;
        std::cout << "---------------------" << std::endl;
        std::cout << "Number of active processes: " << kitchen.getNbProcesses() << std::endl;
        std::cout << "Current orders: " << std::endl;

        const std::vector<Order>& orders = kitchen.getOrders();

        for (const auto& order : orders) {
            printPizzas(order.getPizzas(), std::cout);
        }
    }

    void Reception::orderPizzas(const std::vector<Pizza> pizzas, Kitchen& kitchen)
    {
        SharedMemory* sharedMemory = kitchen.getSharedMemory();
        kitchen.orderPizza(pizzas, sharedMemory);
    }

    static Pizza parseOrderBis(std::string order, double multiplier)
    {
        std::stringstream ss(order);
        std::string type_str, size_str, quantity_str;
        int quantity;
        PizzaType type;
        PizzaSize size;

        ss >> type_str;
        std::transform(type_str.begin(), type_str.end(), type_str.begin(), ::tolower);
        if (type_str == "regina")
            type = Regina;
        else if (type_str == "margarita")
            type = Margarita;
        else if (type_str == "americana")
            type = Americana;
        else if (type_str == "fantasia")
            type = Fantasia;
        else
            throw std::runtime_error("Invalid pizza name.\n");

        ss >> size_str;
        if (size_str == "S")
            size = S;
        else if (size_str == "M")
            size = M;
        else if (size_str == "L")
            size = L;
        else if (size_str == "XL")
            size = XL;
        else if (size_str == "XXL")
            size = XXL;
        else
            throw std::runtime_error("Invalid pizza size.\n");

        ss >> quantity_str;
        if (quantity_str[0] != 'x' || quantity_str.substr(1) > "9" || quantity_str.substr(1) < "1")
            throw std::runtime_error("Invalid pizza quantity.\n");
        quantity = std::stoi(quantity_str.substr(1));

        return Pizza(type, size, quantity, multiplier);
    }

    std::vector<Pizza> Reception::parseOrder(std::string order, double multiplier)
    {
        std::vector<std::string> tokens;
        std::stringstream ss(order);
        std::string orderToken;
        std::vector<Pizza> pizzas;

        while (std::getline(ss, orderToken, ';'))
            pizzas.push_back(parseOrderBis(orderToken, multiplier));
        std::cout << "Order completed!" << std::endl;
        return pizzas;
    }

    void Reception::run(double multiplier, int cooksPerKitchen, int restockTime)
    {
        SharedMemory* sharedMemory = static_cast<SharedMemory*>(mmap(NULL, sizeof(SharedMemory), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0));
        if (sharedMemory == MAP_FAILED) {
            std::cerr << "Error creating shared memory." << std::endl;
            exit(84);
        }
        Kitchen kitchen(cooksPerKitchen, sharedMemory);
        pid_t pid = fork();
        if (pid < 0) {
            std::cerr << "Fork failed" << std::endl;
            exit(84);
        }
        if (pid == 0) {
            kitchen.run();
            exit(0);
        }
        std::string input;
        std::vector<Pizza> pizzas;
        while (true) {
            std::cout << "Enter your order: ";
            std::getline(std::cin, input);
            if (std::cin.eof() || input == "exit") {
                break;
            }
            if (input == "status") {
                displayStatus(kitchen);
            } else {
                std::stringstream ss(input);
                std::string pizzaOrder;

                while (std::getline(ss, pizzaOrder, '\n')) {
                    try {
                        pizzas = parseOrder(pizzaOrder, multiplier);
                    } catch (const std::runtime_error& e) {
                        std::cerr << "\n /!\\ Error: " << e.what() << std::endl;
                        continue;
                    }
                }
                orderPizzas(pizzas, kitchen);
            }
        }
        munmap(sharedMemory, sizeof(SharedMemory));
    }

    std::string pizzaToString(const Pizza& pizza)
    {
        std::string type;
        switch (pizza.getType()) {
            case PizzaType::Regina:
                type = "Regina";
                break;
            case PizzaType::Margarita:
                type = "Margarita";
                break;
            case PizzaType::Americana:
                type = "Americana";
                break;
            case PizzaType::Fantasia:
                type = "Fantasia";
                break;
        }

        std::string size;
        switch (pizza.getSize()) {
            case PizzaSize::S:
                size = "S";
                break;
            case PizzaSize::M:
                size = "M";
                break;
            case PizzaSize::L:
                size = "L";
                break;
            case PizzaSize::XL:
                size = "XL";
                break;
            case PizzaSize::XXL:
                size = "XXL";
                break;
        }
        return "Pizza: " + type + " Size: " + size + " Quantity: " + std::to_string(pizza.getQuantity()) + " Multiplier: " + std::to_string(pizza.getMultiplier());
    }

    std::string pizzaToReceit(const Pizza& pizza)
    {
        std::string type;
        switch (pizza.getType()) {
            case PizzaType::Regina:
                type = "Regina";
                break;
            case PizzaType::Margarita:
                type = "Margarita";
                break;
            case PizzaType::Americana:
                type = "Americana";
                break;
            case PizzaType::Fantasia:
                type = "Fantasia";
                break;
        }

        std::string size;
        switch (pizza.getSize()) {
            case PizzaSize::S:
                size = "S";
                break;
            case PizzaSize::M:
                size = "M";
                break;
            case PizzaSize::L:
                size = "L";
                break;
            case PizzaSize::XL:
                size = "XL";
                break;
            case PizzaSize::XXL:
                size = "XXL";
                break;
        }
        return "Pizza: " + type + " Size: " + size + " Quantity: " + std::to_string(pizza.getQuantity());
    }

    std::string pizzaVectorToString(const std::vector<Pizza>& pizzas)
    {
        if (pizzas.empty()) {
            return "No pizzas";
        } else {
            std::stringstream ss;
            ss << "Pizzas: [";
            for (size_t i = 0; i < pizzas.size(); ++i) {
                ss << pizzaToString(pizzas[i]);
                if (i != pizzas.size() - 1)
                    ss << ",";
            }
            ss << "]";
            return ss.str();
        }
    }

    void printPizzas(const std::vector<Pizza>& pizzas, std::ostream& os)
    {
        for (const auto& pizza : pizzas) {
            os << pizzaToString(pizza) << std::endl;
        }
    }

    bool directoryExists(const std::string& path)
    {
        struct stat info;
        return stat(path.c_str(), &info) == 0 && (info.st_mode & S_IFDIR) != 0;
    }

    void fileExists(int& id)
    {
        std::string directoryPath = "orders";

        if (!directoryExists(directoryPath)) {
            if (CREATE_DIRECTORY(directoryPath.c_str()) != 0) {
                std::cerr << "Failed to create directory." << std::endl;
            }
        }
        std::ifstream file("orders/order_#" + std::to_string(id) + ".txt");
        if (file.is_open()) {
            file.close();
            id++;
            fileExists(id);
        }
    }

    void printOrderCompleted(const Order& order)
    {
        static int id = 1;
        fileExists(id);
        std::vector<Pizza> pizzas = order.getPizzas();

        std::ofstream file("orders/order_#" + std::to_string(id) + ".txt");
        if (file.is_open()) {
            file << "---------------------" << std::endl;
            file << "Order completed: " << std::endl;
            file << "Order ID: " << id << std::endl;
            file << "Pizzas: " << std::endl;
            for (const auto& pizza : pizzas) {
                file << pizzaToReceit(pizza) << std::endl;
            }
            file << "---------------------" << std::endl;
        }
    }
}
