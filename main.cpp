#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

// Функция для задания 1
void task1() {
    cout << "\n=== ЗАДАНИЕ 1 ===" << endl;
    cout << "Вычисление суммы целых чисел от a до 500" << endl;
    cout << "=========================================" << endl;
    
    int a;
    long long sum = 0;
    
    cout << "Введите целое число a: ";
    cin >> a;
    
    if (a > 500) {
        cout << "Ошибка: a должно быть меньше или равно 500!" << endl;
        return;
    }
    
    // Вычисление суммы циклом
    for (int i = a; i <= 500; i++) {
        sum += i;
    }
    
    cout << "Сумма чисел от " << a << " до 500 (через цикл): " << sum << endl;
    
    // Альтернативное решение через формулу арифметической прогрессии
    int n = 500 - a + 1;
    long long sum_formula = (a + 500) * n / 2;
    cout << "Сумма чисел от " << a << " до 500 (по формуле): " << sum_formula << endl;
}

// Функция для задания 2
void task2() {
    cout << "\n=== ЗАДАНИЕ 2 ===" << endl;
    cout << "Вычисление x в степени y" << endl;
    cout << "======================" << endl;
    
    int x, y;
    
    cout << "Введите целое число x: ";
    cin >> x;
    cout << "Введите целое число y (неотрицательное): ";
    cin >> y;
    
    if (y < 0) {
        cout << "Ошибка: степень y должна быть неотрицательной!" << endl;
        return;
    }
    
    // Способ 1: Использование цикла
    long long result_loop = 1;
    for (int i = 0; i < y; i++) {
        result_loop *= x;
    }
    
    // Способ 2: Использование функции pow() из cmath
    double result_pow = pow(x, y);
    
    cout << "Результат (через цикл): " << x << "^" << y << " = " << result_loop << endl;
    cout << "Результат (через pow()): " << x << "^" << y << " = " << fixed << result_pow << endl;
}

// Функция для задания 3
void task3() {
    cout << "\n=== ЗАДАНИЕ 3 ===" << endl;
    cout << "Среднее арифметическое чисел от 1 до 1000" << endl;
    cout << "=========================================" << endl;
    
    long long sum = 0;
    int count = 1000;
    
    // Вычисляем сумму
    for (int i = 1; i <= count; i++) {
        sum += i;
    }
    
    // Вычисляем среднее арифметическое
    double average = static_cast<double>(sum) / count;
    
    cout << "Сумма чисел от 1 до 1000: " << sum << endl;
    cout << "Количество чисел: " << count << endl;
    cout << "Среднее арифметическое: " << fixed << setprecision(2) << average << endl;
    
    // Альтернативное решение через формулу
    double average_formula = (1 + 1000) / 2.0;
    cout << "Среднее арифметическое (по формуле): " << average_formula << endl;
}

// Функция для задания 4
void task4() {
    cout << "\n=== ЗАДАНИЕ 4 ===" << endl;
    cout << "Произведение всех целых чисел от a до 20" << endl;
    cout << "=========================================" << endl;
    
    int a;
    long long product = 1; // Используем long long для больших произведений
    
    cout << "Введите целое число a (1 <= a <= 20): ";
    cin >> a;
    
    if (a < 1 || a > 20) {
        cout << "Ошибка: a должно быть в диапазоне от 1 до 20!" << endl;
        return;
    }
    
    // Вычисляем произведение
    for (int i = a; i <= 20; i++) {
        product *= i;
        // Проверка на переполнение (примерная)
        if (product < 0) {
            cout << "Внимание: возможное переполнение!" << endl;
            break;
        }
    }
    
    cout << "Произведение чисел от " << a << " до 20: " << product << endl;
    
    // Для небольших значений выведем все множители
    if (a <= 10) {
        cout << "Множители: ";
        for (int i = a; i <= 20; i++) {
            cout << i;
            if (i < 20) cout << " * ";
        }
        cout << endl;
    }
}

// Функция для задания 5
void task5() {
    cout << "\n=== ЗАДАНИЕ 5 ===" << endl;
    cout << "Таблица умножения на k" << endl;
    cout << "======================" << endl;
    
    int k;
    
    cout << "Введите номер варианта k: ";
    cin >> k;
    
    cout << "\nТаблица умножения на " << k << ":" << endl;
    cout << "---------------------" << endl;
    
    // Выводим таблицу умножения от 2 до 9 (или другой диапазон)
    for (int i = 2; i <= 9; i++) {
        cout << k << " x " << i << " = " << (k * i) << endl;
    }
    
    // Дополнительно: таблица в более красивом формате
    cout << "\nТаблица умножения на " << k << " (форматированная):" << endl;
    cout << "--------------------------------" << endl;
    for (int i = 1; i <= 10; i++) {
        cout << setw(2) << k << " x " << setw(2) << i << " = " << setw(3) << (k * i);
        if (i % 2 == 0) cout << endl;
        else cout << "   |   ";
    }
}

// Главная функция с меню
int main() {
    int choice;
    
    do {
        cout << "\n========================================" << endl;
        cout << "          МЕНЮ ВЫБОРА ЗАДАНИЙ           " << endl;
        cout << "========================================" << endl;
        cout << "1. Задание 1 - Сумма чисел от a до 500" << endl;
        cout << "2. Задание 2 - Возведение в степень" << endl;
        cout << "3. Задание 3 - Среднее арифметическое (1-1000)" << endl;
        cout << "4. Задание 4 - Произведение чисел от a до 20" << endl;
        cout << "5. Задание 5 - Таблица умножения" << endl;
        cout << "6. Выполнить все задания" << endl;
        cout << "0. Выход" << endl;
        cout << "========================================" << endl;
        cout << "Выберите задание (0-6): ";
        cin >> choice;
        
        switch(choice) {
            case 1:
                task1();
                break;
            case 2:
                task2();
                break;
            case 3:
                task3();
                break;
            case 4:
                task4();
                break;
            case 5:
                task5();
                break;
            case 6:
                cout << "\nВыполнение всех заданий:\n";
                task1();
                task2();
                task3();
                task4();
                task5();
                break;
            case 0:
                cout << "Выход из программы." << endl;
                break;
            default:
                cout << "Неверный выбор! Попробуйте снова." << endl;
        }
        
        if (choice != 0) {
            cout << "\nНажмите Enter для продолжения...";
            cin.ignore();
            cin.get();
        }
        
    } while (choice != 0);
    
    return 0;
}
