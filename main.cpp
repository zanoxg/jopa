#include <iostream>
#include <cmath>
#include <stdexcept>

using namespace std;

// Функция для нахождения наибольшего общего делителя
int gcd(int a, int b) {
    a = abs(a);
    b = abs(b);
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// ==================== ЗАДАНИЕ 1: КЛАСС ДРОБЬ ====================
class Fraction {
private:
    int numerator;     // Числитель
    int denominator;   // Знаменатель

    void reduce() {
        if (denominator == 0) {
            throw invalid_argument("Знаменатель не может быть равен 0");
        }
        
        if (denominator < 0) {
            numerator = -numerator;
            denominator = -denominator;
        }
        
        int divisor = gcd(numerator, denominator);
        if (divisor != 0) {
            numerator /= divisor;
            denominator /= divisor;
        }
    }

public:
    // Конструкторы
    Fraction(int num = 0, int den = 1) : numerator(num), denominator(den) {
        if (denominator == 0) {
            throw invalid_argument("Знаменатель не может быть равен 0");
        }
        reduce();
    }

    // Конструктор копирования
    Fraction(const Fraction& other) : numerator(other.numerator), denominator(other.denominator) {}

    // Оператор присваивания
    Fraction& operator=(const Fraction& other) {
        if (this != &other) {
            numerator = other.numerator;
            denominator = other.denominator;
        }
        return *this;
    }

    // Арифметические операторы
    Fraction operator+(const Fraction& other) const {
        int newNumerator = numerator * other.denominator + other.numerator * denominator;
        int newDenominator = denominator * other.denominator;
        return Fraction(newNumerator, newDenominator);
    }

    Fraction operator-(const Fraction& other) const {
        int newNumerator = numerator * other.denominator - other.numerator * denominator;
        int newDenominator = denominator * other.denominator;
        return Fraction(newNumerator, newDenominator);
    }

    Fraction operator*(const Fraction& other) const {
        int newNumerator = numerator * other.numerator;
        int newDenominator = denominator * other.denominator;
        return Fraction(newNumerator, newDenominator);
    }

    Fraction operator/(const Fraction& other) const {
        if (other.numerator == 0) {
            throw invalid_argument("Деление на ноль!");
        }
        int newNumerator = numerator * other.denominator;
        int newDenominator = denominator * other.numerator;
        return Fraction(newNumerator, newDenominator);
    }

    // Составные операторы присваивания
    Fraction& operator+=(const Fraction& other) {
        *this = *this + other;
        return *this;
    }

    Fraction& operator-=(const Fraction& other) {
        *this = *this - other;
        return *this;
    }

    Fraction& operator*=(const Fraction& other) {
        *this = *this * other;
        return *this;
    }

    Fraction& operator/=(const Fraction& other) {
        *this = *this / other;
        return *this;
    }

    // Операторы сравнения
    bool operator==(const Fraction& other) const {
        return numerator == other.numerator && denominator == other.denominator;
    }

    bool operator!=(const Fraction& other) const {
        return !(*this == other);
    }

    // Операторы ввода/вывода
    friend ostream& operator<<(ostream& os, const Fraction& frac);
    friend istream& operator>>(istream& is, Fraction& frac);

    // Преобразование в double
    double toDouble() const {
        return static_cast<double>(numerator) / denominator;
    }

    // Геттеры
    int getNumerator() const { return numerator; }
    int getDenominator() const { return denominator; }
};

ostream& operator<<(ostream& os, const Fraction& frac) {
    if (frac.denominator == 1) {
        os << frac.numerator;
    } else {
        os << frac.numerator << "/" << frac.denominator;
    }
    return os;
}

istream& operator>>(istream& is, Fraction& frac) {
    char slash;
    is >> frac.numerator >> slash >> frac.denominator;
    if (frac.denominator == 0) {
        throw invalid_argument("Знаменатель не может быть равен 0");
    }
    frac.reduce();
    return is;
}

// ==================== ЗАДАНИЕ 2: КЛАСС COMPLEX ====================
class Complex {
private:
    double real;      // Действительная часть
    double imag;      // Мнимая часть

public:
    // Конструкторы
    Complex(double r = 0, double i = 0) : real(r), imag(i) {}

    // Конструктор копирования
    Complex(const Complex& other) : real(other.real), imag(other.imag) {}

    // Оператор присваивания
    Complex& operator=(const Complex& other) {
        if (this != &other) {
            real = other.real;
            imag = other.imag;
        }
        return *this;
    }

    // Арифметические операторы
    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imag + other.imag);
    }

    Complex operator-(const Complex& other) const {
        return Complex(real - other.real, imag - other.imag);
    }

    Complex operator*(const Complex& other) const {
        return Complex(
            real * other.real - imag * other.imag,
            real * other.imag + imag * other.real
        );
    }

    Complex operator/(const Complex& other) const {
        double denominator = other.real * other.real + other.imag * other.imag;
        if (denominator == 0) {
            throw invalid_argument("Деление на ноль!");
        }
        return Complex(
            (real * other.real + imag * other.imag) / denominator,
            (imag * other.real - real * other.imag) / denominator
        );
    }

    // Составные операторы присваивания
    Complex& operator+=(const Complex& other) {
        *this = *this + other;
        return *this;
    }

    Complex& operator-=(const Complex& other) {
        *this = *this - other;
        return *this;
    }

    Complex& operator*=(const Complex& other) {
        *this = *this * other;
        return *this;
    }

    Complex& operator/=(const Complex& other) {
        *this = *this / other;
        return *this;
    }

    // Операторы сравнения
    bool operator==(const Complex& other) const {
        return (fabs(real - other.real) < 1e-10) && (fabs(imag - other.imag) < 1e-10);
    }

    bool operator!=(const Complex& other) const {
        return !(*this == other);
    }

    // Операторы ввода/вывода
    friend ostream& operator<<(ostream& os, const Complex& comp);
    friend istream& operator>>(istream& is, Complex& comp);

    // Дополнительные методы
    double magnitude() const {
        return sqrt(real * real + imag * imag);
    }

    double argument() const {
        return atan2(imag, real);
    }

    Complex conjugate() const {
        return Complex(real, -imag);
    }

    // Геттеры
    double getReal() const { return real; }
    double getImag() const { return imag; }
};

ostream& operator<<(ostream& os, const Complex& comp) {
    os << comp.real;
    if (comp.imag >= 0) {
        os << "+" << comp.imag << "i";
    } else {
        os << comp.imag << "i";
    }
    return os;
}

istream& operator>>(istream& is, Complex& comp) {
    is >> comp.real >> comp.imag;
    return is;
}

// ==================== ПРИМЕР ИСПОЛЬЗОВАНИЯ ====================
int main() {
    cout << "========== ТЕСТИРОВАНИЕ ДРОБЕЙ ==========" << endl;
    try {
        Fraction f1(2, 3);
        Fraction f2(3, 4);
        
        cout << "f1 = " << f1 << endl;
        cout << "f2 = " << f2 << endl;
        cout << "f1 + f2 = " << f1 + f2 << endl;
        cout << "f1 - f2 = " << f1 - f2 << endl;
        cout << "f1 * f2 = " << f1 * f2 << endl;
        cout << "f1 / f2 = " << f1 / f2 << endl;
        
        Fraction f3(5, 10);
        cout << "f3 = " << f3 << " (сокращённая форма)" << endl;
        
        Fraction f4(7, 1);
        cout << "f4 = " << f4 << " (целое число)" << endl;
        
        // Составные операторы
        Fraction f5(1, 2);
        f5 += Fraction(1, 3);
        cout << "1/2 + 1/3 = " << f5 << endl;
        
        // Ввод с клавиатуры
        Fraction f6;
        cout << "Введите дробь (в формате a/b): ";
        cin >> f6;
        cout << "Вы ввели: " << f6 << endl;
        
    } catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
    }
    
    cout << "\n========== ТЕСТИРОВАНИЕ КОМПЛЕКСНЫХ ЧИСЕЛ ==========" << endl;
    try {
        Complex c1(3, 4);
        Complex c2(1, 2);
        
        cout << "c1 = " << c1 << endl;
        cout << "c2 = " << c2 << endl;
        cout << "c1 + c2 = " << c1 + c2 << endl;
        cout << "c1 - c2 = " << c1 - c2 << endl;
        cout << "c1 * c2 = " << c1 * c2 << endl;
        cout << "c1 / c2 = " << c1 / c2 << endl;
        
        // Дополнительные операции
        cout << "Модуль c1: " << c1.magnitude() << endl;
        cout << "Аргумент c1: " << c1.argument() << " рад" << endl;
        cout << "Сопряжённое c1: " << c1.conjugate() << endl;
        
        // Составные операторы
        Complex c3(2, 1);
        c3 += Complex(1, 3);
        cout << "(2+1i) + (1+3i) = " << c3 << endl;
        
        // Ввод с клавиатуры
        Complex c4;
        cout << "Введите комплексное число (действительная и мнимая части через пробел): ";
        cin >> c4;
        cout << "Вы ввели: " << c4 << endl;
        
    } catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
    }
    
    return 0;
}
