#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

// Прототипы функций
void printMatrix(int** matrix, int rows, int cols);
int** createMatrix(int rows, int cols);
void deleteMatrix(int** matrix, int rows);
void fillMatrixRandom(int** matrix, int rows, int cols, int min = 1, int max = 100);

// Задание 1: Добавление столбца
int** addColumn(int** matrix, int rows, int& cols, int position) {
    // Проверка корректности позиции
    if (position < 0 || position > cols) {
        cout << "Неверная позиция для добавления столбца!" << endl;
        return matrix;
    }
    
    // Создаем новую матрицу с увеличенным количеством столбцов
    int** newMatrix = new int*[rows];
    for (int i = 0; i < rows; i++) {
        newMatrix[i] = new int[cols + 1];
    }
    
    // Копируем данные со сдвигом
    for (int i = 0; i < rows; i++) {
        int newCol = 0;
        for (int j = 0; j < cols; j++) {
            if (j == position) {
                // Вставляем новый столбец со случайными значениями
                newMatrix[i][newCol++] = rand() % 100;
            }
            newMatrix[i][newCol++] = matrix[i][j];
        }
        // Если позиция в конце
        if (position == cols) {
            newMatrix[i][newCol] = rand() % 100;
        }
    }
    
    // Увеличиваем счетчик столбцов
    cols++;
    
    // Удаляем старую матрицу
    deleteMatrix(matrix, rows);
    
    return newMatrix;
}

// Задание 2: Удаление столбца
int** deleteColumn(int** matrix, int rows, int& cols, int position) {
    // Проверка корректности позиции и наличия столбцов
    if (position < 0 || position >= cols || cols <= 1) {
        cout << "Неверная позиция для удаления или нельзя удалить последний столбец!" << endl;
        return matrix;
    }
    
    // Создаем новую матрицу с уменьшенным количеством столбцов
    int** newMatrix = new int*[rows];
    for (int i = 0; i < rows; i++) {
        newMatrix[i] = new int[cols - 1];
    }
    
    // Копируем данные, пропуская удаляемый столбец
    for (int i = 0; i < rows; i++) {
        int newCol = 0;
        for (int j = 0; j < cols; j++) {
            if (j != position) {
                newMatrix[i][newCol++] = matrix[i][j];
            }
        }
    }
    
    // Уменьшаем счетчик столбцов
    cols--;
    
    // Удаляем старую матрицу
    deleteMatrix(matrix, rows);
    
    return newMatrix;
}

// Задание 3: Циклический сдвиг
void cyclicShift(int** matrix, int rows, int cols, int shiftCount, char direction, char axis) {
    // Проверка параметров
    if (shiftCount <= 0) {
        cout << "Количество сдвигов должно быть положительным!" << endl;
        return;
    }
    
    // Нормализуем количество сдвигов
    shiftCount = shiftCount % (axis == 'r' ? rows : cols);
    if (shiftCount == 0) return;
    
    // Временный массив для хранения данных
    int* temp = new int[axis == 'r' ? cols : rows];
    
    if (axis == 'r') { // Сдвиг строк
        for (int i = 0; i < rows; i++) {
            if (direction == 'l') { // Сдвиг влево
                // Сохраняем первые shiftCount элементов
                for (int j = 0; j < shiftCount; j++) {
                    temp[j] = matrix[i][j];
                }
                // Сдвигаем остальные элементы
                for (int j = shiftCount; j < cols; j++) {
                    matrix[i][j - shiftCount] = matrix[i][j];
                }
                // Восстанавливаем сохраненные элементы в конец
                for (int j = 0; j < shiftCount; j++) {
                    matrix[i][cols - shiftCount + j] = temp[j];
                }
            } else { // Сдвиг вправо
                // Сохраняем последние shiftCount элементов
                for (int j = 0; j < shiftCount; j++) {
                    temp[j] = matrix[i][cols - shiftCount + j];
                }
                // Сдвигаем остальные элементы
                for (int j = cols - 1; j >= shiftCount; j--) {
                    matrix[i][j] = matrix[i][j - shiftCount];
                }
                // Восстанавливаем сохраненные элементы в начало
                for (int j = 0; j < shiftCount; j++) {
                    matrix[i][j] = temp[j];
                }
            }
        }
    } else { // Сдвиг столбцов
        for (int j = 0; j < cols; j++) {
            if (direction == 'u') { // Сдвиг вверх
                // Сохраняем первые shiftCount элементов
                for (int i = 0; i < shiftCount; i++) {
                    temp[i] = matrix[i][j];
                }
                // Сдвигаем остальные элементы
                for (int i = shiftCount; i < rows; i++) {
                    matrix[i - shiftCount][j] = matrix[i][j];
                }
                // Восстанавливаем сохраненные элементы в конец
                for (int i = 0; i < shiftCount; i++) {
                    matrix[rows - shiftCount + i][j] = temp[i];
                }
            } else { // Сдвиг вниз
                // Сохраняем последние shiftCount элементов
                for (int i = 0; i < shiftCount; i++) {
                    temp[i] = matrix[rows - shiftCount + i][j];
                }
                // Сдвигаем остальные элементы
                for (int i = rows - 1; i >= shiftCount; i--) {
                    matrix[i][j] = matrix[i - shiftCount][j];
                }
                // Восстанавливаем сохраненные элементы в начало
                for (int i = 0; i < shiftCount; i++) {
                    matrix[i][j] = temp[i];
                }
            }
        }
    }
    
    delete[] temp;
}

// Вспомогательные функции
int** createMatrix(int rows, int cols) {
    int** matrix = new int*[rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new int[cols];
    }
    return matrix;
}

void deleteMatrix(int** matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

void fillMatrixRandom(int** matrix, int rows, int cols, int min, int max) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = rand() % (max - min + 1) + min;
        }
    }
}

void printMatrix(int** matrix, int rows, int cols) {
    cout << "\nМатрица " << rows << "x" << cols << ":\n";
    cout << string(cols * 5 + 1, '-') << endl;
    
    for (int i = 0; i < rows; i++) {
        cout << "|";
        for (int j = 0; j < cols; j++) {
            cout << setw(4) << matrix[i][j] << "|";
        }
        cout << endl;
        cout << string(cols * 5 + 1, '-') << endl;
    }
    cout << endl;
}

// Демонстрационная функция
void demo() {
    srand(time(0));
    
    int rows, cols;
    cout << "Введите количество строк матрицы: ";
    cin >> rows;
    cout << "Введите количество столбцов матрицы: ";
    cin >> cols;
    
    // Создаем и заполняем матрицу
    int** matrix = createMatrix(rows, cols);
    fillMatrixRandom(matrix, rows, cols);
    
    cout << "\n=== ИСХОДНАЯ МАТРИЦА ===";
    printMatrix(matrix, rows, cols);
    
    // Демонстрация задания 1: добавление столбца
    cout << "\n=== ЗАДАНИЕ 1: ДОБАВЛЕНИЕ СТОЛБЦА ===" << endl;
    int addPos;
    cout << "Введите позицию для добавления столбца (0-" << cols << "): ";
    cin >> addPos;
    
    matrix = addColumn(matrix, rows, cols, addPos);
    cout << "После добавления столбца:";
    printMatrix(matrix, rows, cols);
    
    // Демонстрация задания 2: удаление столбца
    cout << "\n=== ЗАДАНИЕ 2: УДАЛЕНИЕ СТОЛБЦА ===" << endl;
    int delPos;
    cout << "Введите позицию для удаления столбца (0-" << cols - 1 << "): ";
    cin >> delPos;
    
    matrix = deleteColumn(matrix, rows, cols, delPos);
    cout << "После удаления столбца:";
    printMatrix(matrix, rows, cols);
    
    // Демонстрация задания 3: циклический сдвиг
    cout << "\n=== ЗАДАНИЕ 3: ЦИКЛИЧЕСКИЙ СДВИГ ===" << endl;
    
    // Сначала восстанавливаем оригинальные размеры для демонстрации
    int originalRows = rows, originalCols = cols;
    deleteMatrix(matrix, rows);
    rows = originalRows;
    cols = originalCols;
    matrix = createMatrix(rows, cols);
    fillMatrixRandom(matrix, rows, cols);
    
    cout << "\nНовая матрица для демонстрации сдвига:";
    printMatrix(matrix, rows, cols);
    
    char axis, direction;
    int shiftCount;
    
    cout << "Выберите ось для сдвига (r - строки, c - столбцы): ";
    cin >> axis;
    
    if (axis == 'r') {
        cout << "Выберите направление сдвига строк (l - влево, r - вправо): ";
        cin >> direction;
    } else {
        cout << "Выберите направление сдвига столбцов (u - вверх, d - вниз): ";
        cin >> direction;
    }
    
    cout << "Введите количество сдвигов: ";
    cin >> shiftCount;
    
    cyclicShift(matrix, rows, cols, shiftCount, direction, axis);
    
    cout << "\nПосле циклического сдвига:";
    printMatrix(matrix, rows, cols);
    
    // Освобождаем память
    deleteMatrix(matrix, rows);
}

// Меню для интерактивного тестирования
void menu() {
    srand(time(0));
    
    int** matrix = nullptr;
    int rows = 0, cols = 0;
    int choice;
    
    do {
        cout << "\n========================================" << endl;
        cout << "         МЕНЮ УПРАВЛЕНИЯ МАТРИЦЕЙ       " << endl;
        cout << "========================================" << endl;
        cout << "1. Создать новую матрицу" << endl;
        cout << "2. Вывести матрицу" << endl;
        cout << "3. Добавить столбец (Задание 1)" << endl;
        cout << "4. Удалить столбец (Задание 2)" << endl;
        cout << "5. Циклический сдвиг (Задание 3)" << endl;
        cout << "6. Запустить демонстрацию всех заданий" << endl;
        cout << "0. Выход" << endl;
        cout << "========================================" << endl;
        cout << "Выберите действие: ";
        cin >> choice;
        
        switch(choice) {
            case 1: {
                if (matrix != nullptr) {
                    deleteMatrix(matrix, rows);
                }
                cout << "Введите количество строк: ";
                cin >> rows;
                cout << "Введите количество столбцов: ";
                cin >> cols;
                matrix = createMatrix(rows, cols);
                fillMatrixRandom(matrix, rows, cols);
                cout << "Матрица создана и заполнена случайными числами." << endl;
                break;
            }
            case 2: {
                if (matrix == nullptr) {
                    cout << "Сначала создайте матрицу!" << endl;
                } else {
                    printMatrix(matrix, rows, cols);
                }
                break;
            }
            case 3: {
                if (matrix == nullptr) {
                    cout << "Сначала создайте матрицу!" << endl;
                } else {
                    int pos;
                    cout << "Текущий размер: " << rows << "x" << cols << endl;
                    cout << "Введите позицию для добавления столбца (0-" << cols << "): ";
                    cin >> pos;
                    matrix = addColumn(matrix, rows, cols, pos);
                    cout << "Столбец добавлен. Новый размер: " << rows << "x" << cols << endl;
                }
                break;
            }
            case 4: {
                if (matrix == nullptr) {
                    cout << "Сначала создайте матрицу!" << endl;
                } else {
                    int pos;
                    cout << "Текущий размер: " << rows << "x" << cols << endl;
                    cout << "Введите позицию для удаления столбца (0-" << cols - 1 << "): ";
                    cin >> pos;
                    matrix = deleteColumn(matrix, rows, cols, pos);
                    cout << "Столбец удален. Новый размер: " << rows << "x" << cols << endl;
                }
                break;
            }
            case 5: {
                if (matrix == nullptr) {
                    cout << "Сначала создайте матрицу!" << endl;
                } else {
                    char axis, direction;
                    int shiftCount;
                    
                    cout << "Выберите ось для сдвига (r - строки, c - столбцы): ";
                    cin >> axis;
                    
                    if (axis == 'r') {
                        cout << "Выберите направление сдвига строк (l - влево, r - вправо): ";
                        cin >> direction;
                    } else {
                        cout << "Выберите направление сдвига столбцов (u - вверх, d - вниз): ";
                        cin >> direction;
                    }
                    
                    cout << "Введите количество сдвигов: ";
                    cin >> shiftCount;
                    
                    cyclicShift(matrix, rows, cols, shiftCount, direction, axis);
                    cout << "Сдвиг выполнен." << endl;
                }
                break;
            }
            case 6: {
                demo();
                matrix = nullptr; // Матрица удалена в demo()
                rows = cols = 0;
                break;
            }
            case 0: {
                if (matrix != nullptr) {
                    deleteMatrix(matrix, rows);
                }
                cout << "Выход из программы." << endl;
                break;
            }
            default:
                cout << "Неверный выбор!" << endl;
        }
    } while (choice != 0);
}

int main() {
    // Устанавливаем русскую локаль для корректного отображения
    setlocale(LC_ALL, "Russian");
    
    cout << "========================================" << endl;
    cout << "   РАБОТА С ДВУМЕРНЫМИ МАССИВАМИ (C++)  " << endl;
    cout << "========================================" << endl;
    
    int mode;
    cout << "Выберите режим работы:" << endl;
    cout << "1. Интерактивное меню" << endl;
    cout << "2. Автоматическая демонстрация" << endl;
    cout << "Ваш выбор: ";
    cin >> mode;
    
    if (mode == 1) {
        menu();
    } else {
        demo();
    }
    
    return 0;
}
