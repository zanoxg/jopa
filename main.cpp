#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

// Задание 1: Нахождение минимального и максимального элементов в массиве
void findMinMax(const std::vector<int>& arr, int& minElem, int& maxElem) {
    minElem = arr[0];
    maxElem = arr[0];
    
    for (int num : arr) {
        if (num < minElem) minElem = num;
        if (num > maxElem) maxElem = num;
    }
}

// Задание 2: Сумма элементов массива, которые меньше указанного значения
int sumLessThan(const std::vector<int>& arr, int threshold) {
    int sum = 0;
    
    for (int num : arr) {
        if (num < threshold) sum += num;
    }
    
    return sum;
}

// Задание 3: Нахождение месяца с максимальной и минимальной прибылью в заданном диапазоне
void findMaxMinProfit(const std::vector<int>& profits, int startMonth, int endMonth, int& maxMonth, int& minMonth) {
    maxMonth = startMonth;
    minMonth = startMonth;
    
    for (int i = startMonth - 1; i < endMonth; ++i) {
        if (profits[i] > profits[maxMonth - 1]) maxMonth = i + 1;
        if (profits[i] < profits[minMonth - 1]) minMonth = i + 1;
    }
}

int main() {
    srand(time(0));

    // Пример использования Задания 1: Нахождение минимального и максимального элементов массива
    std::vector<int> arr = {10, 20, 5, 30, -10, 50, 40};
    int minElem, maxElem;
    findMinMax(arr, minElem, maxElem);
    std::cout << "Min: " << minElem << ", Max: " << maxElem << std::endl;

    // Пример использования Задания 2: Сумма элементов меньше указанного числа
    int threshold = 15;
    std::cout << "Sum of elements less than " << threshold << ": " << sumLessThan(arr, threshold) << std::endl;

    // Пример использования Задания 3: Нахождение месяца с максимальной и минимальной прибылью
    std::vector<int> profits = {200, 150, 180, 220, 190, 250, 270, 260, 230, 240, 210, 220};
    int startMonth = 3, endMonth = 6;
    int maxMonth, minMonth;
    findMaxMinProfit(profits, startMonth, endMonth, maxMonth, minMonth);
    std::cout << "Max profit month: " << maxMonth << ", Min profit month: " << minMonth << std::endl;

    return 0;
}
