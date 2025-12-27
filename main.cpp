#include <iostream>
#include <cstdlib>
#include <ctime>

// Задание 1: Копирование элементов из одного массива в два массива по 5 элементов
void copyArray(int* src, int* dest1, int* dest2) {
    for (int i = 0; i < 5; ++i) {
        dest1[i] = src[i];
        dest2[i] = src[i + 5];
    }
}

// Задание 2: Поэлементная сумма двух массивов с занесением результата в третий
void sumArrays(int* arr1, int* arr2, int* result, int size) {
    for (int i = 0; i < size; ++i) {
        result[i] = arr1[i] + arr2[i];
    }
}

int main() {
    srand(time(0));

    // Задание 1: Генерация и копирование элементов массива
    int array1[10];
    for (int i = 0; i < 10; ++i) {
        array1[i] = rand() % 100;  // Сгенерировать число в диапазоне от 0 до 99
    }
    
    int array2[5], array3[5];
    copyArray(array1, array2, array3);

    std::cout << "Original Array: ";
    for (int i = 0; i < 10; ++i) {
        std::cout << array1[i] << " ";
    }
    std::cout << "\nArray 1 (First 5 elements): ";
    for (int i = 0; i < 5; ++i) {
        std::cout << array2[i] << " ";
    }
    std::cout << "\nArray 2 (Last 5 elements): ";
    for (int i = 0; i < 5; ++i) {
        std::cout << array3[i] << " ";
    }
    std::cout << std::endl;

    // Задание 2: Генерация двух массивов и поэлементная сумма
    int array4[5], array5[5], result[5];
    for (int i = 0; i < 5; ++i) {
        array4[i] = rand() % 100;
        array5[i] = rand() % 100;
    }

    sumArrays(array4, array5, result, 5);

    std::cout << "\nArray 4: ";
    for (int i = 0; i < 5; ++i) {
        std::cout << array4[i] << " ";
    }
    
    std::cout << "\nArray 5: ";
    for (int i = 0; i < 5; ++i) {
        std::cout << array5[i] << " ";
    }
    
    std::cout << "\nSum of Array 4 and Array 5: ";
    for (int i = 0; i < 5; ++i) {
        std::cout << result[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
