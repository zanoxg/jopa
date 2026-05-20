#include <iostream>
#include <string>
#include <exception>
#include <stdexcept>
#include <memory>

using namespace std;

// Пользовательские исключения для списка
class ListException : public exception {
protected:
    string message;
public:
    ListException(const string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

class ListEmptyException : public ListException {
public:
    ListEmptyException() : ListException("Ошибка: попытка操作ции с пустым списком!") {}
};

class ListIndexOutOfRangeException : public ListException {
public:
    ListIndexOutOfRangeException(int index, int size) 
        : ListException("Ошибка: индекс " + to_string(index) + " вне диапазона [0, " + to_string(size - 1) + "]") {}
};

class ListMemoryAllocationException : public ListException {
public:
    ListMemoryAllocationException() 
        : ListException("Ошибка: не удалось выделить память для нового узла списка!") {}
};

class ListInvalidOperationException : public ListException {
public:
    ListInvalidOperationException(const string& op) 
        : ListException("Ошибка: недопустимая операция - " + op) {}
};

// Шаблонный класс для узла двусвязного списка
template<typename T>
class DoubleListNode {
public:
    T data;
    DoubleListNode* prev;
    DoubleListNode* next;
    
    DoubleListNode(const T& value) : data(value), prev(nullptr), next(nullptr) {
        if (this == nullptr) {
            throw ListMemoryAllocationException();
        }
    }
};

// Шаблонный класс Двусвязный список с обработкой исключений
template<typename T>
class DoubleLinkedList {
private:
    DoubleListNode<T>* head;
    DoubleListNode<T>* tail;
    int listSize;
    
    void checkEmpty() const {
        if (isEmpty()) {
            throw ListEmptyException();
        }
    }
    
    void checkIndex(int index) const {
        if (index < 0 || index >= listSize) {
            throw ListIndexOutOfRangeException(index, listSize);
        }
    }
    
public:
    // Конструктор
    DoubleLinkedList() : head(nullptr), tail(nullptr), listSize(0) {}
    
    // Конструктор копирования
    DoubleLinkedList(const DoubleLinkedList& other) : head(nullptr), tail(nullptr), listSize(0) {
        try {
            DoubleListNode<T>* current = other.head;
            while (current) {
                pushBack(current->data);
                current = current->next;
            }
        } catch (const exception& e) {
            clear();
            throw;
        }
    }
    
    // Деструктор
    ~DoubleLinkedList() {
        clear();
    }
    
    // Оператор присваивания
    DoubleLinkedList& operator=(const DoubleLinkedList& other) {
        if (this != &other) {
            clear();
            try {
                DoubleListNode<T>* current = other.head;
                while (current) {
                    pushBack(current->data);
                    current = current->next;
                }
            } catch (const exception& e) {
                clear();
                throw;
            }
        }
        return *this;
    }
    
    // Добавление в начало
    void pushFront(const T& value) {
        try {
            DoubleListNode<T>* newNode = new DoubleListNode<T>(value);
            if (!newNode) {
                throw ListMemoryAllocationException();
            }
            
            if (!head) {
                head = tail = newNode;
            } else {
                newNode->next = head;
                head->prev = newNode;
                head = newNode;
            }
            listSize++;
        } catch (const bad_alloc& e) {
            throw ListMemoryAllocationException();
        }
    }
    
    // Добавление в конец
    void pushBack(const T& value) {
        try {
            DoubleListNode<T>* newNode = new DoubleListNode<T>(value);
            if (!newNode) {
                throw ListMemoryAllocationException();
            }
            
            if (!head) {
                head = tail = newNode;
            } else {
                newNode->prev = tail;
                tail->next = newNode;
                tail = newNode;
            }
            listSize++;
        } catch (const bad_alloc& e) {
            throw ListMemoryAllocationException();
        }
    }
    
    // Удаление из начала
    T popFront() {
        checkEmpty();
        
        DoubleListNode<T>* temp = head;
        T value = temp->data;
        
        if (head == tail) {
            head = tail = nullptr;
        } else {
            head = head->next;
            head->prev = nullptr;
        }
        
        delete temp;
        listSize--;
        return value;
    }
    
    // Удаление из конца
    T popBack() {
        checkEmpty();
        
        DoubleListNode<T>* temp = tail;
        T value = temp->data;
        
        if (head == tail) {
            head = tail = nullptr;
        } else {
            tail = tail->prev;
            tail->next = nullptr;
        }
        
        delete temp;
        listSize--;
        return value;
    }
    
    // Получение элемента по индексу
    T getAt(int index) const {
        checkIndex(index);
        
        DoubleListNode<T>* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->data;
    }
    
    // Вставка по индексу
    void insertAt(int index, const T& value) {
        if (index < 0 || index > listSize) {
            throw ListIndexOutOfRangeException(index, listSize);
        }
        
        if (index == 0) {
            pushFront(value);
        } else if (index == listSize) {
            pushBack(value);
        } else {
            try {
                DoubleListNode<T>* newNode = new DoubleListNode<T>(value);
                if (!newNode) {
                    throw ListMemoryAllocationException();
                }
                
                DoubleListNode<T>* current = head;
                for (int i = 0; i < index; i++) {
                    current = current->next;
                }
                
                newNode->prev = current->prev;
                newNode->next = current;
                current->prev->next = newNode;
                current->prev = newNode;
                listSize++;
            } catch (const bad_alloc& e) {
                throw ListMemoryAllocationException();
            }
        }
    }
    
    // Удаление по индексу
    T removeAt(int index) {
        checkIndex(index);
        
        if (index == 0) {
            return popFront();
        } else if (index == listSize - 1) {
            return popBack();
        } else {
            DoubleListNode<T>* current = head;
            for (int i = 0; i < index; i++) {
                current = current->next;
            }
            
            T value = current->data;
            current->prev->next = current->next;
            current->next->prev = current->prev;
            delete current;
            listSize--;
            return value;
        }
    }
    
    // Поиск элемента
    int find(const T& value) const {
        DoubleListNode<T>* current = head;
        int index = 0;
        while (current) {
            if (current->data == value) {
                return index;
            }
            current = current->next;
            index++;
        }
        return -1;
    }
    
    // Просмотр первого элемента
    T front() const {
        checkEmpty();
        return head->data;
    }
    
    // Просмотр последнего элемента
    T back() const {
        checkEmpty();
        return tail->data;
    }
    
    // Отображение списка
    void displayForward() const {
        if (isEmpty()) {
            cout << "Список пуст." << endl;
            return;
        }
        
        DoubleListNode<T>* current = head;
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << "(размер: " << listSize << ")" << endl;
    }
    
    // Очистка списка
    void clear() {
        while (head) {
            DoubleListNode<T>* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
        listSize = 0;
    }
    
    // Получение размера
    int size() const {
        return listSize;
    }
    
    // Проверка на пустоту
    bool isEmpty() const {
        return head == nullptr;
    }
    
    // Клонирование списка
    DoubleLinkedList<T> clone() const {
        DoubleLinkedList<T> newList;
        DoubleListNode<T>* current = head;
        while (current) {
            newList.pushBack(current->data);
            current = current->next;
        }
        return newList;
    }
    
    // Оператор + (объединение)
    DoubleLinkedList<T> operator+(const DoubleLinkedList<T>& other) const {
        DoubleLinkedList<T> result = this->clone();
        DoubleListNode<T>* current = other.head;
        while (current) {
            result.pushBack(current->data);
            current = current->next;
        }
        return result;
    }
    
    // Оператор * (пересечение)
    DoubleLinkedList<T> operator*(const DoubleLinkedList<T>& other) const {
        DoubleLinkedList<T> result;
        
        DoubleListNode<T>* current = head;
        while (current) {
            if (other.find(current->data) != -1 && result.find(current->data) == -1) {
                result.pushBack(current->data);
            }
            current = current->next;
        }
        return result;
    }
};

// Демонстрация работы списка с исключениями
void demonstrateDoubleLinkedListWithExceptions() {
    cout << "\n========== ДВУСВЯЗНЫЙ СПИСОК С ОБРАБОТКОЙ ИСКЛЮЧЕНИЙ ==========" << endl;
    
    DoubleLinkedList<int> list;
    
    // Тест 1: Добавление элементов
    cout << "\n--- Добавление элементов ---" << endl;
    try {
        list.pushBack(10);
        list.pushBack(20);
        list.pushBack(30);
        list.pushFront(5);
        list.displayForward();
    } catch (const exception& e) {
        cerr << "Исключение: " << e.what() << endl;
    }
    
    // Тест 2: Попытка удаления из пустого списка
    cout << "\n--- Тест удаления из пустого списка ---" << endl;
    try {
        DoubleLinkedList<int> emptyList;
        emptyList.popFront(); // Должно выбросить исключение
    } catch (const ListEmptyException& e) {
        cerr << "Поймано исключение: " << e.what() << endl;
    }
    
    // Тест 3: Попытка доступа по неверному индексу
    cout << "\n--- Тест доступа по неверному индексу ---" << endl;
    try {
        list.getAt(10); // Должно выбросить исключение
    } catch (const ListIndexOutOfRangeException& e) {
        cerr << "Поймано исключение: " << e.what() << endl;
    }
    
    // Тест 4: Вставка по неверному индексу
    cout << "\n--- Тест вставки по неверному индексу ---" << endl;
    try {
        list.insertAt(100, 999);
    } catch (const ListIndexOutOfRangeException& e) {
        cerr << "Поймано исключение: " << e.what() << endl;
    }
    
    // Тест 5: Нормальная работа
    cout << "\n--- Нормальная работа списка ---" << endl;
    try {
        cout << "Первый элемент: " << list.front() << endl;
        cout << "Последний элемент: " << list.back() << endl;
        cout << "Элемент по индексу 2: " << list.getAt(2) << endl;
        
        list.insertAt(2, 99);
        cout << "После вставки 99 на позицию 2: ";
        list.displayForward();
        
        int removed = list.removeAt(2);
        cout << "Удален элемент: " << removed << endl;
        list.displayForward();
    } catch (const exception& e) {
        cerr << "Исключение: " << e.what() << endl;
    }
}

// Базовый класс для всех исключений приложения
class ApplicationException : public exception {
protected:
    string message;
    string file;
    int line;
    
public:
    ApplicationException(const string& msg, const string& f = "", int l = 0) 
        : message(msg), file(f), line(l) {}
    
    virtual const char* what() const noexcept override {
        static string fullMessage;
        if (!file.empty()) {
            fullMessage = message + " [" + file + ":" + to_string(line) + "]";
        } else {
            fullMessage = message;
        }
        return fullMessage.c_str();
    }
    
    virtual string getDetails() const {
        return message;
    }
};

// 1. Исключения для математических операций
class MathException : public ApplicationException {
public:
    MathException(const string& msg, const string& f = "", int l = 0) 
        : ApplicationException(msg, f, l) {}
};

class DivisionByZeroException : public MathException {
public:
    DivisionByZeroException(const string& f = "", int l = 0) 
        : MathException("Ошибка: деление на ноль!", f, l) {}
};

class FractionInvalidException : public MathException {
public:
    FractionInvalidException(const string& f = "", int l = 0) 
        : MathException("Ошибка: некорректная дробь (знаменатель не может быть нулем)!", f, l) {}
};

class OverflowException : public MathException {
public:
    OverflowException(const string& operation, const string& f = "", int l = 0) 
        : MathException("Ошибка: переполнение при выполнении операции " + operation, f, l) {}
};

// 2. Исключения для работы с памятью
class MemoryException : public ApplicationException {
public:
    MemoryException(const string& msg, const string& f = "", int l = 0) 
        : ApplicationException(msg, f, l) {}
};

class MemoryAllocationException : public MemoryException {
public:
    MemoryAllocationException(const string& f = "", int l = 0) 
        : MemoryException("Ошибка: не удалось выделить память!", f, l) {}
};

class MemoryLeakException : public MemoryException {
public:
    MemoryLeakException(const string& resource, const string& f = "", int l = 0) 
        : MemoryException("Ошибка: утечка памяти при работе с ресурсом: " + resource, f, l) {}
};

class NullPointerException : public MemoryException {
public:
    NullPointerException(const string& ptrName, const string& f = "", int l = 0) 
        : MemoryException("Ошибка: нулевой указатель - " + ptrName, f, l) {}
};

// 3. Исключения для работы с файлами
class FileException : public ApplicationException {
public:
    FileException(const string& msg, const string& f = "", int l = 0) 
        : ApplicationException(msg, f, l) {}
};

class FileNotFoundException : public FileException {
public:
    FileNotFoundException(const string& filename, const string& f = "", int l = 0) 
        : FileException("Ошибка: файл не найден - " + filename, f, l) {}
};

class FileOpenException : public FileException {
public:
    FileOpenException(const string& filename, const string& f = "", int l = 0) 
        : FileException("Ошибка: не удалось открыть файл - " + filename, f, l) {}
};

class FileReadException : public FileException {
public:
    FileReadException(const string& filename, const string& f = "", int l = 0) 
        : FileException("Ошибка: ошибка чтения из файла - " + filename, f, l) {}
};

class FileWriteException : public FileException {
public:
    FileWriteException(const string& filename, const string& f = "", int l = 0) 
        : FileException("Ошибка: ошибка записи в файл - " + filename, f, l) {}
};

// 4. Исключения для работы со строками
class StringException : public ApplicationException {
public:
    StringException(const string& msg, const string& f = "", int l = 0) 
        : ApplicationException(msg, f, l) {}
};

class InvalidStringException : public StringException {
public:
    InvalidStringException(const string& str, const string& f = "", int l = 0) 
        : StringException("Ошибка: некорректная строка - " + str, f, l) {}
};

class StringIndexOutOfRangeException : public StringException {
public:
    StringIndexOutOfRangeException(int index, int length, const string& f = "", int l = 0) 
        : StringException("Ошибка: индекс " + to_string(index) + " вне диапазона [0, " + to_string(length - 1) + "]", f, l) {}
};

// 5. Исключения для работы с контейнерами
class ContainerException : public ApplicationException {
public:
    ContainerException(const string& msg, const string& f = "", int l = 0) 
        : ApplicationException(msg, f, l) {}
};

class ContainerEmptyException : public ContainerException {
public:
    ContainerEmptyException(const string& container, const string& f = "", int l = 0) 
        : ContainerException("Ошибка: контейнер " + container + " пуст!", f, l) {}
};

class ContainerFullException : public ContainerException {
public:
    ContainerFullException(const string& container, const string& f = "", int l = 0) 
        : ContainerException("Ошибка: контейнер " + container + " переполнен!", f, l) {}
};

class ElementNotFoundException : public ContainerException {
public:
    ElementNotFoundException(const string& element, const string& f = "", int l = 0) 
        : ContainerException("Ошибка: элемент " + element + " не найден в контейнере!", f, l) {}
};

// Тестирование иерархии исключений
class Fraction {
private:
    int numerator;
    int denominator;
    
    void validate() const {
        if (denominator == 0) {
            throw FractionInvalidException(__FILE__, __LINE__);
        }
    }
    
public:
    Fraction(int num = 0, int den = 1) : numerator(num), denominator(den) {
        validate();
    }
    
    Fraction operator/(const Fraction& other) const {
        if (other.numerator == 0) {
            throw DivisionByZeroException(__FILE__, __LINE__);
        }
        return Fraction(numerator * other.denominator, denominator * other.numerator);
    }
    
    void display() const {
        cout << numerator << "/" << denominator;
    }
};

void testExceptionHierarchy() {
    cout << "\n========== ТЕСТИРОВАНИЕ ИЕРАРХИИ ИСКЛЮЧЕНИЙ ==========" << endl;
    
    // Тест 1: Математические исключения
    cout << "\n--- Математические исключения ---" << endl;
    try {
        Fraction f1(1, 0); // Должно выбросить исключение
    } catch (const FractionInvalidException& e) {
        cerr << "Поймано FractionInvalidException: " << e.what() << endl;
    }
    
    try {
        Fraction f1(1, 2);
        Fraction f2(0, 1);
        Fraction f3 = f1 / f2; // Деление на ноль
    } catch (const DivisionByZeroException& e) {
        cerr << "Поймано DivisionByZeroException: " << e.what() << endl;
    }
    
    // Тест 2: Файловые исключения
    cout << "\n--- Файловые исключения ---" << endl;
    try {
        throw FileNotFoundException("data.txt", __FILE__, __LINE__);
    } catch (const FileNotFoundException& e) {
        cerr << "Поймано FileNotFoundException: " << e.what() << endl;
    }
    
    // Тест 3: Исключения памяти
    cout << "\n--- Исключения памяти ---" << endl;
    try {
        throw MemoryAllocationException(__FILE__, __LINE__);
    } catch (const MemoryAllocationException& e) {
        cerr << "Поймано MemoryAllocationException: " << e.what() << endl;
    }
    
    // Тест 4: Исключения контейнеров
    cout << "\n--- Исключения контейнеров ---" << endl;
    try {
        throw ContainerEmptyException("Vector", __FILE__, __LINE__);
    } catch (const ContainerEmptyException& e) {
        cerr << "Поймано ContainerEmptyException: " << e.what() << endl;
    }
    
    // Тест 5: Исключения строк
    cout << "\n--- Исключения строк ---" << endl;
    try {
        throw StringIndexOutOfRangeException(10, 5, __FILE__, __LINE__);
    } catch (const StringIndexOutOfRangeException& e) {
        cerr << "Поймано StringIndexOutOfRangeException: " << e.what() << endl;
    }
    
    // Демонстрация полиморфизма исключений
    cout << "\n--- Полиморфизм исключений ---" << endl;
    try {
        throw FileOpenException("config.ini", __FILE__, __LINE__);
    } catch (const FileException& e) {
        cerr << "Поймано как FileException: " << e.what() << endl;
        cout << "Детали: " << e.getDetails() << endl;
    } catch (const ApplicationException& e) {
        cerr << "Поймано как ApplicationException: " << e.what() << endl;
    }
}

// Пространство имен для математических утилит
namespace MathUtils {
    
    // Класс Fraction (Дробь)
    class Fraction {
    private:
        int numerator;
        int denominator;
        
        int gcd(int a, int b) const {
            a = abs(a);
            b = abs(b);
            while (b != 0) {
                int temp = b;
                b = a % b;
                a = temp;
            }
            return a;
        }
        
        void reduce() {
            if (denominator == 0) {
                throw DivisionByZeroException(__FILE__, __LINE__);
            }
            int divisor = gcd(numerator, denominator);
            numerator /= divisor;
            denominator /= divisor;
            if (denominator < 0) {
                numerator = -numerator;
                denominator = -denominator;
            }
        }
        
    public:
        Fraction(int num = 0, int den = 1) : numerator(num), denominator(den) {
            reduce();
        }
        
        Fraction operator+(const Fraction& other) const {
            return Fraction(
                numerator * other.denominator + other.numerator * denominator,
                denominator * other.denominator
            );
        }
        
        Fraction operator-(const Fraction& other) const {
            return Fraction(
                numerator * other.denominator - other.numerator * denominator,
                denominator * other.denominator
            );
        }
        
        Fraction operator*(const Fraction& other) const {
            return Fraction(
                numerator * other.numerator,
                denominator * other.denominator
            );
        }
        
        Fraction operator/(const Fraction& other) const {
            if (other.numerator == 0) {
                throw DivisionByZeroException(__FILE__, __LINE__);
            }
            return Fraction(
                numerator * other.denominator,
                denominator * other.numerator
            );
        }
        
        double toDouble() const {
            return static_cast<double>(numerator) / denominator;
        }
        
        void display() const {
            if (denominator == 1) {
                cout << numerator;
            } else {
                cout << numerator << "/" << denominator;
            }
        }
    };
    
    // Класс Point2D (Точка в двумерном пространстве)
    class Point2D {
    private:
        double x;
        double y;
        
    public:
        Point2D(double xCoord = 0, double yCoord = 0) : x(xCoord), y(yCoord) {}
        
        double getX() const { return x; }
        double getY() const { return y; }
        
        double distanceTo(const Point2D& other) const {
            double dx = x - other.x;
            double dy = y - other.y;
            return sqrt(dx * dx + dy * dy);
        }
        
        Point2D operator+(const Point2D& other) const {
            return Point2D(x + other.x, y + other.y);
        }
        
        Point2D operator-(const Point2D& other) const {
            return Point2D(x - other.x, y - other.y);
        }
        
        void display() const {
            cout << "(" << x << ", " << y << ")";
        }
    };
    
    // Класс Point3D (Точка в трехмерном пространстве)
    class Point3D {
    private:
        double x;
        double y;
        double z;
        
    public:
        Point3D(double xCoord = 0, double yCoord = 0, double zCoord = 0) 
            : x(xCoord), y(yCoord), z(zCoord) {}
        
        double getX() const { return x; }
        double getY() const { return y; }
        double getZ() const { return z; }
        
        double distanceTo(const Point3D& other) const {
            double dx = x - other.x;
            double dy = y - other.y;
            double dz = z - other.z;
            return sqrt(dx * dx + dy * dy + dz * dz);
        }
        
        Point3D operator+(const Point3D& other) const {
            return Point3D(x + other.x, y + other.y, z + other.z);
        }
        
        Point3D operator-(const Point3D& other) const {
            return Point3D(x - other.x, y - other.y, z - other.z);
        }
        
        double dotProduct(const Point3D& other) const {
            return x * other.x + y * other.y + z * other.z;
        }
        
        Point3D crossProduct(const Point3D& other) const {
            return Point3D(
                y * other.z - z * other.y,
                z * other.x - x * other.z,
                x * other.y - y * other.x
            );
        }
        
        void display() const {
            cout << "(" << x << ", " << y << ", " << z << ")";
        }
    };
    
    // Класс Matrix (Матрица)
    template<typename T>
    class Matrix {
    private:
        T** data;
        int rows;
        int cols;
        
    public:
        Matrix(int r, int c) : rows(r), cols(c) {
            data = new T*[rows];
            for (int i = 0; i < rows; i++) {
                data[i] = new T[cols]();
            }
        }
        
        ~Matrix() {
            for (int i = 0; i < rows; i++) {
                delete[] data[i];
            }
            delete[] data;
        }
        
        T& operator()(int i, int j) {
            if (i < 0 || i >= rows || j < 0 || j >= cols) {
                throw out_of_range("Индекс вне границ");
            }
            return data[i][j];
        }
        
        void display() const {
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    cout << data[i][j] << "\t";
                }
                cout << endl;
            }
        }
    };
}

// Пространство имен для утилит работы с контейнерами
namespace ContainerUtils {
    
    template<typename T>
    class Stack {
    private:
        struct Node {
            T data;
            Node* next;
            Node(const T& value) : data(value), next(nullptr) {}
        };
        Node* top;
        int size;
        
    public:
        Stack() : top(nullptr), size(0) {}
        
        ~Stack() {
            while (!isEmpty()) {
                pop();
            }
        }
        
        void push(const T& value) {
            Node* newNode = new Node(value);
            newNode->next = top;
            top = newNode;
            size++;
        }
        
        T pop() {
            if (isEmpty()) {
                throw ContainerEmptyException("Stack", __FILE__, __LINE__);
            }
            Node* temp = top;
            T value = temp->data;
            top = top->next;
            delete temp;
            size--;
            return value;
        }
        
        T peek() const {
            if (isEmpty()) {
                throw ContainerEmptyException("Stack", __FILE__, __LINE__);
            }
            return top->data;
        }
        
        bool isEmpty() const {
            return top == nullptr;
        }
        
        int getSize() const {
            return size;
        }
    };
    
    template<typename T>
    class Queue {
    private:
        struct Node {
            T data;
            Node* next;
            Node(const T& value) : data(value), next(nullptr) {}
        };
        Node* front;
        Node* rear;
        int size;
        
    public:
        Queue() : front(nullptr), rear(nullptr), size(0) {}
        
        ~Queue() {
            while (!isEmpty()) {
                dequeue();
            }
        }
        
        void enqueue(const T& value) {
            Node* newNode = new Node(value);
            if (isEmpty()) {
                front = rear = newNode;
            } else {
                rear->next = newNode;
                rear = newNode;
            }
            size++;
        }
        
        T dequeue() {
            if (isEmpty()) {
                throw ContainerEmptyException("Queue", __FILE__, __LINE__);
            }
            Node* temp = front;
            T value = temp->data;
            front = front->next;
            if (!front) {
                rear = nullptr;
            }
            delete temp;
            size--;
            return value;
        }
        
        bool isEmpty() const {
            return front == nullptr;
        }
        
        int getSize() const {
            return size;
        }
    };
}

// Тестирование пространств имен
void testNamespaces() {
    cout << "\n========== ТЕСТИРОВАНИЕ ПРОСТРАНСТВ ИМЕН ==========" << endl;
    
    // Тестирование MathUtils::Fraction
    cout << "\n--- MathUtils::Fraction ---" << endl;
    try {
        MathUtils::Fraction f1(1, 2);
        MathUtils::Fraction f2(1, 3);
        MathUtils::Fraction f3 = f1 + f2;
        MathUtils::Fraction f4 = f1 * f2;
        MathUtils::Fraction f5 = f1 / f2;
        
        cout << "f1 = "; f1.display(); cout << endl;
        cout << "f2 = "; f2.display(); cout << endl;
        cout << "f1 + f2 = "; f3.display(); cout << endl;
        cout << "f1 * f2 = "; f4.display(); cout << endl;
        cout << "f1 / f2 = "; f5.display(); cout << endl;
        cout << "f1 as double = " << f1.toDouble() << endl;
    } catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
    }
    
    // Тестирование MathUtils::Point2D
    cout << "\n--- MathUtils::Point2D ---" << endl;
    MathUtils::Point2D p1(0, 0);
    MathUtils::Point2D p2(3, 4);
    cout << "Точка p1: "; p1.display(); cout << endl;
    cout << "Точка p2: "; p2.display(); cout << endl;
    cout << "Расстояние между точками: " << p1.distanceTo(p2) << endl;
    
    // Тестирование MathUtils::Point3D
    cout << "\n--- MathUtils::Point3D ---" << endl;
    MathUtils::Point3D p3d1(1, 0, 0);
    MathUtils::Point3D p3d2(0, 1, 0);
    cout << "Точка A: "; p3d1.display(); cout << endl;
    cout << "Точка B: "; p3d2.display(); cout << endl;
    cout << "Скалярное произведение: " << p3d1.dotProduct(p3d2) << endl;
    
    MathUtils::Point3D cross = p3d1.crossProduct(p3d2);
    cout << "Векторное произведение: "; cross.display(); cout << endl;
    
    // Тестирование ContainerUtils::Stack
    cout << "\n--- ContainerUtils::Stack ---" << endl;
    ContainerUtils::Stack<int> stack;
    stack.push(10);
    stack.push(20);
    stack.push(30);
    cout << "Верхний элемент стека: " << stack.peek() << endl;
    cout << "Размер стека: " << stack.getSize() << endl;
    
    while (!stack.isEmpty()) {
        cout << "Извлечено: " << stack.pop() << endl;
    }
    
    // Тестирование ContainerUtils::Queue
    cout << "\n--- ContainerUtils::Queue ---" << endl;
    ContainerUtils::Queue<string> queue;
    queue.enqueue("Первый");
    queue.enqueue("Второй");
    queue.enqueue("Третий");
    
    while (!queue.isEmpty()) {
        cout << "Извлечено: " << queue.dequeue() << endl;
    }
    
    // Демонстрация обработки исключений в контейнерах
    cout << "\n--- Обработка исключений в контейнерах ---" << endl;
    try {
        ContainerUtils::Stack<double> emptyStack;
        emptyStack.pop(); // Должно выбросить исключение
    } catch (const ContainerEmptyException& e) {
        cerr << "Поймано исключение: " << e.what() << endl;
    }
}

int main() {
    // Задание 1: Двусвязный список с исключениями
    demonstrateDoubleLinkedListWithExceptions();
    
    // Задание 2: Иерархия классов-исключений
    testExceptionHierarchy();
    
    // Задание 3: Пространства имен
    testNamespaces();
    
    return 0;
}
