#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

// Шаблонная функция для поиска максимума в массиве
template<typename T>
T findMax(const T* arr, int size) {
    if (size <= 0) {
        throw invalid_argument("Массив пуст");
    }
    T maxVal = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > maxVal) {
            maxVal = arr[i];
        }
    }
    return maxVal;
}

// Шаблонная функция для поиска минимума в массиве
template<typename T>
T findMin(const T* arr, int size) {
    if (size <= 0) {
        throw invalid_argument("Массив пуст");
    }
    T minVal = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] < minVal) {
            minVal = arr[i];
        }
    }
    return minVal;
}

// Шаблонная функция для сортировки массива (быстрая сортировка)
template<typename T>
void quickSort(T* arr, int left, int right) {
    if (left >= right) return;
    
    T pivot = arr[(left + right) / 2];
    int i = left, j = right;
    
    while (i <= j) {
        while (arr[i] < pivot) i++;
        while (arr[j] > pivot) j--;
        if (i <= j) {
            swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }
    
    if (left < j) quickSort(arr, left, j);
    if (i < right) quickSort(arr, i, right);
}

template<typename T>
void sortArray(T* arr, int size) {
    quickSort(arr, 0, size - 1);
}

// Шаблонная функция для двоичного поиска (массив должен быть отсортирован)
template<typename T>
int binarySearch(const T* arr, int size, const T& value) {
    int left = 0, right = size - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == value) {
            return mid;
        } else if (arr[mid] < value) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return -1; // не найдено
}

// Шаблонная функция для замены элемента массива
template<typename T>
void replaceElement(T* arr, int size, int index, const T& newValue) {
    if (index < 0 || index >= size) {
        throw out_of_range("Индекс вне границ массива");
    }
    arr[index] = newValue;
}

// Демонстрация работы шаблонных функций
void demonstrateTemplateFunctions() {
    cout << "========== ДЕМОНСТРАЦИЯ ШАБЛОННЫХ ФУНКЦИЙ ==========" << endl;
    
    // Тест с целыми числами
    int intArr[] = {5, 2, 8, 1, 9, 3, 7, 4, 6};
    int intSize = sizeof(intArr) / sizeof(intArr[0]);
    
    cout << "Исходный массив int: ";
    for (int i = 0; i < intSize; i++) cout << intArr[i] << " ";
    cout << endl;
    
    cout << "Максимум: " << findMax(intArr, intSize) << endl;
    cout << "Минимум: " << findMin(intArr, intSize) << endl;
    
    sortArray(intArr, intSize);
    cout << "Отсортированный массив: ";
    for (int i = 0; i < intSize; i++) cout << intArr[i] << " ";
    cout << endl;
    
    int searchVal = 7;
    int pos = binarySearch(intArr, intSize, searchVal);
    cout << "Поиск значения " << searchVal << ": " << (pos != -1 ? "найден на позиции " + to_string(pos) : "не найден") << endl;
    
    replaceElement(intArr, intSize, 2, 99);
    cout << "После замены элемента 2 на 99: ";
    for (int i = 0; i < intSize; i++) cout << intArr[i] << " ";
    cout << endl;
    
    // Тест с числами с плавающей точкой
    double doubleArr[] = {5.5, 2.2, 8.8, 1.1, 9.9};
    int doubleSize = sizeof(doubleArr) / sizeof(doubleArr[0]);
    
    cout << "\nМассив double: ";
    for (int i = 0; i < doubleSize; i++) cout << doubleArr[i] << " ";
    cout << endl;
    cout << "Максимум: " << findMax(doubleArr, doubleSize) << endl;
    cout << "Минимум: " << findMin(doubleArr, doubleSize) << endl;
}

template<typename T>
class Matrix {
private:
    T** data;
    int rows;
    int cols;
    
public:
    // Конструкторы
    Matrix(int r = 0, int c = 0) : rows(r), cols(c) {
        if (rows > 0 && cols > 0) {
            allocateMemory();
        } else {
            data = nullptr;
        }
    }
    
    // Конструктор копирования
    Matrix(const Matrix& other) : rows(other.rows), cols(other.cols) {
        allocateMemory();
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                data[i][j] = other.data[i][j];
            }
        }
    }
    
    // Деструктор
    ~Matrix() {
        freeMemory();
    }
    
    // Оператор присваивания
    Matrix& operator=(const Matrix& other) {
        if (this != &other) {
            freeMemory();
            rows = other.rows;
            cols = other.cols;
            allocateMemory();
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    data[i][j] = other.data[i][j];
                }
            }
        }
        return *this;
    }
    
    // Выделение памяти
    void allocateMemory() {
        data = new T*[rows];
        for (int i = 0; i < rows; i++) {
            data[i] = new T[cols];
        }
    }
    
    // Очистка памяти
    void freeMemory() {
        if (data) {
            for (int i = 0; i < rows; i++) {
                delete[] data[i];
            }
            delete[] data;
            data = nullptr;
        }
    }
    
    // Заполнение с клавиатуры
    void fillFromKeyboard() {
        cout << "Введите элементы матрицы " << rows << "x" << cols << ":" << endl;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << "[" << i << "][" << j << "]: ";
                cin >> data[i][j];
            }
        }
    }
    
    // Заполнение случайными значениями
    void fillRandom(T minVal, T maxVal) {
        random_device rd;
        mt19937 gen(rd());
        
        if constexpr (is_integral<T>::value) {
            uniform_int_distribution<T> dist(minVal, maxVal);
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    data[i][j] = dist(gen);
                }
            }
        } else if constexpr (is_floating_point<T>::value) {
            uniform_real_distribution<T> dist(minVal, maxVal);
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    data[i][j] = dist(gen);
                }
            }
        }
    }
    
    // Отображение матрицы
    void display() const {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << data[i][j] << "\t";
            }
            cout << endl;
        }
    }
    
    // Арифметические операторы
    Matrix operator+(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols) {
            throw invalid_argument("Размеры матриц не совпадают");
        }
        
        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return result;
    }
    
    Matrix operator-(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols) {
            throw invalid_argument("Размеры матриц не совпадают");
        }
        
        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.data[i][j] = data[i][j] - other.data[i][j];
            }
        }
        return result;
    }
    
    Matrix operator*(const Matrix& other) const {
        if (cols != other.rows) {
            throw invalid_argument("Количество столбцов первой матрицы не равно количеству строк второй");
        }
        
        Matrix result(rows, other.cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < other.cols; j++) {
                result.data[i][j] = 0;
                for (int k = 0; k < cols; k++) {
                    result.data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }
        return result;
    }
    
    // Умножение на скаляр
    Matrix operator*(T scalar) const {
        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.data[i][j] = data[i][j] * scalar;
            }
        }
        return result;
    }
    
    // Составные операторы
    Matrix& operator+=(const Matrix& other) {
        *this = *this + other;
        return *this;
    }
    
    Matrix& operator-=(const Matrix& other) {
        *this = *this - other;
        return *this;
    }
    
    Matrix& operator*=(const Matrix& other) {
        *this = *this * other;
        return *this;
    }
    
    // Доступ к элементам
    T& operator()(int i, int j) {
        if (i < 0 || i >= rows || j < 0 || j >= cols) {
            throw out_of_range("Индекс вне границ матрицы");
        }
        return data[i][j];
    }
    
    const T& operator()(int i, int j) const {
        if (i < 0 || i >= rows || j < 0 || j >= cols) {
            throw out_of_range("Индекс вне границ матрицы");
        }
        return data[i][j];
    }
    
    // Геттеры
    int getRows() const { return rows; }
    int getCols() const { return cols; }
    
    // Транспонирование
    Matrix transpose() const {
        Matrix result(cols, rows);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.data[j][i] = data[i][j];
            }
        }
        return result;
    }
};

// Демонстрация работы матрицы
void demonstrateMatrix() {
    cout << "\n========== ДЕМОНСТРАЦИЯ ШАБЛОННОГО КЛАССА МАТРИЦА ==========" << endl;
    
    Matrix<int> m1(2, 3);
    Matrix<int> m2(2, 3);
    
    cout << "Матрица 1 (случайные числа от 1 до 10):" << endl;
    m1.fillRandom(1, 10);
    m1.display();
    
    cout << "\nМатрица 2 (случайные числа от 1 до 10):" << endl;
    m2.fillRandom(1, 10);
    m2.display();
    
    cout << "\nСумма матриц:" << endl;
    Matrix<int> sum = m1 + m2;
    sum.display();
    
    cout << "\nРазность матриц:" << endl;
    Matrix<int> diff = m1 - m2;
    diff.display();
    
    Matrix<int> m3(3, 2);
    m3.fillRandom(1, 5);
    cout << "\nМатрица 3 (3x2):" << endl;
    m3.display();
    
    cout << "\nПроизведение m1(2x3) * m3(3x2):" << endl;
    Matrix<int> product = m1 * m3;
    product.display();
    
    cout << "\nТранспонированная матрица m1:" << endl;
    Matrix<int> trans = m1.transpose();
    trans.display();
}

#include <stack>

class Stack {
private:
    struct Node {
        char data;
        Node* next;
        Node(char val) : data(val), next(nullptr) {}
    };
    Node* top;
    
public:
    Stack() : top(nullptr) {}
    
    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }
    
    void push(char value) {
        Node* newNode = new Node(value);
        newNode->next = top;
        top = newNode;
    }
    
    void pop() {
        if (!isEmpty()) {
            Node* temp = top;
            top = top->next;
            delete temp;
        }
    }
    
    char peek() const {
        if (!isEmpty()) {
            return top->data;
        }
        return '\0';
    }
    
    bool isEmpty() const {
        return top == nullptr;
    }
};

class BracketChecker {
private:
    string checkBrackets(const string& str) {
        Stack stack;
        
        for (size_t i = 0; i < str.length(); i++) {
            char ch = str[i];
            
            // Если открывающая скобка - добавляем в стек
            if (ch == '(' || ch == '[' || ch == '{') {
                stack.push(ch);
            }
            // Если закрывающая скобка - проверяем
            else if (ch == ')' || ch == ']' || ch == '}') {
                if (stack.isEmpty()) {
                    return "Ошибка: закрывающая скобка без соответствующей открывающей на позиции " + to_string(i);
                }
                
                char openBracket = stack.peek();
                bool isMatch = false;
                
                if ((openBracket == '(' && ch == ')') ||
                    (openBracket == '[' && ch == ']') ||
                    (openBracket == '{' && ch == '}')) {
                    isMatch = true;
                }
                
                if (!isMatch) {
                    return "Ошибка: несоответствие типов скобок на позиции " + to_string(i);
                }
                
                stack.pop();
            }
        }
        
        if (!stack.isEmpty()) {
            return "Ошибка: остались незакрытые скобки. Открывающая скобка '" + 
                   string(1, stack.peek()) + "' не имеет пары.";
        }
        
        return "Строка корректна";
    }
    
public:
    void processString(const string& str) {
        cout << "Проверяемая строка: " << str << endl;
        string result = checkBrackets(str);
        cout << "Результат: " << result << endl;
        
        if (result != "Строка корректна") {
            cout << "Строка до места ошибки: " << result.substr(0, result.find("Ошибка")) << endl;
        }
    }
};

void demonstrateBracketChecking() {
    cout << "\n========== ПРОВЕРКА СКОБОК ==========" << endl;
    
    BracketChecker checker;
    
    string correctStr = "({x-y-z}*[x+2y]-(z+4x))";
    cout << "\nПравильная строка:" << endl;
    checker.processString(correctStr);
    
    string incorrectStr = "([x-y-z}*[x+2y)-{z+4x)]";
    cout << "\nНеправильная строка:" << endl;
    checker.processString(incorrectStr);
    
    string missingBracket = "({x+y}*[z-w]";
    cout << "\nСтрока с незакрытой скобкой:" << endl;
    checker.processString(missingBracket);
    
    string wrongOrder = "([)]";
    cout << "\nСтрока с неправильным порядком:" << endl;
    checker.processString(wrongOrder);
}

#include <queue>
#include <vector>
#include <map>
#include <ctime>

// Задание 4.1: Остановка маршрутных такси
class BusStopSimulation {
private:
    struct Passenger {
        double arrivalTime;
        double waitTime;
        Passenger(double t) : arrivalTime(t), waitTime(0) {}
    };
    
    struct Minibus {
        int freeSeats;
        double arrivalTime;
        Minibus(double t, int seats) : arrivalTime(t), freeSeats(seats) {}
    };
    
    double avgPassengerInterval;  // среднее время между появлениями пассажиров
    double avgMinibusInterval;    // среднее время между появлениями маршруток
    bool isTerminal;              // тип остановки (конечная или нет)
    int maxAllowedPeople;         // максимально допустимое количество людей на остановке
    
public:
    BusStopSimulation(double passInterval, double busInterval, bool terminal, int maxPeople)
        : avgPassengerInterval(passInterval), avgMinibusInterval(busInterval),
          isTerminal(terminal), maxAllowedPeople(maxPeople) {}
    
    void run(double simulationTime) {
        vector<Passenger> passengers;
        vector<Minibus> minibuses;
        
        random_device rd;
        mt19937 gen(rd());
        exponential_distribution<> passDist(1.0 / avgPassengerInterval);
        exponential_distribution<> busDist(1.0 / avgMinibusInterval);
        uniform_int_distribution<> seatsDist(5, 15); // от 5 до 15 свободных мест
        
        double currentTime = 0;
        double nextPassenger = passDist(gen);
        double nextMinibus = busDist(gen);
        
        cout << "\nЗапуск симуляции остановки маршрутных такси..." << endl;
        cout << "Тип остановки: " << (isTerminal ? "Конечная" : "Промежуточная") << endl;
        cout << "Максимально допустимое количество людей: " << maxAllowedPeople << endl;
        
        while (currentTime < simulationTime) {
            if (nextPassenger < nextMinibus) {
                // Прибытие пассажира
                currentTime = nextPassenger;
                passengers.push_back(Passenger(currentTime));
                nextPassenger += passDist(gen);
                
                if (passengers.size() > maxAllowedPeople) {
                    cout << "Предупреждение на " << currentTime << " мин: на остановке "
                         << passengers.size() << " человек (превышение допустимого)!" << endl;
                }
            } else {
                // Прибытие маршрутки
                currentTime = nextMinibus;
                int freeSeats = seatsDist(gen);
                minibuses.push_back(Minibus(currentTime, freeSeats));
                
                // Посадка пассажиров
                int boarded = min(freeSeats, (int)passengers.size());
                for (int i = 0; i < boarded; i++) {
                    passengers[i].waitTime = currentTime - passengers[i].arrivalTime;
                }
                passengers.erase(passengers.begin(), passengers.begin() + boarded);
                
                nextMinibus += busDist(gen);
            }
        }
        
        // Статистика
        double totalWaitTime = 0;
        for (const auto& p : passengers) {
            totalWaitTime += p.waitTime;
        }
        double avgWaitTime = passengers.empty() ? 0 : totalWaitTime / passengers.size();
        
        cout << "\n=== РЕЗУЛЬТАТЫ СИМУЛЯЦИИ ===" << endl;
        cout << "Всего обслужено пассажиров: " << passengers.size() << endl;
        cout << "Среднее время ожидания: " << avgWaitTime << " мин" << endl;
        cout << "Количество прибывших маршруток: " << minibuses.size() << endl;
        cout << "Средний интервал между маршрутками: " << avgMinibusInterval << " мин" << endl;
    }
};

// Задание 4.2: Очередь печати принтера
class PrintQueue {
private:
    struct PrintJob {
        string userName;
        int priority;      // 1 - наивысший, 5 - наинизший
        time_t requestTime;
        time_t completionTime;
        
        PrintJob(const string& name, int prio) 
            : userName(name), priority(prio) {
            requestTime = time(nullptr);
            completionTime = 0;
        }
        
        bool operator<(const PrintJob& other) const {
            return priority > other.priority; // Для приоритетной очереди (чем меньше число, тем выше приоритет)
        }
    };
    
    struct CompletedJob {
        string userName;
        time_t completionTime;
        
        CompletedJob(const string& name, time_t time) 
            : userName(name), completionTime(time) {}
    };
    
    priority_queue<PrintJob> queue;      // Очередь печати
    queue<CompletedJob> statistics;       // Очередь статистики
    
public:
    void addJob(const string& userName, int priority) {
        if (priority < 1) priority = 1;
        if (priority > 5) priority = 5;
        
        PrintJob job(userName, priority);
        queue.push(job);
        
        cout << "Добавлена задача печати для " << userName 
             << " (приоритет: " << priority << ")" << endl;
    }
    
    void processNextJob() {
        if (queue.empty()) {
            cout << "Нет задач в очереди печати" << endl;
            return;
        }
        
        PrintJob job = queue.top();
        queue.pop();
        
        job.completionTime = time(nullptr);
        statistics.push(CompletedJob(job.userName, job.completionTime));
        
        cout << "Печать завершена для " << job.userName 
             << " (приоритет: " << job.priority 
             << ", время ожидания: " << (job.completionTime - job.requestTime) << " сек)" << endl;
    }
    
    void showStatistics() {
        cout << "\n=== СТАТИСТИКА ПЕЧАТИ ===" << endl;
        queue<CompletedJob> temp = statistics;
        
        if (temp.empty()) {
            cout << "Нет завершенных задач" << endl;
            return;
        }
        
        int jobNumber = 1;
        while (!temp.empty()) {
            CompletedJob job = temp.front();
            temp.pop();
            
            char* timeStr = ctime(&job.completionTime);
            timeStr[strlen(timeStr) - 1] = '\0'; // Удаляем символ новой строки
            
            cout << jobNumber++ << ". Пользователь: " << job.userName 
                 << ", время завершения: " << timeStr << endl;
        }
    }
    
    void showQueue() {
        if (queue.empty()) {
            cout << "Очередь печати пуста" << endl;
            return;
        }
        
        cout << "\n=== ТЕКУЩАЯ ОЧЕРЕДЬ ПЕЧАТИ ===" << endl;
        priority_queue<PrintJob> temp = queue;
        
        while (!temp.empty()) {
            PrintJob job = temp.top();
            temp.pop();
            cout << "Пользователь: " << job.userName 
                 << ", приоритет: " << job.priority 
                 << ", время запроса: " << ctime(&job.requestTime);
        }
    }
    
    bool isEmpty() const {
        return queue.empty();
    }
};

void demonstratePrintQueue() {
    cout << "\n========== ИМИТАЦИЯ ОЧЕРЕДИ ПЕЧАТИ ПРИНТЕРА ==========" << endl;
    
    PrintQueue printer;
    
    // Добавление задач с разными приоритетами
    printer.addJob("Иван", 3);
    printer.addJob("Мария", 1);  // Высокий приоритет
    printer.addJob("Петр", 5);
    printer.addJob("Анна", 2);
    
    printer.showQueue();
    
    // Обработка задач
    cout << "\n--- Обработка задач ---" << endl;
    while (!printer.isEmpty()) {
        printer.processNextJob();
        // Небольшая задержка для имитации
        this_thread::sleep_for(chrono::seconds(1));
    }
    
    printer.showStatistics();
}

void demonstrateBusStop() {
    cout << "\n========== ИМИТАЦИЯ ОСТАНОВКИ МАРШРУТНЫХ ТАКСИ ==========" << endl;
    
    // Параметры: средний интервал пассажиров, средний интервал маршруток,
    // тип остановки, максимальное количество людей
    BusStopSimulation stop(2.0, 5.0, false, 20);
    stop.run(60); // Симуляция на 60 минут
}

int main() {
    // Задание 1: Шаблонные функции
    demonstrateTemplateFunctions();
    
    // Задание 2: Шаблонный класс Матрица
    demonstrateMatrix();
    
    // Задание 3: Проверка скобок
    demonstrateBracketChecking();
    
    // Задание 4.1: Остановка маршрутных такси
    demonstrateBusStop();
    
    // Задание 4.2: Очередь печати
    demonstratePrintQueue();
    
    return 0;
}
