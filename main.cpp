#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>

using namespace std;

// Базовый класс с виртуальным наследованием
class Pet {
protected:
    string name;
    string species;
    int age;
    double weight;

public:
    Pet(const string& n = "", const string& s = "", int a = 0, double w = 0.0)
        : name(n), species(s), age(a), weight(w) {
        cout << "Конструктор Pet: " << name << " (" << species << ")" << endl;
    }

    virtual ~Pet() {
        cout << "Деструктор Pet: " << name << endl;
    }

    // Конструктор копирования
    Pet(const Pet& other)
        : name(other.name), species(other.species), age(other.age), weight(other.weight) {
        cout << "Конструктор копирования Pet: " << name << endl;
    }

    // Оператор присваивания
    Pet& operator=(const Pet& other) {
        if (this != &other) {
            name = other.name;
            species = other.species;
            age = other.age;
            weight = other.weight;
            cout << "Оператор присваивания Pet" << endl;
        }
        return *this;
    }

    // Виртуальные методы
    virtual void makeSound() const = 0; // Чисто виртуальный метод
    virtual void display() const {
        cout << "Имя: " << name << ", Вид: " << species 
             << ", Возраст: " << age << " лет, Вес: " << weight << " кг" << endl;
    }

    // Геттеры
    string getName() const { return name; }
    string getSpecies() const { return species; }
    int getAge() const { return age; }
    double getWeight() const { return weight; }
};

// Производный класс "Собака"
class Dog : virtual public Pet {
private:
    string breed;      // Порода
    bool isTrained;    // Дрессирована или нет

public:
    Dog(const string& n = "", int a = 0, double w = 0.0, const string& b = "", bool trained = false)
        : Pet(n, "Собака", a, w), breed(b), isTrained(trained) {
        cout << "Конструктор Dog: " << name << " (порода: " << breed << ")" << endl;
    }

    Dog(const Dog& other) : Pet(other), breed(other.breed), isTrained(other.isTrained) {
        cout << "Конструктор копирования Dog" << endl;
    }

    ~Dog() override {
        cout << "Деструктор Dog: " << name << endl;
    }

    void makeSound() const override {
        cout << name << " говорит: Гав-гав!" << endl;
    }

    void display() const override {
        Pet::display();
        cout << "Порода: " << breed << ", Дрессирована: " << (isTrained ? "Да" : "Нет") << endl;
    }

    void fetch() const {
        cout << name << " приносит палку!" << endl;
    }
};

// Производный класс "Кошка"
class Cat : virtual public Pet {
private:
    string color;      // Окрас
    bool isIndoor;     // Домашняя или уличная

public:
    Cat(const string& n = "", int a = 0, double w = 0.0, const string& c = "", bool indoor = true)
        : Pet(n, "Кошка", a, w), color(c), isIndoor(indoor) {
        cout << "Конструктор Cat: " << name << " (окрас: " << color << ")" << endl;
    }

    Cat(const Cat& other) : Pet(other), color(other.color), isIndoor(other.isIndoor) {
        cout << "Конструктор копирования Cat" << endl;
    }

    ~Cat() override {
        cout << "Деструктор Cat: " << name << endl;
    }

    void makeSound() const override {
        cout << name << " говорит: Мяу-мяу!" << endl;
    }

    void display() const override {
        Pet::display();
        cout << "Окрас: " << color << ", Домашняя: " << (isIndoor ? "Да" : "Нет") << endl;
    }

    void climb() const {
        cout << name << " забирается на дерево!" << endl;
    }
};

// Производный класс "Попугай"
class Parrot : virtual public Pet {
private:
    string color;      // Окрас
    bool canTalk;      // Умеет говорить

public:
    Parrot(const string& n = "", int a = 0, double w = 0.0, const string& c = "", bool talk = false)
        : Pet(n, "Попугай", a, w), color(c), canTalk(talk) {
        cout << "Конструктор Parrot: " << name << " (окрас: " << color << ")" << endl;
    }

    Parrot(const Parrot& other) : Pet(other), color(other.color), canTalk(other.canTalk) {
        cout << "Конструктор копирования Parrot" << endl;
    }

    ~Parrot() override {
        cout << "Деструктор Parrot: " << name << endl;
    }

    void makeSound() const override {
        if (canTalk) {
            cout << name << " говорит: Привет! Как дела?" << endl;
        } else {
            cout << name << " издаёт: Чирик-чирик!" << endl;
        }
    }

    void display() const override {
        Pet::display();
        cout << "Окрас: " << color << ", Умеет говорить: " << (canTalk ? "Да" : "Нет") << endl;
    }

    void fly() const {
        cout << name << " летает по комнате!" << endl;
    }
};

// Базовый класс "Строка" с виртуальным наследованием
class String {
protected:
    char* str;
    size_t length;

    void copyFrom(const char* s) {
        if (s) {
            length = strlen(s);
            str = new char[length + 1];
            strcpy(str, s);
        } else {
            str = nullptr;
            length = 0;
        }
    }

    void freeMemory() {
        delete[] str;
        str = nullptr;
        length = 0;
    }

public:
    // 1) Конструктор без параметров
    String() : str(nullptr), length(0) {
        cout << "Конструктор String без параметров" << endl;
        str = new char[1];
        str[0] = '\0';
    }

    // 2) Конструктор, принимающий C-строку
    String(const char* s) : str(nullptr), length(0) {
        cout << "Конструктор String из C-строки: " << (s ? s : "null") << endl;
        if (s) {
            copyFrom(s);
        } else {
            str = new char[1];
            str[0] = '\0';
        }
    }

    // 3) Конструктор копирования
    String(const String& other) : str(nullptr), length(0) {
        cout << "Конструктор копирования String" << endl;
        copyFrom(other.str);
    }

    // 4) Оператор присваивания
    String& operator=(const String& other) {
        cout << "Оператор присваивания String" << endl;
        if (this != &other) {
            freeMemory();
            copyFrom(other.str);
        }
        return *this;
    }

    // 5) Получение длины строки
    size_t getLength() const {
        return length;
    }

    // 6) Очистка строки
    void clear() {
        freeMemory();
        str = new char[1];
        str[0] = '\0';
        length = 0;
    }

    // 7) Деструктор
    virtual ~String() {
        cout << "Деструктор String" << endl;
        freeMemory();
    }

    // 8) Конкатенация строк (операторы + и +=)
    String operator+(const String& other) const {
        String result;
        delete[] result.str;
        
        result.length = length + other.length;
        result.str = new char[result.length + 1];
        
        strcpy(result.str, str);
        strcat(result.str, other.str);
        
        return result;
    }

    String& operator+=(const String& other) {
        *this = *this + other;
        return *this;
    }

    // 9) Проверка на равенство и неравенство
    bool operator==(const String& other) const {
        return strcmp(str, other.str) == 0;
    }

    bool operator!=(const String& other) const {
        return !(*this == other);
    }

    // Дополнительные методы
    const char* c_str() const {
        return str;
    }

    virtual void display() const {
        cout << "Строка: \"" << (str ? str : "") << "\", Длина: " << length << endl;
    }
};

// Производный класс "Битовая строка"
class BitString : virtual public String {
private:
    bool isValidBitString(const char* s) const {
        if (!s) return false;
        for (size_t i = 0; i < strlen(s); i++) {
            if (s[i] != '0' && s[i] != '1') {
                return false;
            }
        }
        return true;
    }

    long long toInteger() const {
        if (length == 0) return 0;
        
        // Проверка на знак (первый бит - знаковый)
        bool isNegative = (str[0] == '1');
        long long value = 0;
        
        for (size_t i = 1; i < length; i++) {
            value = (value << 1) | (str[i] - '0');
        }
        
        if (isNegative) {
            // Преобразование из дополнительного кода
            value = -(value + 1);
        }
        
        return value;
    }

    void fromInteger(long long num, size_t bits) {
        freeMemory();
        length = bits;
        str = new char[length + 1];
        
        bool isNegative = (num < 0);
        if (isNegative) {
            num = -num - 1;
        }
        
        // Заполняем биты с конца
        for (int i = length - 1; i >= 0; i--) {
            str[i] = (num & 1) ? '1' : '0';
            num >>= 1;
        }
        
        if (isNegative) {
            // Инвертируем все биты (дополнительный код уже учтен)
            for (size_t i = 0; i < length; i++) {
                str[i] = (str[i] == '0') ? '1' : '0';
            }
        }
        
        str[length] = '\0';
    }

public:
    // 1) Конструктор без параметров
    BitString() : String() {
        cout << "Конструктор BitString без параметров" << endl;
    }

    // 2) Конструктор, принимающий C-строку
    BitString(const char* s) : String() {
        cout << "Конструктор BitString из C-строки: " << (s ? s : "null") << endl;
        if (s && isValidBitString(s)) {
            freeMemory();
            copyFrom(s);
        } else {
            // Если строка содержит недопустимые символы, делаем её пустой
            clear();
            cout << "Предупреждение: битовая строка содержит недопустимые символы, создана пустая строка" << endl;
        }
    }

    // 3) Конструктор копирования
    BitString(const BitString& other) : String(other) {
        cout << "Конструктор копирования BitString" << endl;
    }

    // 4) Оператор присваивания
    BitString& operator=(const BitString& other) {
        cout << "Оператор присваивания BitString" << endl;
        if (this != &other) {
            String::operator=(other);
        }
        return *this;
    }

    // 5) Деструктор
    ~BitString() override {
        cout << "Деструктор BitString" << endl;
    }

    // 6) Изменение знака числа (перевод в дополнительный код)
    void changeSign() {
        if (length == 0) return;
        
        // Инвертируем все биты
        for (size_t i = 0; i < length; i++) {
            str[i] = (str[i] == '0') ? '1' : '0';
        }
        
        // Прибавляем 1
        int carry = 1;
        for (int i = length - 1; i >= 0 && carry; i--) {
            if (str[i] == '0') {
                str[i] = '1';
                carry = 0;
            } else {
                str[i] = '0';
            }
        }
    }

    // 7) Сложение битовых строк (оператор +)
    BitString operator+(const BitString& other) const {
        long long num1 = toInteger();
        long long num2 = other.toInteger();
        long long sum = num1 + num2;
        
        BitString result;
        result.fromInteger(sum, max(length, other.length) + 1);
        return result;
    }

    // 8) Проверка на равенство и неравенство
    bool operator==(const BitString& other) const {
        return String::operator==(other);
    }

    bool operator!=(const BitString& other) const {
        return String::operator!=(other);
    }

    // Дополнительные методы
    void display() const override {
        cout << "Битовая строка: \"" << (str ? str : "") 
             << "\", Длина: " << length 
             << ", Значение: " << toInteger() << endl;
    }

    long long getValue() const {
        return toInteger();
    }
};

// Базовый шаблонный класс base
template<typename T1, typename T2>
class Base {
protected:
    T1 value1;
    T2 value2;

public:
    // Конструкторы
    Base() : value1(T1()), value2(T2()) {
        cout << "Конструктор Base (по умолчанию)" << endl;
    }

    Base(const T1& v1, const T2& v2) : value1(v1), value2(v2) {
        cout << "Конструктор Base с параметрами: " << value1 << ", " << value2 << endl;
    }

    // Конструктор копирования
    Base(const Base& other) : value1(other.value1), value2(other.value2) {
        cout << "Конструктор копирования Base" << endl;
    }

    // Деструктор
    virtual ~Base() {
        cout << "Деструктор Base" << endl;
    }

    // Оператор присваивания
    Base& operator=(const Base& other) {
        if (this != &other) {
            value1 = other.value1;
            value2 = other.value2;
            cout << "Оператор присваивания Base" << endl;
        }
        return *this;
    }

    // Методы доступа
    T1 getValue1() const { return value1; }
    T2 getValue2() const { return value2; }
    void setValue1(const T1& v) { value1 = v; }
    void setValue2(const T2& v) { value2 = v; }

    virtual void display() const {
        cout << "Base: value1 = " << value1 << ", value2 = " << value2 << endl;
    }
};

// Потомок child
template<typename T1, typename T2, typename T3, typename T4>
class Child : public Base<T1, T2> {
protected:
    T3 value3;
    T4 value4;

public:
    // Конструкторы
    Child() : Base<T1, T2>(), value3(T3()), value4(T4()) {
        cout << "Конструктор Child (по умолчанию)" << endl;
    }

    Child(const T1& v1, const T2& v2, const T3& v3, const T4& v4)
        : Base<T1, T2>(v1, v2), value3(v3), value4(v4) {
        cout << "Конструктор Child с параметрами" << endl;
    }

    // Конструктор копирования
    Child(const Child& other) : Base<T1, T2>(other), value3(other.value3), value4(other.value4) {
        cout << "Конструктор копирования Child" << endl;
    }

    // Деструктор
    ~Child() override {
        cout << "Деструктор Child" << endl;
    }

    // Оператор присваивания
    Child& operator=(const Child& other) {
        if (this != &other) {
            Base<T1, T2>::operator=(other);
            value3 = other.value3;
            value4 = other.value4;
            cout << "Оператор присваивания Child" << endl;
        }
        return *this;
    }

    // Методы доступа
    T3 getValue3() const { return value3; }
    T4 getValue4() const { return value4; }
    void setValue3(const T3& v) { value3 = v; }
    void setValue4(const T4& v) { value4 = v; }

    void display() const override {
        Base<T1, T2>::display();
        cout << "Child: value3 = " << value3 << ", value4 = " << value4 << endl;
    }
};

// Потомок child2
template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
class Child2 : public Child<T1, T2, T3, T4> {
private:
    T5 value5;
    T6 value6;

public:
    // Конструкторы
    Child2() : Child<T1, T2, T3, T4>(), value5(T5()), value6(T6()) {
        cout << "Конструктор Child2 (по умолчанию)" << endl;
    }

    Child2(const T1& v1, const T2& v2, const T3& v3, const T4& v4, const T5& v5, const T6& v6)
        : Child<T1, T2, T3, T4>(v1, v2, v3, v4), value5(v5), value6(v6) {
        cout << "Конструктор Child2 с параметрами" << endl;
    }

    // Конструктор копирования
    Child2(const Child2& other) 
        : Child<T1, T2, T3, T4>(other), value5(other.value5), value6(other.value6) {
        cout << "Конструктор копирования Child2" << endl;
    }

    // Деструктор
    ~Child2() override {
        cout << "Деструктор Child2" << endl;
    }

    // Оператор присваивания
    Child2& operator=(const Child2& other) {
        if (this != &other) {
            Child<T1, T2, T3, T4>::operator=(other);
            value5 = other.value5;
            value6 = other.value6;
            cout << "Оператор присваивания Child2" << endl;
        }
        return *this;
    }

    // Методы доступа
    T5 getValue5() const { return value5; }
    T6 getValue6() const { return value6; }
    void setValue5(const T5& v) { value5 = v; }
    void setValue6(const T6& v) { value6 = v; }

    void display() const override {
        Child<T1, T2, T3, T4>::display();
        cout << "Child2: value5 = " << value5 << ", value6 = " << value6 << endl;
    }
};

int main() {
    cout << "========== ТЕСТИРОВАНИЕ ДОМАШНИХ ЖИВОТНЫХ ==========" << endl;
    
    // Создание объектов
    Dog dog("Рекс", 3, 25.5, "Немецкая овчарка", true);
    Cat cat("Мурка", 2, 4.2, "Рыжий", true);
    Parrot parrot("Кеша", 5, 0.5, "Зелёный", true);
    
    cout << "\n--- Информация о животных ---" << endl;
    dog.display();
    dog.makeSound();
    dog.fetch();
    
    cout << endl;
    cat.display();
    cat.makeSound();
    cat.climb();
    
    cout << endl;
    parrot.display();
    parrot.makeSound();
    parrot.fly();
    
    // Массив указателей на базовый класс для демонстрации полиморфизма
    cout << "\n--- Полиморфизм ---" << endl;
    Pet* pets[] = {&dog, &cat, &parrot};
    for (int i = 0; i < 3; i++) {
        pets[i]->makeSound();
    }
    
    cout << "\n========== ТЕСТИРОВАНИЕ СТРОК И БИТОВЫХ СТРОК ==========" << endl;
    
    // Тестирование класса String
    String s1("Hello");
    String s2(" World");
    String s3 = s1 + s2;
    
    cout << "s1: " << s1.c_str() << ", длина: " << s1.getLength() << endl;
    cout << "s2: " << s2.c_str() << ", длина: " << s2.getLength() << endl;
    cout << "s3 = s1 + s2: " << s3.c_str() << ", длина: " << s3.getLength() << endl;
    
    s1 += s2;
    cout << "s1 += s2: " << s1.c_str() << endl;
    
    cout << "s1 == s3? " << (s1 == s3 ? "Да" : "Нет") << endl;
    
    // Тестирование класса BitString
    BitString bs1("1010");  // 10 в десятичной (если 4 бита)
    BitString bs2("0101");  // 5 в десятичной
    
    cout << "\nБитовые строки:" << endl;
    bs1.display();
    bs2.display();
    
    BitString bs3 = bs1 + bs2;
    cout << "bs1 + bs2 = ";
    bs3.display();
    
    cout << "\nТестирование с недопустимыми символами:" << endl;
    BitString bs4("1023");
    bs4.display();
    
    cout << "\nИзменение знака:" << endl;
    BitString bs5("0011"); // 3
    bs5.display();
    bs5.changeSign();
    cout << "После изменения знака: ";
    bs5.display();
    
    cout << "\n========== ТЕСТИРОВАНИЕ ШАБЛОННОГО НАСЛЕДОВАНИЯ ==========" << endl;
    
    // Тестирование Base
    Base<int, double> base1(10, 3.14);
    base1.display();
    
    // Тестирование Child
    Child<int, double, string, char> child1(5, 2.71, "Hello", 'A');
    child1.display();
    
    // Тестирование Child2
    Child2<int, double, string, char, float, bool> child2(
        1, 1.414, "World", 'B', 3.14159f, true
    );
    child2.display();
    
    // Демонстрация копирования
    cout << "\n--- Демонстрация копирования ---" << endl;
    Child2<int, double, string, char, float, bool> child3 = child2;
    child3.display();
    
    cout << "\n========== ВИРТУАЛЬНОЕ НАСЛЕДОВАНИЕ ==========" << endl;
    // Виртуальное наследование уже реализовано в классах Pet и String
    
    return 0;
}
