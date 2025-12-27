#include <iostream>
#include <vector>
#include <set>

// Задание 1: Подсчет чисел с одинаковыми цифрами в диапазоне от 100 до 999
int countNumbersWithSameDigits() {
    int count = 0;
    
    for (int num = 100; num <= 999; ++num) {
        int hundreds = num / 100;
        int tens = (num / 10) % 10;
        int ones = num % 10;
        
        if (hundreds == tens || tens == ones || hundreds == ones) {
            ++count;
        }
    }
    
    return count;
}

// Задание 2: Подсчет чисел с разными цифрами в диапазоне от 100 до 999
int countNumbersWithDifferentDigits() {
    int count = 0;
    
    for (int num = 100; num <= 999; ++num) {
        int hundreds = num / 100;
        int tens = (num / 10) % 10;
        int ones = num % 10;
        
        if (hundreds != tens && tens != ones && hundreds != ones) {
            ++count;
        }
    }
    
    return count;
}

// Задание 3: Удаление цифр 3 и 6 из введенного числа
int removeDigits36(int num) {
    int result = 0;
    int place = 1;
    
    while (num > 0) {
        int digit = num % 10;
        num /= 10;
        
        if (digit != 3 && digit != 6) {
            result += digit * place;
            place *= 10;
        }
    }
    
    return result;
}

int main() {
    // Задание 1: Подсчет чисел с одинаковыми цифрами
    std::cout << "Count of numbers with same digits: " << countNumbersWithSameDigits() << std::endl;
    
    // Задание 2: Подсчет чисел с разными цифрами
    std::cout << "Count of numbers with different digits: " << countNumbersWithDifferentDigits() << std::endl;
    
    // Задание 3: Удаление цифр 3 и 6
    int number;
    std::cout << "Enter a number: ";
    std::cin >> number;
    
    std::cout << "Number after removing 3 and 6: " << removeDigits36(number) << std::endl;
    
    return 0;
}
