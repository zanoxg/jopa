#include <iostream>
#include <vector>
#include <limits>

// Задание 1: Анализ числа
void analyzeNumber(int num) {
    int countDigits = 0;
    int sumDigits = 0;
    int zeroCount = 0;
    
    // Обработка числа
    while (num != 0) {
        int digit = num % 10;
        sumDigits += digit;
        if (digit == 0) {
            zeroCount++;
        }
        countDigits++;
        num /= 10;
    }

    double average = countDigits > 0 ? static_cast<double>(sumDigits) / countDigits : 0;

    std::cout << "Количество цифр: " << countDigits << std::endl;
    std::cout << "Сумма цифр: " << sumDigits << std::endl;
    std::cout << "Среднее арифметическое: " << average << std::endl;
    std::cout << "Количество нулей: " << zeroCount << std::endl;
}

// Задание 2: Программа расчета заказа в кафетерии
void calculateOrder(int numPeople) {
    // Меню кафетерия
    std::vector<std::string> drinks = {"Кофе", "Чай", "Сок"};
    std::vector<std::string> desserts = {"Пирог", "Кекс", "Печенье"};
    std::vector<int> drinksPrices = {100, 50, 80}; // Цена напитков
    std::vector<int> dessertsPrices = {120, 60, 40}; // Цена десертов

    int totalOrder = 0;

    for (int i = 0; i < numPeople; ++i) {
        std::cout << "\nЗаказ для клиента #" << i + 1 << ":\n";
        int personTotal = 0;

        // Напитки
        std::cout << "Выберите напитки (введите номер, 0 для завершения):\n";
        for (int i = 0; i < drinks.size(); ++i) {
            std::cout << i + 1 << ". " << drinks[i] << " - " << drinksPrices[i] << " руб.\n";
        }

        while (true) {
            int choice;
            std::cout << "Ваш выбор (0 для завершения): ";
            std::cin >> choice;
            if (choice == 0) break;
            if (choice >= 1 && choice <= drinks.size()) {
                personTotal += drinksPrices[choice - 1];
            } else {
                std::cout << "Неверный выбор. Попробуйте снова.\n";
            }
        }

        // Десерты
        std::cout << "Выберите десерты (введите номер, 0 для завершения):\n";
        for (int i = 0; i < desserts.size(); ++i) {
            std::cout << i + 1 << ". " << desserts[i] << " - " << dessertsPrices[i] << " руб.\n";
        }

        while (true) {
            int choice;
            std::cout << "Ваш выбор (0 для завершения): ";
            std::cin >> choice;
            if (choice == 0) break;
            if (choice >= 1 && choice <= desserts.size()) {
                personTotal += dessertsPrices[choice - 1];
            } else {
                std::cout << "Неверный выбор. Попробуйте снова.\n";
            }
        }

        totalOrder += personTotal;
        std::cout << "Сумма заказа для клиента #" << i + 1 << ": " << personTotal << " руб.\n";
    }

    std::cout << "\nОбщая сумма заказа для всей компании: " << totalOrder << " руб.\n";
}

int main() {
    int choice;

    while (true) {
        std::cout << "\nМеню:\n";
        std::cout << "1. Анализ числа\n";
        std::cout << "2. Расчет заказа в кафетерии\n";
        std::cout << "0. Выход\n";
        std::cout << "Ваш выбор: ";
        std::cin >> choice;

        if (choice == 1) {
            int num;
            std::cout << "Введите число: ";
            std::cin >> num;
            analyzeNumber(num);
        } else if (choice == 2) {
            int numPeople;
            std::cout << "На сколько человек заказ? ";
            std::cin >> numPeople;
            calculateOrder(numPeople);
        } else if (choice == 0) {
            std::cout << "Выход из программы.\n";
            break;
        } else {
            std::cout << "Неверный выбор. Попробуйте снова.\n";
        }
    }

    return 0;
}
