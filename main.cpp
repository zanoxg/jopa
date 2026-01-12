#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

// Возможные ходы коня (8 направлений)
const int moves[8][2] = {
    {2, 1}, {1, 2}, {-1, 2}, {-2, 1},
    {-2, -1}, {-1, -2}, {1, -2}, {2, -1}
};

class KnightTour {
private:
    int boardSize;            // Размер доски (6x6, 8x8 и т.д.)
    vector<vector<int>> board; // Шахматная доска
    int totalCells;           // Общее количество клеток
    bool solutionFound;       // Флаг нахождения решения

public:
    KnightTour(int size) : boardSize(size), totalCells(size * size), solutionFound(false) {
        // Инициализация доски
        board.resize(size, vector<int>(size, 0));
    }

    // Проверка, находится ли клетка в пределах доски
    bool isSafe(int x, int y) {
        return (x >= 0 && x < boardSize && y >= 0 && y < boardSize && board[x][y] == 0);
    }

    // Вывод доски с номерами ходов
    void printBoard() {
        cout << "\nМаршрут коня:\n";
        for (int i = 0; i < boardSize; i++) {
            for (int j = 0; j < boardSize; j++) {
                cout << setw(3) << board[i][j] << " ";
            }
            cout << endl;
        }
    }

    // Рекурсивная функция для обхода доски
    bool solveKnightTour(int x, int y, int moveCount) {
        // Помечаем текущую клетку
        board[x][y] = moveCount;

        // Если все клетки посещены
        if (moveCount == totalCells) {
            solutionFound = true;
            return true;
        }

        // Пробуем все возможные ходы из текущей позиции
        for (int i = 0; i < 8; i++) {
            int nextX = x + moves[i][0];
            int nextY = y + moves[i][1];

            if (isSafe(nextX, nextY)) {
                if (solveKnightTour(nextX, nextY, moveCount + 1)) {
                    return true;
                }
            }
        }

        // Если ни один ход не привел к решению, откатываемся
        board[x][y] = 0;
        return false;
    }

    // Функция для запуска поиска пути
    bool findTour(int startX, int startY) {
        // Проверка корректности начальных координат
        if (!isSafe(startX, startY)) {
            cout << "Некорректные начальные координаты!\n";
            return false;
        }

        cout << "Поиск решения для доски " << boardSize << "x" << boardSize 
             << " с начальной позиции (" << startX << ", " << startY << ")...\n";

        // Запуск рекурсивного поиска
        if (solveKnightTour(startX, startY, 1)) {
            printBoard();
            return true;
        } else {
            cout << "Решение не найдено!\n";
            return false;
        }
    }

    // Геттер для флага решения
    bool isSolutionFound() const {
        return solutionFound;
    }
};

int main() {
    int boardSize;
    int startX, startY;

    cout << "=== ЗАДАЧА ОБХОДА ДОСКИ КОНЕМ ===\n";
    cout << "Рекомендуется начать с доски 6x6\n";
    cout << "Введите размер доски (5-8): ";
    cin >> boardSize;

    if (boardSize < 5 || boardSize > 8) {
        cout << "Размер доски должен быть от 5 до 8!\n";
        return 1;
    }

    // Шахматная доска: координаты от 0 до boardSize-1
    cout << "\nКоординаты вводятся от 0 до " << boardSize - 1 << endl;
    cout << "Введите начальную координату X (строка): ";
    cin >> startX;
    cout << "Введите начальную координату Y (столбец): ";
    cin >> startY;

    // Создаем объект и ищем решение
    KnightTour tour(boardSize);
    
    // Засекаем время для больших досок (опционально)
    tour.findTour(startX, startY);

    cout << "\nПримечание: числа на доске обозначают порядок посещения клеток конем.\n";
    cout << "Конь начинает с клетки с цифрой 1 и заканчивает на клетке с цифрой " 
         << boardSize * boardSize << ".\n";

    return 0;
}
