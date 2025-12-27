#include <iostream>
#include <vector>

bool isLeapYear(int year) {
    return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

int daysBetween(int day1, int month1, int year1, int day2, int month2, int year2) {
    struct tm a = {0};
    struct tm b = {0};
    
    a.tm_year = year1 - 1900;
    a.tm_mon = month1 - 1;
    a.tm_mday = day1;
    
    b.tm_year = year2 - 1900;
    b.tm_mon = month2 - 1;
    b.tm_mday = day2;
    
    time_t time_a = mktime(&a);
    time_t time_b = mktime(&b);
    
    return difftime(time_b, time_a) / (60 * 60 * 24);
}

double average(const std::vector<int>& arr) {
    if (arr.empty()) return 0.0;
    
    double sum = 0;
    for (int num : arr) {
        sum += num;
    }
    
    return sum / arr.size();
}

void countElements(const std::vector<int>& arr, int& positive, int& negative, int& zero) {
    positive = negative = zero = 0;
    
    for (int num : arr) {
        if (num > 0) positive++;
        else if (num < 0) negative++;
        else zero++;
    }
}

int main() {
    // Пример использования функций
    
    // Задание 1: Разность между датами
    std::cout << daysBetween(1, 1, 2020, 1, 1, 2021) << std::endl;

    // Задание 2: Среднее арифметическое
    std::vector<int> arr = {1, 2, 3, 4, 5};
    std::cout << average(arr) << std::endl;
    
    // Задание 3: Количество положительных, отрицательных и нулевых элементов
    int positive = 0, negative = 0, zero = 0;
    countElements(arr, positive, negative, zero);
    std::cout << "Positive: " << positive << ", Negative: " << negative << ", Zero: " << zero << std::endl;
    
    return 0;
}

