#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <algorithm>
#include <limits>

using namespace std;

// ============================
// ЗАДАНИЕ 1: Транспонирование матрицы
// ============================

// Функция для создания матрицы
vector<vector<int>> createMatrix(int rows, int cols) {
    vector<vector<int>> matrix(rows, vector<int>(cols));
    int counter = 1;
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = counter++;
        }
    }
    return matrix;
}

// Функция для вывода матрицы
void printMatrix(const vector<vector<int>>& matrix, const string& title = "Матрица:") {
    cout << "\n" << title << "\n";
    for (const auto& row : matrix) {
        for (int val : row) {
            cout << setw(4) << val << " ";
        }
        cout << endl;
    }
}

// Функция транспонирования матрицы
vector<vector<int>> transposeMatrix(const vector<vector<int>>& matrix) {
    if (matrix.empty()) return {};
    
    int rows = matrix.size();
    int cols = matrix[0].size();
    
    // Создаем транспонированную матрицу (меняем местами строки и столбцы)
    vector<vector<int>> transposed(cols, vector<int>(rows));
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            transposed[j][i] = matrix[i][j];
        }
    }
    
    return transposed;
}

void task1() {
    cout << "=== ЗАДАНИЕ 1: ТРАНСПОНИРОВАНИЕ МАТРИЦЫ ===\n";
    
    int rows, cols;
    cout << "Введите количество строк матрицы: ";
    cin >> rows;
    cout << "Введите количество столбцов матрицы: ";
    cin >> cols;
    
    // Создаем исходную матрицу
    vector<vector<int>> original = createMatrix(rows, cols);
    printMatrix(original, "Исходная матрица:");
    
    // Транспонируем матрицу
    vector<vector<int>> transposed = transposeMatrix(original);
    printMatrix(transposed, "Транспонированная матрица:");
    
    cout << "Размеры исходной матрицы: " << rows << "x" << cols << endl;
    cout << "Размеры транспонированной матрицы: " << cols << "x" << rows << endl;
}

// ============================
// ЗАДАНИЕ 2: Телефонная книга
// ============================

struct Contact {
    string name;
    string phone;
};

class PhoneBook {
private:
    vector<Contact> contacts;
    
    // Вспомогательная функция для поиска контакта по имени
    int findByName(const string& name) {
        for (size_t i = 0; i < contacts.size(); i++) {
            if (contacts[i].name == name) {
                return i;
            }
        }
        return -1;
    }
    
    // Вспомогательная функция для поиска контакта по номеру телефона
    int findByPhone(const string& phone) {
        for (size_t i = 0; i < contacts.size(); i++) {
            if (contacts[i].phone == phone) {
                return i;
            }
        }
        return -1;
    }
    
public:
    // Добавление контакта
    void addContact() {
        Contact newContact;
        cout << "Введите имя: ";
        cin.ignore();
        getline(cin, newContact.name);
        
        // Проверка на существование контакта с таким именем
        if (findByName(newContact.name) != -1) {
            cout << "Контакт с таким именем уже существует!\n";
            return;
        }
        
        cout << "Введите номер телефона: ";
        getline(cin, newContact.phone);
        
        // Проверка на существование контакта с таким номером
        if (findByPhone(newContact.phone) != -1) {
            cout << "Контакт с таким номером телефона уже существует!\n";
            return;
        }
        
        contacts.push_back(newContact);
        cout << "Контакт добавлен успешно!\n";
    }
    
    // Поиск по имени
    void searchByName() {
        string name;
        cout << "Введите имя для поиска: ";
        cin.ignore();
        getline(cin, name);
        
        int index = findByName(name);
        if (index != -1) {
            cout << "Контакт найден:\n";
            cout << "Имя: " << contacts[index].name << endl;
            cout << "Телефон: " << contacts[index].phone << endl;
        } else {
            cout << "Контакт с именем '" << name << "' не найден.\n";
        }
    }
    
    // Поиск по номеру телефона
    void searchByPhone() {
        string phone;
        cout << "Введите номер телефона для поиска: ";
        cin.ignore();
        getline(cin, phone);
        
        int index = findByPhone(phone);
        if (index != -1) {
            cout << "Контакт найден:\n";
            cout << "Имя: " << contacts[index].name << endl;
            cout << "Телефон: " << contacts[index].phone << endl;
        } else {
            cout << "Контакт с номером '" << phone << "' не найден.\n";
        }
    }
    
    // Изменение данных контакта
    void editContact() {
        string name;
        cout << "Введите имя контакта для изменения: ";
        cin.ignore();
        getline(cin, name);
        
        int index = findByName(name);
        if (index == -1) {
            cout << "Контакт не найден!\n";
            return;
        }
        
        cout << "Текущие данные:\n";
        cout << "Имя: " << contacts[index].name << endl;
        cout << "Телефон: " << contacts[index].phone << endl;
        
        cout << "\nВведите новое имя (или нажмите Enter для пропуска): ";
        string newName;
        getline(cin, newName);
        
        if (!newName.empty()) {
            // Проверяем, не существует ли уже контакт с таким именем
            int existingIndex = findByName(newName);
            if (existingIndex != -1 && existingIndex != index) {
                cout << "Контакт с таким именем уже существует!\n";
                return;
            }
            contacts[index].name = newName;
        }
        
        cout << "Введите новый номер телефона (или нажмите Enter для пропуска): ";
        string newPhone;
        getline(cin, newPhone);
        
        if (!newPhone.empty()) {
            // Проверяем, не существует ли уже контакт с таким номером
            int existingIndex = findByPhone(newPhone);
            if (existingIndex != -1 && existingIndex != index) {
                cout << "Контакт с таким номером телефона уже существует!\n";
                return;
            }
            contacts[index].phone = newPhone;
        }
        
        cout << "Данные контакта обновлены успешно!\n";
    }
    
    // Показать все контакты
    void showAllContacts() {
        if (contacts.empty()) {
            cout << "Телефонная книга пуста.\n";
            return;
        }
        
        cout << "\n=== ТЕЛЕФОННАЯ КНИГА ===\n";
        cout << setw(30) << left << "Имя" << "Телефон\n";
        cout << string(50, '-') << endl;
        
        for (const auto& contact : contacts) {
            cout << setw(30) << left << contact.name 
                 << contact.phone << endl;
        }
    }
    
    // Удаление контакта
    void deleteContact() {
        string name;
        cout << "Введите имя контакта для удаления: ";
        cin.ignore();
        getline(cin, name);
        
        int index = findByName(name);
        if (index == -1) {
            cout << "Контакт не найден!\n";
            return;
        }
        
        contacts.erase(contacts.begin() + index);
        cout << "Контакт удален успешно!\n";
    }
};

void task2() {
    cout << "\n=== ЗАДАНИЕ 2: ТЕЛЕФОННАЯ КНИГА ===\n";
    
    PhoneBook phoneBook;
    int choice;
    
    do {
        cout << "\n=== МЕНЮ ТЕЛЕФОННОЙ КНИГИ ===\n";
        cout << "1. Показать все контакты\n";
        cout << "2. Добавить контакт\n";
        cout << "3. Поиск по имени\n";
        cout << "4. Поиск по номеру телефона\n";
        cout << "5. Изменить контакт\n";
        cout << "6. Удалить контакт\n";
        cout << "0. Выход\n";
        cout << "Выберите действие: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                phoneBook.showAllContacts();
                break;
            case 2:
                phoneBook.addContact();
                break;
            case 3:
                phoneBook.searchByName();
                break;
            case 4:
                phoneBook.searchByPhone();
                break;
            case 5:
                phoneBook.editContact();
                break;
            case 6:
                phoneBook.deleteContact();
                break;
            case 0:
                cout << "Выход из телефонной книги...\n";
                break;
            default:
                cout << "Неверный выбор! Попробуйте снова.\n";
        }
    } while (choice != 0);
}

// ============================
// Главное меню программы
// ============================
int main() {
    int mainChoice;
    
    do {
        cout << "\n=== ГЛАВНОЕ МЕНЮ ===\n";
        cout << "1. Задание 1: Транспонирование матрицы\n";
        cout << "2. Задание 2: Телефонная книга\n";
        cout << "0. Выход из программы\n";
        cout << "Выберите задание: ";
        cin >> mainChoice;
        
        switch (mainChoice) {
            case 1:
                task1();
                break;
            case 2:
                task2();
                break;
            case 0:
                cout << "Программа завершена. До свидания!\n";
                break;
            default:
                cout << "Неверный выбор! Попробуйте снова.\n";
        }
    } while (mainChoice != 0);
    
    return 0;
}
