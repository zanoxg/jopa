#include <iostream>
#include <stdexcept>

using namespace std;

// Шаблонный класс для узла стека
template<typename T>
class StackNode {
public:
    T data;
    StackNode* next;
    
    StackNode(const T& value) : data(value), next(nullptr) {}
};

// Шаблонный класс Стек
template<typename T>
class Stack {
private:
    StackNode<T>* top;      // Вершина стека
    int currentSize;        // Текущий размер
    int capacity;           // Вместимость
    
    void resize() {
        capacity = capacity * 2;
        cout << "Стек переполнен! Увеличение размера до " << capacity << endl;
    }
    
public:
    // Конструктор
    Stack(int initialCapacity = 10) : top(nullptr), currentSize(0), capacity(initialCapacity) {}
    
    // Конструктор копирования
    Stack(const Stack& other) : top(nullptr), currentSize(0), capacity(other.capacity) {
        Stack<T> temp;
        StackNode<T>* current = other.top;
        
        // Копируем элементы во временный стек (чтобы сохранить порядок)
        while (current) {
            temp.push(current->data);
            current = current->next;
        }
        
        // Перекладываем обратно
        while (!temp.isEmpty()) {
            push(temp.pop());
        }
    }
    
    // Деструктор
    ~Stack() {
        clear();
    }
    
    // Оператор присваивания
    Stack& operator=(const Stack& other) {
        if (this != &other) {
            clear();
            capacity = other.capacity;
            
            Stack<T> temp;
            StackNode<T>* current = other.top;
            while (current) {
                temp.push(current->data);
                current = current->next;
            }
            
            while (!temp.isEmpty()) {
                push(temp.pop());
            }
        }
        return *this;
    }
    
    // Добавление элемента в стек
    void push(const T& value) {
        if (currentSize >= capacity) {
            resize();
        }
        
        StackNode<T>* newNode = new StackNode<T>(value);
        newNode->next = top;
        top = newNode;
        currentSize++;
        
        cout << "Добавлен элемент: " << value << " (размер: " << currentSize << "/" << capacity << ")" << endl;
    }
    
    // Удаление элемента из стека
    T pop() {
        if (isEmpty()) {
            throw runtime_error("Стек пуст! Невозможно выполнить pop.");
        }
        
        StackNode<T>* temp = top;
        T value = temp->data;
        top = top->next;
        delete temp;
        currentSize--;
        
        cout << "Удален элемент: " << value << " (размер: " << currentSize << "/" << capacity << ")" << endl;
        return value;
    }
    
    // Просмотр верхнего элемента
    T peek() const {
        if (isEmpty()) {
            throw runtime_error("Стек пуст! Нет элементов для просмотра.");
        }
        return top->data;
    }
    
    // Проверка на пустоту
    bool isEmpty() const {
        return top == nullptr;
    }
    
    // Получение текущего размера
    int size() const {
        return currentSize;
    }
    
    // Получение вместимости
    int getCapacity() const {
        return capacity;
    }
    
    // Очистка стека
    void clear() {
        while (!isEmpty()) {
            pop();
        }
    }
    
    // Отображение всех элементов
    void display() const {
        if (isEmpty()) {
            cout << "Стек пуст." << endl;
            return;
        }
        
        cout << "Содержимое стека (сверху вниз): ";
        StackNode<T>* current = top;
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
    
    // Получение головы списка (для доступа к узлам)
    StackNode<T>* getTop() const {
        return top;
    }
};

// Демонстрация работы стека
void demonstrateStack() {
    cout << "\n========== ДЕМОНСТРАЦИЯ РАБОТЫ СТЕКА ==========" << endl;
    
    Stack<int> stack(3); // Создаем стек с начальной вместимостью 3
    
    cout << "\n--- Добавление элементов ---" << endl;
    stack.push(10);
    stack.push(20);
    stack.push(30);
    stack.display();
    
    cout << "\n--- Добавление элемента при переполнении ---" << endl;
    stack.push(40); // Должен увеличить размер
    
    cout << "\n--- Просмотр верхнего элемента ---" << endl;
    cout << "Верхний элемент: " << stack.peek() << endl;
    
    cout << "\n--- Удаление элементов ---" << endl;
    while (!stack.isEmpty()) {
        stack.pop();
    }
    
    cout << "\n--- Проверка на пустоту ---" << endl;
    cout << "Стек пуст? " << (stack.isEmpty() ? "Да" : "Нет") << endl;
}

// Шаблонный класс узла списка
template<typename T>
class ListNode {
public:
    T data;
    ListNode* next;
    
    ListNode(const T& value) : data(value), next(nullptr) {}
};

// Шаблонный класс Односвязный список
template<typename T>
class LinkedList {
protected:
    ListNode<T>* head;
    int listSize;
    
public:
    // Конструктор
    LinkedList() : head(nullptr), listSize(0) {}
    
    // Конструктор копирования
    LinkedList(const LinkedList& other) : head(nullptr), listSize(0) {
        ListNode<T>* current = other.head;
        while (current) {
            pushBack(current->data);
            current = current->next;
        }
    }
    
    // Деструктор
    virtual ~LinkedList() {
        clear();
    }
    
    // Оператор присваивания
    LinkedList& operator=(const LinkedList& other) {
        if (this != &other) {
            clear();
            ListNode<T>* current = other.head;
            while (current) {
                pushBack(current->data);
                current = current->next;
            }
        }
        return *this;
    }
    
    // Добавление в начало
    void pushFront(const T& value) {
        ListNode<T>* newNode = new ListNode<T>(value);
        newNode->next = head;
        head = newNode;
        listSize++;
    }
    
    // Добавление в конец
    void pushBack(const T& value) {
        ListNode<T>* newNode = new ListNode<T>(value);
        
        if (!head) {
            head = newNode;
        } else {
            ListNode<T>* current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = newNode;
        }
        listSize++;
    }
    
    // Удаление из начала
    T popFront() {
        if (!head) {
            throw runtime_error("Список пуст!");
        }
        
        ListNode<T>* temp = head;
        T value = temp->data;
        head = head->next;
        delete temp;
        listSize--;
        return value;
    }
    
    // Отображение списка
    void display() const {
        if (!head) {
            cout << "Список пуст." << endl;
            return;
        }
        
        ListNode<T>* current = head;
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << "(размер: " << listSize << ")" << endl;
    }
    
    // Очистка списка
    void clear() {
        while (head) {
            ListNode<T>* temp = head;
            head = head->next;
            delete temp;
        }
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
    
    // 1. Операция клонирования списка (возвращает адрес головы клонированного списка)
    ListNode<T>* clone() const {
        if (!head) return nullptr;
        
        ListNode<T>* newHead = nullptr;
        ListNode<T>* newTail = nullptr;
        ListNode<T>* current = head;
        
        while (current) {
            ListNode<T>* newNode = new ListNode<T>(current->data);
            if (!newHead) {
                newHead = newNode;
                newTail = newNode;
            } else {
                newTail->next = newNode;
                newTail = newNode;
            }
            current = current->next;
        }
        
        return newHead;
    }
    
    // 2. Перегрузка оператора + (объединение списков)
    LinkedList<T> operator+(const LinkedList<T>& other) const {
        LinkedList<T> result;
        
        // Добавляем элементы первого списка
        ListNode<T>* current = head;
        while (current) {
            result.pushBack(current->data);
            current = current->next;
        }
        
        // Добавляем элементы второго списка
        current = other.head;
        while (current) {
            result.pushBack(current->data);
            current = current->next;
        }
        
        return result;
    }
    
    // 3. Перегрузка оператора * (пересечение списков - общие элементы)
    LinkedList<T> operator*(const LinkedList<T>& other) const {
        LinkedList<T> result;
        
        ListNode<T>* current = head;
        while (current) {
            // Проверяем, есть ли текущий элемент во втором списке
            ListNode<T>* search = other.head;
            while (search) {
                if (search->data == current->data) {
                    // Проверяем, не добавлен ли уже этот элемент в результат
                    bool alreadyExists = false;
                    ListNode<T>* resultCurrent = result.head;
                    while (resultCurrent) {
                        if (resultCurrent->data == current->data) {
                            alreadyExists = true;
                            break;
                        }
                        resultCurrent = resultCurrent->next;
                    }
                    
                    if (!alreadyExists) {
                        result.pushBack(current->data);
                    }
                    break;
                }
                search = search->next;
            }
            current = current->next;
        }
        
        return result;
    }
    
    // Получение головы списка
    ListNode<T>* getHead() const {
        return head;
    }
    
    // Поиск элемента
    bool find(const T& value) const {
        ListNode<T>* current = head;
        while (current) {
            if (current->data == value) {
                return true;
            }
            current = current->next;
        }
        return false;
    }
};

// Демонстрация работы односвязного списка с дополнительными операциями
void demonstrateLinkedList() {
    cout << "\n========== ДЕМОНСТРАЦИЯ ОДНОСВЯЗНОГО СПИСКА ==========" << endl;
    
    LinkedList<int> list1;
    LinkedList<int> list2;
    
    // Заполняем первый список
    cout << "\nПервый список: ";
    list1.pushBack(1);
    list1.pushBack(2);
    list1.pushBack(3);
    list1.pushBack(4);
    list1.pushBack(5);
    list1.display();
    
    // Заполняем второй список
    cout << "Второй список: ";
    list2.pushBack(4);
    list2.pushBack(5);
    list2.pushBack(6);
    list2.pushBack(7);
    list2.pushBack(8);
    list2.display();
    
    // Тестируем клонирование
    cout << "\n--- Клонирование первого списка ---" << endl;
    ListNode<int>* clonedHead = list1.clone();
    LinkedList<int> clonedList;
    ListNode<int>* current = clonedHead;
    while (current) {
        clonedList.pushBack(current->data);
        current = current->next;
    }
    cout << "Клонированный список: ";
    clonedList.display();
    
    // Тестируем оператор +
    cout << "\n--- Оператор + (объединение) ---" << endl;
    LinkedList<int> unionList = list1 + list2;
    cout << "Результат объединения: ";
    unionList.display();
    
    // Тестируем оператор *
    cout << "\n--- Оператор * (пересечение) ---" << endl;
    LinkedList<int> intersectList = list1 * list2;
    cout << "Результат пересечения: ";
    intersectList.display();
    
    // Очищаем память клонированного списка
    while (clonedHead) {
        ListNode<int>* temp = clonedHead;
        clonedHead = clonedHead->next;
        delete temp;
    }
}

// Шаблонный класс для узла двусвязного списка
template<typename T>
class DoubleListNode {
public:
    T data;
    DoubleListNode* prev;
    DoubleListNode* next;
    
    DoubleListNode(const T& value) : data(value), prev(nullptr), next(nullptr) {}
};

// Шаблонный класс Двусвязный список
template<typename T>
class DoubleLinkedList {
protected:
    DoubleListNode<T>* head;
    DoubleListNode<T>* tail;
    int listSize;
    
public:
    // Конструктор
    DoubleLinkedList() : head(nullptr), tail(nullptr), listSize(0) {}
    
    // Конструктор копирования
    DoubleLinkedList(const DoubleLinkedList& other) : head(nullptr), tail(nullptr), listSize(0) {
        DoubleListNode<T>* current = other.head;
        while (current) {
            pushBack(current->data);
            current = current->next;
        }
    }
    
    // Деструктор
    virtual ~DoubleLinkedList() {
        clear();
    }
    
    // Оператор присваивания
    DoubleLinkedList& operator=(const DoubleLinkedList& other) {
        if (this != &other) {
            clear();
            DoubleListNode<T>* current = other.head;
            while (current) {
                pushBack(current->data);
                current = current->next;
            }
        }
        return *this;
    }
    
    // Добавление в начало
    void pushFront(const T& value) {
        DoubleListNode<T>* newNode = new DoubleListNode<T>(value);
        
        if (!head) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        listSize++;
    }
    
    // Добавление в конец
    void pushBack(const T& value) {
        DoubleListNode<T>* newNode = new DoubleListNode<T>(value);
        
        if (!head) {
            head = tail = newNode;
        } else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
        listSize++;
    }
    
    // Удаление из начала
    T popFront() {
        if (!head) {
            throw runtime_error("Список пуст!");
        }
        
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
        if (!tail) {
            throw runtime_error("Список пуст!");
        }
        
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
    
    // Просмотр первого элемента
    T front() const {
        if (!head) {
            throw runtime_error("Список пуст!");
        }
        return head->data;
    }
    
    // Просмотр последнего элемента
    T back() const {
        if (!tail) {
            throw runtime_error("Список пуст!");
        }
        return tail->data;
    }
    
    // Отображение списка (с начала)
    void displayForward() const {
        if (!head) {
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
    
    // Отображение списка (с конца)
    void displayBackward() const {
        if (!tail) {
            cout << "Список пуст." << endl;
            return;
        }
        
        DoubleListNode<T>* current = tail;
        while (current) {
            cout << current->data << " ";
            current = current->prev;
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
    
    // 1. Операция клонирования списка
    DoubleListNode<T>* clone() const {
        if (!head) return nullptr;
        
        DoubleListNode<T>* newHead = nullptr;
        DoubleListNode<T>* newTail = nullptr;
        DoubleListNode<T>* current = head;
        
        while (current) {
            DoubleListNode<T>* newNode = new DoubleListNode<T>(current->data);
            if (!newHead) {
                newHead = newNode;
                newTail = newNode;
            } else {
                newTail->next = newNode;
                newNode->prev = newTail;
                newTail = newNode;
            }
            current = current->next;
        }
        
        return newHead;
    }
    
    // 2. Перегрузка оператора + (объединение списков)
    DoubleLinkedList<T> operator+(const DoubleLinkedList<T>& other) const {
        DoubleLinkedList<T> result;
        
        // Добавляем элементы первого списка
        DoubleListNode<T>* current = head;
        while (current) {
            result.pushBack(current->data);
            current = current->next;
        }
        
        // Добавляем элементы второго списка
        current = other.head;
        while (current) {
            result.pushBack(current->data);
            current = current->next;
        }
        
        return result;
    }
    
    // 3. Перегрузка оператора * (пересечение списков)
    DoubleLinkedList<T> operator*(const DoubleLinkedList<T>& other) const {
        DoubleLinkedList<T> result;
        
        DoubleListNode<T>* current = head;
        while (current) {
            // Проверяем, есть ли текущий элемент во втором списке
            DoubleListNode<T>* search = other.head;
            while (search) {
                if (search->data == current->data) {
                    // Проверяем, не добавлен ли уже этот элемент в результат
                    bool alreadyExists = false;
                    DoubleListNode<T>* resultCurrent = result.head;
                    while (resultCurrent) {
                        if (resultCurrent->data == current->data) {
                            alreadyExists = true;
                            break;
                        }
                        resultCurrent = resultCurrent->next;
                    }
                    
                    if (!alreadyExists) {
                        result.pushBack(current->data);
                    }
                    break;
                }
                search = search->next;
            }
            current = current->next;
        }
        
        return result;
    }
    
    // Получение головы и хвоста
    DoubleListNode<T>* getHead() const { return head; }
    DoubleListNode<T>* getTail() const { return tail; }
};

// Шаблонный класс Очередь на основе двусвязного списка
template<typename T>
class Queue : private DoubleLinkedList<T> {
public:
    // Конструктор
    Queue() : DoubleLinkedList<T>() {}
    
    // Добавление в очередь
    void enqueue(const T& value) {
        this->pushBack(value);
        cout << "Добавлен в очередь: " << value << " (размер: " << this->size() << ")" << endl;
    }
    
    // Удаление из очереди
    T dequeue() {
        if (this->isEmpty()) {
            throw runtime_error("Очередь пуста! Невозможно выполнить dequeue.");
        }
        T value = this->popFront();
        cout << "Удален из очереди: " << value << " (размер: " << this->size() << ")" << endl;
        return value;
    }
    
    // Просмотр первого элемента
    T front() const {
        return this->front();
    }
    
    // Просмотр последнего элемента
    T back() const {
        return this->back();
    }
    
    // Проверка на пустоту
    bool isEmpty() const {
        return this->isEmpty();
    }
    
    // Получение размера
    int size() const {
        return this->size();
    }
    
    // Очистка очереди
    void clear() {
        this->clear();
    }
    
    // Отображение очереди
    void display() const {
        cout << "Содержимое очереди (с начала): ";
        this->displayForward();
    }
};

// Демонстрация работы очереди
void demonstrateQueue() {
    cout << "\n========== ДЕМОНСТРАЦИЯ РАБОТЫ ОЧЕРЕДИ ==========" << endl;
    
    Queue<int> queue;
    
    cout << "\n--- Добавление элементов в очередь ---" << endl;
    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);
    queue.display();
    
    cout << "\n--- Просмотр элементов ---" << endl;
    cout << "Первый элемент: " << queue.front() << endl;
    cout << "Последний элемент: " << queue.back() << endl;
    
    cout << "\n--- Удаление элементов из очереди ---" << endl;
    while (!queue.isEmpty()) {
        queue.dequeue();
    }
    
    cout << "\n--- Проверка на пустоту ---" << endl;
    cout << "Очередь пуста? " << (queue.isEmpty() ? "Да" : "Нет") << endl;
}

// Демонстрация работы двусвязного списка с дополнительными операциями
void demonstrateDoubleLinkedList() {
    cout << "\n========== ДЕМОНСТРАЦИЯ ДВУСВЯЗНОГО СПИСКА ==========" << endl;
    
    DoubleLinkedList<int> list1;
    DoubleLinkedList<int> list2;
    
    // Заполняем первый список
    cout << "\nПервый список (с начала): ";
    list1.pushBack(1);
    list1.pushBack(2);
    list1.pushBack(3);
    list1.pushBack(4);
    list1.pushBack(5);
    list1.displayForward();
    
    cout << "Первый список (с конца): ";
    list1.displayBackward();
    
    // Заполняем второй список
    cout << "Второй список: ";
    list2.pushBack(4);
    list2.pushBack(5);
    list2.pushBack(6);
    list2.pushBack(7);
    list2.pushBack(8);
    list2.displayForward();
    
    // Тестируем клонирование
    cout << "\n--- Клонирование первого списка ---" << endl;
    DoubleListNode<int>* clonedHead = list1.clone();
    DoubleLinkedList<int> clonedList;
    DoubleListNode<int>* current = clonedHead;
    while (current) {
        clonedList.pushBack(current->data);
        current = current->next;
    }
    cout << "Клонированный список: ";
    clonedList.displayForward();
    
    // Тестируем оператор +
    cout << "\n--- Оператор + (объединение) ---" << endl;
    DoubleLinkedList<int> unionList = list1 + list2;
    cout << "Результат объединения: ";
    unionList.displayForward();
    
    // Тестируем оператор *
    cout << "\n--- Оператор * (пересечение) ---" << endl;
    DoubleLinkedList<int> intersectList = list1 * list2;
    cout << "Результат пересечения: ";
    intersectList.displayForward();
    
    // Очищаем память клонированного списка
    while (clonedHead) {
        DoubleListNode<int>* temp = clonedHead;
        clonedHead = clonedHead->next;
        delete temp;
    }
}

int main() {
    // Демонстрация стека
    demonstrateStack();
    
    // Демонстрация односвязного списка
    demonstrateLinkedList();
    
    // Демонстрация очереди (на основе двусвязного списка)
    demonstrateQueue();
    
    // Демонстрация двусвязного списка
    demonstrateDoubleLinkedList();
    
    return 0;
}
