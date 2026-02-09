#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <limits>

class Subscriber {
private:
    char* fullName;      // ФИО (динамическая память)
    char* homePhone;     // Домашний телефон
    char* workPhone;     // Рабочий телефон
    char* mobilePhone;   // Мобильный телефон
    char* extraInfo;     // Дополнительная информация
    
    // Вспомогательная функция для копирования строк
    void copyString(char*& dest, const char* src) {
        if (src == nullptr) {
            dest = nullptr;
            return;
        }
        dest = new char[strlen(src) + 1];
        strcpy(dest, src);
    }

public:
    // Конструктор по умолчанию
    Subscriber() : fullName(nullptr), homePhone(nullptr), 
                   workPhone(nullptr), mobilePhone(nullptr), extraInfo(nullptr) {}
    
    // Конструктор с параметрами
    Subscriber(const char* name, const char* home = "", const char* work = "", 
               const char* mobile = "", const char* info = "") {
        copyString(fullName, name);
        copyString(homePhone, home);
        copyString(workPhone, work);
        copyString(mobilePhone, mobile);
        copyString(extraInfo, info);
    }
    
    // Конструктор копирования
    Subscriber(const Subscriber& other) {
        copyString(fullName, other.fullName);
        copyString(homePhone, other.homePhone);
        copyString(workPhone, other.workPhone);
        copyString(mobilePhone, other.mobilePhone);
        copyString(extraInfo, other.extraInfo);
    }
    
    // Оператор присваивания
    Subscriber& operator=(const Subscriber& other) {
        if (this != &other) {
            // Освобождаем старую память
            delete[] fullName;
            delete[] homePhone;
            delete[] workPhone;
            delete[] mobilePhone;
            delete[] extraInfo;
            
            // Копируем новые данные
            copyString(fullName, other.fullName);
            copyString(homePhone, other.homePhone);
            copyString(workPhone, other.workPhone);
            copyString(mobilePhone, other.mobilePhone);
            copyString(extraInfo, other.extraInfo);
        }
        return *this;
    }
    
    // Деструктор
    ~Subscriber() {
        delete[] fullName;
        delete[] homePhone;
        delete[] workPhone;
        delete[] mobilePhone;
        delete[] extraInfo;
    }
    
    // Геттеры (inline функции)
    inline const char* getFullName() const { return fullName; }
    inline const char* getHomePhone() const { return homePhone; }
    inline const char* getWorkPhone() const { return workPhone; }
    inline const char* getMobilePhone() const { return mobilePhone; }
    inline const char* getExtraInfo() const { return extraInfo; }
    
    // Сеттеры (inline функции)
    inline void setFullName(const char* name) {
        delete[] fullName;
        copyString(fullName, name);
    }
    
    inline void setHomePhone(const char* phone) {
        delete[] homePhone;
        copyString(homePhone, phone);
    }
    
    inline void setWorkPhone(const char* phone) {
        delete[] workPhone;
        copyString(workPhone, phone);
    }
    
    inline void setMobilePhone(const char* phone) {
        delete[] mobilePhone;
        copyString(mobilePhone, phone);
    }
    
    inline void setExtraInfo(const char* info) {
        delete[] extraInfo;
        copyString(extraInfo, info);
    }
    
    // Функция для вывода информации об абоненте
    void display() const {
        std::cout << "\n╔══════════════════════════════════════════════╗\n";
        std::cout << "║              ИНФОРМАЦИЯ О КОНТАКТЕ           ║\n";
        std::cout << "╠══════════════════════════════════════════════╣\n";
        std::cout << "║ ФИО:           " << std::setw(30) << std::left 
                  << (fullName ? fullName : "-") << "║\n";
        std::cout << "║ Домашний тел.: " << std::setw(30) << std::left 
                  << (homePhone ? homePhone : "-") << "║\n";
        std::cout << "║ Рабочий тел.:  " << std::setw(30) << std::left 
                  << (workPhone ? workPhone : "-") << "║\n";
        std::cout << "║ Мобильный тел.:" << std::setw(30) << std::left 
                  << (mobilePhone ? mobilePhone : "-") << "║\n";
        std::cout << "║ Доп. инфо:     " << std::setw(30) << std::left 
                  << (extraInfo ? extraInfo : "-") << "║\n";
        std::cout << "╚══════════════════════════════════════════════╝\n";
    }
    
    // Функция для сохранения в файл
    void saveToFile(std::ofstream& file) const {
        file << (fullName ? fullName : "") << "\n";
        file << (homePhone ? homePhone : "") << "\n";
        file << (workPhone ? workPhone : "") << "\n";
        file << (mobilePhone ? mobilePhone : "") << "\n";
        file << (extraInfo ? extraInfo : "") << "\n";
    }
    
    // Функция для загрузки из файла
    void loadFromFile(std::ifstream& file) {
        char buffer[256];
        
        file.getline(buffer, 256);
        setFullName(buffer);
        
        file.getline(buffer, 256);
        setHomePhone(buffer);
        
        file.getline(buffer, 256);
        setWorkPhone(buffer);
        
        file.getline(buffer, 256);
        setMobilePhone(buffer);
        
        file.getline(buffer, 256);
        setExtraInfo(buffer);
    }
};

class PhoneBook {
private:
    std::vector<Subscriber> subscribers;
    
    // Функция для ввода строки с пробелами
    void inputString(char* buffer, int size, const char* prompt) {
        std::cout << prompt;
        std::cin.getline(buffer, size);
        
        // Если ввод был пустым, запрашиваем снова
        if (strlen(buffer) == 0) {
            std::cout << "Поле не может быть пустым! ";
            inputString(buffer, size, prompt);
        }
    }

public:
    // Деструктор
    ~PhoneBook() {
        subscribers.clear();
    }
    
    // Добавление нового абонента
    void addSubscriber() {
        char name[100];
        char home[20];
        char work[20];
        char mobile[20];
        char info[200];
        
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        std::cout << "\n╔══════════════════════════════════════════════╗\n";
        std::cout << "║           ДОБАВЛЕНИЕ НОВОГО КОНТАКТА         ║\n";
        std::cout << "╚══════════════════════════════════════════════╝\n";
        
        inputString(name, 100, "Введите ФИО: ");
        std::cout << "Введите домашний телефон (или Enter для пропуска): ";
        std::cin.getline(home, 20);
        std::cout << "Введите рабочий телефон (или Enter для пропуска): ";
        std::cin.getline(work, 20);
        std::cout << "Введите мобильный телефон (или Enter для пропуска): ";
        std::cin.getline(mobile, 20);
        std::cout << "Введите дополнительную информацию (или Enter для пропуска): ";
        std::cin.getline(info, 200);
        
        Subscriber newSubscriber(name, 
                                (strlen(home) > 0 ? home : ""),
                                (strlen(work) > 0 ? work : ""),
                                (strlen(mobile) > 0 ? mobile : ""),
                                (strlen(info) > 0 ? info : ""));
        
        subscribers.push_back(newSubscriber);
        std::cout << "\n✓ Контакт успешно добавлен!\n";
    }
    
    // Удаление абонента по ФИО
    void deleteSubscriber() {
        char name[100];
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        std::cout << "\nВведите ФИО контакта для удаления: ";
        std::cin.getline(name, 100);
        
        auto it = std::remove_if(subscribers.begin(), subscribers.end(),
            [name](const Subscriber& s) {
                return strcmp(s.getFullName(), name) == 0;
            });
        
        if (it != subscribers.end()) {
            subscribers.erase(it, subscribers.end());
            std::cout << "\n✓ Контакт успешно удален!\n";
        } else {
            std::cout << "\n✗ Контакт с ФИО \"" << name << "\" не найден!\n";
        }
    }
    
    // Поиск абонента по ФИО
    void searchSubscriber() const {
        char name[100];
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        std::cout << "\nВведите ФИО для поиска: ";
        std::cin.getline(name, 100);
        
        bool found = false;
        for (const auto& subscriber : subscribers) {
            if (strcmp(subscriber.getFullName(), name) == 0) {
                subscriber.display();
                found = true;
                break;
            }
        }
        
        if (!found) {
            std::cout << "\n✗ Контакт с ФИО \"" << name << "\" не найден!\n";
        }
    }
    
    // Показать всех абонентов
    void showAllSubscribers() const {
        if (subscribers.empty()) {
            std::cout << "\nТелефонная книга пуста!\n";
            return;
        }
        
        std::cout << "\n╔══════════════════════════════════════════════════════════════╗\n";
        std::cout << "║                    ВСЕ КОНТАКТЫ (" << subscribers.size() << ")               ║\n";
        std::cout << "╠══════════════════════════════════════════════════════════════╣\n";
        
        for (size_t i = 0; i < subscribers.size(); ++i) {
            std::cout << "║ " << std::setw(3) << i + 1 << ". " 
                      << std::setw(40) << std::left << subscribers[i].getFullName()
                      << " Тел: " << std::setw(15) 
                      << (subscribers[i].getMobilePhone() && strlen(subscribers[i].getMobilePhone()) > 0 ? 
                          subscribers[i].getMobilePhone() : "не указан") << " ║\n";
        }
        std::cout << "╚══════════════════════════════════════════════════════════════╝\n";
    }
    
    // Сохранение в файл
    void saveToFile() const {
        std::ofstream file("phonebook.txt");
        
        if (!file.is_open()) {
            std::cerr << "\n✗ Ошибка открытия файла для записи!\n";
            return;
        }
        
        file << subscribers.size() << "\n";
        for (const auto& subscriber : subscribers) {
            subscriber.saveToFile(file);
        }
        
        file.close();
        std::cout << "\n✓ Данные успешно сохранены в файл phonebook.txt\n";
    }
    
    // Загрузка из файла
    void loadFromFile() {
        std::ifstream file("phonebook.txt");
        
        if (!file.is_open()) {
            std::cerr << "\n✗ Файл phonebook.txt не найден!\n";
            return;
        }
        
        int count;
        file >> count;
        file.ignore(); // Пропускаем перевод строки
        
        subscribers.clear();
        
        for (int i = 0; i < count; ++i) {
            Subscriber subscriber;
            subscriber.loadFromFile(file);
            subscribers.push_back(subscriber);
        }
        
        file.close();
        std::cout << "\n✓ Данные успешно загружены из файла phonebook.txt\n";
        std::cout << "  Загружено контактов: " << count << "\n";
    }
    
    // Получение количества контактов
    inline size_t getCount() const { return subscribers.size(); }
};

// Функция для отображения меню
void displayMenu() {
    std::cout << "\n╔══════════════════════════════════════════════╗\n";
    std::cout << "║            ТЕЛЕФОННАЯ КНИГА v1.0            ║\n";
    std::cout << "╠══════════════════════════════════════════════╣\n";
    std::cout << "║ 1. Добавить новый контакт                   ║\n";
    std::cout << "║ 2. Удалить контакт                          ║\n";
    std::cout << "║ 3. Найти контакт по ФИО                     ║\n";
    std::cout << "║ 4. Показать все контакты                    ║\n";
    std::cout << "║ 5. Сохранить в файл                         ║\n";
    std::cout << "║ 6. Загрузить из файла                       ║\n";
    std::cout << "║ 7. Статистика                               ║\n";
    std::cout << "║ 0. Выход                                    ║\n";
    std::cout << "╚══════════════════════════════════════════════╝\n";
    std::cout << "Выберите действие: ";
}

int main() {
    // Установка локализации для поддержки кириллицы
    setlocale(LC_ALL, "ru_RU.UTF-8");
    
    PhoneBook phoneBook;
    int choice;
    
    std::cout << "Добро пожаловать в телефонную книгу!\n";
    
    do {
        displayMenu();
        std::cin >> choice;
        
        switch (choice) {
            case 1:
                phoneBook.addSubscriber();
                break;
            case 2:
                phoneBook.deleteSubscriber();
                break;
            case 3:
                phoneBook.searchSubscriber();
                break;
            case 4:
                phoneBook.showAllSubscribers();
                break;
            case 5:
                phoneBook.saveToFile();
                break;
            case 6:
                phoneBook.loadFromFile();
                break;
            case 7:
                std::cout << "\n╔══════════════════════════════════════════════╗\n";
                std::cout << "║                СТАТИСТИКА                   ║\n";
                std::cout << "╠══════════════════════════════════════════════╣\n";
                std::cout << "║ Всего контактов: " << std::setw(25) 
                          << phoneBook.getCount() << " ║\n";
                std::cout << "╚══════════════════════════════════════════════╝\n";
                break;
            case 0:
                std::cout << "\nСпасибо за использование телефонной книги!\n";
                break;
            default:
                std::cout << "\n✗ Неверный выбор! Попробуйте снова.\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while (choice != 0);
    
    return 0;
}
