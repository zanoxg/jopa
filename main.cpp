#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <sstream>

using namespace std;

class Directory {
private:
    struct Entry {
        string companyName;   // Название фирмы
        string owner;         // Владелец
        string phone;         // Телефон
        string address;       // Адрес
        string activity;      // Род деятельности
        
        // Метод для преобразования в строку для сохранения
        string toString() const {
            return companyName + "|" + owner + "|" + phone + "|" + address + "|" + activity;
        }
        
        // Метод для загрузки из строки
        static Entry fromString(const string& str) {
            Entry entry;
            stringstream ss(str);
            getline(ss, entry.companyName, '|');
            getline(ss, entry.owner, '|');
            getline(ss, entry.phone, '|');
            getline(ss, entry.address, '|');
            getline(ss, entry.activity);
            return entry;
        }
        
        // Вывод записи в консоль
        void display() const {
            cout << left << setw(25) << companyName 
                 << setw(20) << owner 
                 << setw(15) << phone 
                 << setw(30) << address 
                 << setw(20) << activity << endl;
        }
    };
    
    vector<Entry> entries;
    string filename;
    
    // Загрузка данных из файла
    void loadFromFile() {
        ifstream file(filename);
        if (!file.is_open()) return;
        
        entries.clear();
        string line;
        while (getline(file, line)) {
            if (!line.empty()) {
                entries.push_back(Entry::fromString(line));
            }
        }
        file.close();
    }
    
    // Сохранение данных в файл
    void saveToFile() const {
        ofstream file(filename);
        if (!file.is_open()) {
            cerr << "Ошибка: не удалось открыть файл для записи!" << endl;
            return;
        }
        
        for (const auto& entry : entries) {
            file << entry.toString() << endl;
        }
        file.close();
    }
    
public:
    Directory(const string& fname = "directory.txt") : filename(fname) {
        loadFromFile();
    }
    
    ~Directory() {
        saveToFile();
    }
    
    // Добавление новой записи
    void addEntry() {
        Entry newEntry;
        cin.ignore();
        
        cout << "Введите название фирмы: ";
        getline(cin, newEntry.companyName);
        
        cout << "Введите владельца: ";
        getline(cin, newEntry.owner);
        
        cout << "Введите телефон: ";
        getline(cin, newEntry.phone);
        
        cout << "Введите адрес: ";
        getline(cin, newEntry.address);
        
        cout << "Введите род деятельности: ";
        getline(cin, newEntry.activity);
        
        entries.push_back(newEntry);
        saveToFile();
        cout << "\nЗапись успешно добавлена!" << endl;
    }
    
    // Поиск по названию
    vector<Entry> searchByName(const string& name) const {
        vector<Entry> results;
        for (const auto& entry : entries) {
            if (toLowerCase(entry.companyName).find(toLowerCase(name)) != string::npos) {
                results.push_back(entry);
            }
        }
        return results;
    }
    
    // Поиск по владельцу
    vector<Entry> searchByOwner(const string& owner) const {
        vector<Entry> results;
        for (const auto& entry : entries) {
            if (toLowerCase(entry.owner).find(toLowerCase(owner)) != string::npos) {
                results.push_back(entry);
            }
        }
        return results;
    }
    
    // Поиск по телефону
    vector<Entry> searchByPhone(const string& phone) const {
        vector<Entry> results;
        for (const auto& entry : entries) {
            if (entry.phone.find(phone) != string::npos) {
                results.push_back(entry);
            }
        }
        return results;
    }
    
    // Поиск по роду деятельности
    vector<Entry> searchByActivity(const string& activity) const {
        vector<Entry> results;
        for (const auto& entry : entries) {
            if (toLowerCase(entry.activity).find(toLowerCase(activity)) != string::npos) {
                results.push_back(entry);
            }
        }
        return results;
    }
    
    // Показ всех записей
    void displayAll() const {
        if (entries.empty()) {
            cout << "\nСправочник пуст!" << endl;
            return;
        }
        
        cout << "\n" << string(115, '=') << endl;
        cout << left << setw(25) << "Название фирмы" 
             << setw(20) << "Владелец" 
             << setw(15) << "Телефон" 
             << setw(30) << "Адрес" 
             << setw(20) << "Род деятельности" << endl;
        cout << string(115, '-') << endl;
        
        for (const auto& entry : entries) {
            entry.display();
        }
        cout << string(115, '=') << endl;
        cout << "Всего записей: " << entries.size() << endl;
    }
    
    // Вывод результатов поиска
    void displayResults(const vector<Entry>& results, const string& searchType) const {
        if (results.empty()) {
            cout << "\nПо запросу \"" << searchType << "\" ничего не найдено!" << endl;
            return;
        }
        
        cout << "\nРезультаты поиска (" << results.size() << " записей):" << endl;
        cout << string(115, '-') << endl;
        cout << left << setw(25) << "Название фирмы" 
             << setw(20) << "Владелец" 
             << setw(15) << "Телефон" 
             << setw(30) << "Адрес" 
             << setw(20) << "Род деятельности" << endl;
        cout << string(115, '-') << endl;
        
        for (const auto& entry : results) {
            entry.display();
        }
    }
    
    // Получение количества записей
    size_t getSize() const {
        return entries.size();
    }
    
private:
    string toLowerCase(const string& str) const {
        string result = str;
        transform(result.begin(), result.end(), result.begin(), ::tolower);
        return result;
    }
};

// Функция отображения меню
void showDirectoryMenu() {
    cout << "\n" << string(50, '=') << endl;
    cout << "        СПРАВОЧНИК ФИРМ" << endl;
    cout << string(50, '=') << endl;
    cout << "1. Добавить новую запись" << endl;
    cout << "2. Поиск по названию" << endl;
    cout << "3. Поиск по владельцу" << endl;
    cout << "4. Поиск по телефону" << endl;
    cout << "5. Поиск по роду деятельности" << endl;
    cout << "6. Показать все записи" << endl;
    cout << "0. Выход" << endl;
    cout << string(50, '-') << endl;
    cout << "Выберите действие: ";
}

void runDirectory() {
    Directory dir;
    int choice;
    
    do {
        showDirectoryMenu();
        cin >> choice;
        
        switch (choice) {
            case 1:
                dir.addEntry();
                break;
            case 2: {
                string name;
                cin.ignore();
                cout << "Введите название фирмы: ";
                getline(cin, name);
                dir.displayResults(dir.searchByName(name), name);
                break;
            }
            case 3: {
                string owner;
                cin.ignore();
                cout << "Введите владельца: ";
                getline(cin, owner);
                dir.displayResults(dir.searchByOwner(owner), owner);
                break;
            }
            case 4: {
                string phone;
                cin.ignore();
                cout << "Введите телефон: ";
                getline(cin, phone);
                dir.displayResults(dir.searchByPhone(phone), phone);
                break;
            }
            case 5: {
                string activity;
                cin.ignore();
                cout << "Введите род деятельности: ";
                getline(cin, activity);
                dir.displayResults(dir.searchByActivity(activity), activity);
                break;
            }
            case 6:
                dir.displayAll();
                break;
            case 0:
                cout << "До свидания!" << endl;
                break;
            default:
                cout << "Неверный выбор!" << endl;
        }
    } while (choice != 0);
}

#include <iostream>
#include <atomic>

// ============ Реализация unique_ptr ============
template<typename T>
class MyUniquePtr {
private:
    T* ptr;
    
public:
    // Конструктор
    explicit MyUniquePtr(T* p = nullptr) : ptr(p) {}
    
    // Запрещаем копирование
    MyUniquePtr(const MyUniquePtr&) = delete;
    MyUniquePtr& operator=(const MyUniquePtr&) = delete;
    
    // Конструктор перемещения
    MyUniquePtr(MyUniquePtr&& other) noexcept : ptr(other.ptr) {
        other.ptr = nullptr;
    }
    
    // Оператор перемещения
    MyUniquePtr& operator=(MyUniquePtr&& other) noexcept {
        if (this != &other) {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }
    
    // Деструктор
    ~MyUniquePtr() {
        delete ptr;
    }
    
    // Операторы разыменования
    T& operator*() const {
        return *ptr;
    }
    
    T* operator->() const {
        return ptr;
    }
    
    // Получение сырого указателя
    T* get() const {
        return ptr;
    }
    
    // Освобождение управления
    T* release() {
        T* temp = ptr;
        ptr = nullptr;
        return temp;
    }
    
    // Сброс указателя
    void reset(T* p = nullptr) {
        delete ptr;
        ptr = p;
    }
    
    // Проверка на наличие указателя
    explicit operator bool() const {
        return ptr != nullptr;
    }
};

// ============ Реализация shared_ptr ============
template<typename T>
class MySharedPtr {
private:
    T* ptr;
    std::atomic<int>* refCount;
    
    void release() {
        if (refCount) {
            if (--(*refCount) == 0) {
                delete ptr;
                delete refCount;
            }
            ptr = nullptr;
            refCount = nullptr;
        }
    }
    
public:
    // Конструктор
    explicit MySharedPtr(T* p = nullptr) : ptr(p), refCount(nullptr) {
        if (ptr) {
            refCount = new std::atomic<int>(1);
        }
    }
    
    // Конструктор копирования
    MySharedPtr(const MySharedPtr& other) : ptr(other.ptr), refCount(other.refCount) {
        if (refCount) {
            (*refCount)++;
        }
    }
    
    // Оператор присваивания
    MySharedPtr& operator=(const MySharedPtr& other) {
        if (this != &other) {
            release();
            ptr = other.ptr;
            refCount = other.refCount;
            if (refCount) {
                (*refCount)++;
            }
        }
        return *this;
    }
    
    // Конструктор перемещения
    MySharedPtr(MySharedPtr&& other) noexcept : ptr(other.ptr), refCount(other.refCount) {
        other.ptr = nullptr;
        other.refCount = nullptr;
    }
    
    // Оператор перемещения
    MySharedPtr& operator=(MySharedPtr&& other) noexcept {
        if (this != &other) {
            release();
            ptr = other.ptr;
            refCount = other.refCount;
            other.ptr = nullptr;
            other.refCount = nullptr;
        }
        return *this;
    }
    
    // Деструктор
    ~MySharedPtr() {
        release();
    }
    
    // Операторы разыменования
    T& operator*() const {
        return *ptr;
    }
    
    T* operator->() const {
        return ptr;
    }
    
    // Получение сырого указателя
    T* get() const {
        return ptr;
    }
    
    // Количество ссылок
    int use_count() const {
        return refCount ? refCount->load() : 0;
    }
    
    // Проверка на наличие указателя
    explicit operator bool() const {
        return ptr != nullptr;
    }
    
    // Сброс указателя
    void reset(T* p = nullptr) {
        release();
        ptr = p;
        if (ptr) {
            refCount = new std::atomic<int>(1);
        } else {
            refCount = nullptr;
        }
    }
};

// Тестовый класс для демонстрации
class TestClass {
private:
    string name;
    int value;
    
public:
    TestClass(const string& n, int v) : name(n), value(v) {
        cout << "Создан объект TestClass: " << name << " (значение: " << value << ")" << endl;
    }
    
    ~TestClass() {
        cout << "Уничтожен объект TestClass: " << name << endl;
    }
    
    void display() const {
        cout << "Объект: " << name << ", значение: " << value << endl;
    }
    
    void setValue(int v) {
        value = v;
    }
};

// Тестирование умных указателей
void testSmartPointers() {
    cout << "\n========== ТЕСТИРОВАНИЕ UNIQUE_PTR ==========" << endl;
    
    // Создание и использование MyUniquePtr
    MyUniquePtr<TestClass> ptr1(new TestClass("Объект1", 100));
    ptr1->display();
    
    // Перемещение
    MyUniquePtr<TestClass> ptr2 = std::move(ptr1);
    if (!ptr1) {
        cout << "ptr1 теперь пуст" << endl;
    }
    ptr2->display();
    
    // Сброс и освобождение
    ptr2.reset(new TestClass("Объект2", 200));
    ptr2->display();
    
    TestClass* rawPtr = ptr2.release();
    cout << "Освобожденный указатель: ";
    rawPtr->display();
    delete rawPtr;
    
    cout << "\n========== ТЕСТИРОВАНИЕ SHARED_PTR ==========" << endl;
    
    // Создание и использование MySharedPtr
    MySharedPtr<TestClass> sp1(new TestClass("SharedObj1", 1000));
    cout << "sp1 count: " << sp1.use_count() << endl;
    
    {
        MySharedPtr<TestClass> sp2 = sp1;
        cout << "sp1 count после копирования: " << sp1.use_count() << endl;
        cout << "sp2 count: " << sp2.use_count() << endl;
        
        MySharedPtr<TestClass> sp3 = sp2;
        cout << "sp1 count после второго копирования: " << sp1.use_count() << endl;
        
        sp3->display();
    }
    
    cout << "sp1 count после выхода из области видимости: " << sp1.use_count() << endl;
    sp1->display();
    
    // Сброс
    sp1.reset(new TestClass("SharedObj2", 2000));
    cout << "После сброса, sp1 count: " << sp1.use_count() << endl;
    sp1->display();
}

#include <fstream>
#include <map>
#include <cctype>
#include <algorithm>

class FrequencyDictionary {
private:
    map<string, int> wordFrequency;
    int totalWords;
    
    // Очистка слова от знаков препинания и приведение к нижнему регистру
    string cleanWord(const string& word) {
        string result;
        for (char c : word) {
            if (isalnum(c) || c == '-' || c == '\'') {
                result += tolower(c);
            }
        }
        return result;
    }
    
    // Разбиение текста на слова
    void processText(const string& text) {
        stringstream ss(text);
        string word;
        
        while (ss >> word) {
            string cleaned = cleanWord(word);
            if (!cleaned.empty() && isalpha(cleaned[0])) {
                wordFrequency[cleaned]++;
                totalWords++;
            }
        }
    }
    
public:
    FrequencyDictionary() : totalWords(0) {}
    
    // Чтение текста из файла
    bool loadFromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Ошибка: не удалось открыть файл " << filename << endl;
            return false;
        }
        
        stringstream buffer;
        buffer << file.rdbuf();
        file.close();
        
        processText(buffer.str());
        return true;
    }
    
    // Вывод информации обо всех словах
    void displayAllWords() const {
        if (wordFrequency.empty()) {
            cout << "Словарь пуст!" << endl;
            return;
        }
        
        cout << "\n" << string(60, '=') << endl;
        cout << "ЧАСТОТНЫЙ СЛОВАРЬ" << endl;
        cout << string(60, '=') << endl;
        cout << left << setw(25) << "Слово" 
             << right << setw(15) << "Частота" 
             << setw(20) << "Частота (%)" << endl;
        cout << string(60, '-') << endl;
        
        for (const auto& pair : wordFrequency) {
            double percentage = (static_cast<double>(pair.second) / totalWords) * 100;
            cout << left << setw(25) << pair.first 
                 << right << setw(15) << pair.second
                 << setw(19) << fixed << setprecision(2) << percentage << "%" << endl;
        }
        cout << string(60, '-') << endl;
        cout << "Всего уникальных слов: " << wordFrequency.size() << endl;
        cout << "Всего слов в тексте: " << totalWords << endl;
    }
    
    // Вывод наиболее часто встречающегося слова
    void displayMostFrequent() const {
        if (wordFrequency.empty()) {
            cout << "Словарь пуст!" << endl;
            return;
        }
        
        auto maxElement = max_element(wordFrequency.begin(), wordFrequency.end(),
            [](const pair<string, int>& a, const pair<string, int>& b) {
                return a.second < b.second;
            });
        
        cout << "\n=== НАИБОЛЕЕ ЧАСТО ВСТРЕЧАЮЩЕЕСЯ СЛОВО ===" << endl;
        cout << "Слово: \"" << maxElement->first << "\"" << endl;
        cout << "Частота: " << maxElement->second << " раз" << endl;
        
        double percentage = (static_cast<double>(maxElement->second) / totalWords) * 100;
        cout << "Частота: " << fixed << setprecision(2) << percentage << "% от всех слов" << endl;
        
        // Поиск всех слов с максимальной частотой (если их несколько)
        auto range = equal_range(wordFrequency.begin(), wordFrequency.end(), 
            maxElement->second,
            [](const pair<string, int>& a, int b) { return a.second < b; });
        
        int count = distance(range.first, range.second);
        if (count > 1) {
            cout << "\nДругие слова с такой же частотой:" << endl;
            for (auto it = range.first; it != range.second; ++it) {
                if (it->first != maxElement->first) {
                    cout << " - \"" << it->first << "\"" << endl;
                }
            }
        }
    }
    
    // Сохранение результата в файл
    bool saveToFile(const string& filename) const {
        ofstream file(filename);
        if (!file.is_open()) {
            cerr << "Ошибка: не удалось создать файл " << filename << endl;
            return false;
        }
        
        file << "Частотный словарь\n";
        file << string(50, '=') << "\n";
        file << left << setw(25) << "Слово" 
             << right << setw(15) << "Частота" << "\n";
        file << string(50, '-') << "\n";
        
        for (const auto& pair : wordFrequency) {
            file << left << setw(25) << pair.first 
                 << right << setw(15) << pair.second << "\n";
        }
        
        file << string(50, '-') << "\n";
        file << "Всего уникальных слов: " << wordFrequency.size() << "\n";
        file << "Всего слов в тексте: " << totalWords << "\n";
        
        file.close();
        return true;
    }
    
    // Получение статистики
    void getStatistics() const {
        if (wordFrequency.empty()) return;
        
        int minFreq = min_element(wordFrequency.begin(), wordFrequency.end(),
            [](const auto& a, const auto& b) { return a.second < b.second; })->second;
        
        int maxFreq = max_element(wordFrequency.begin(), wordFrequency.end(),
            [](const auto& a, const auto& b) { return a.second < b.second; })->second;
        
        double avgFreq = static_cast<double>(totalWords) / wordFrequency.size();
        
        cout << "\n=== СТАТИСТИКА СЛОВАРЯ ===" << endl;
        cout << "Минимальная частота слова: " << minFreq << endl;
        cout << "Максимальная частота слова: " << maxFreq << endl;
        cout << "Средняя частота слова: " << fixed << setprecision(2) << avgFreq << endl;
    }
};

// Создание тестового файла для демонстрации
void createTestFile() {
    ofstream file("test_text.txt");
    if (file.is_open()) {
        file << "Lorem ipsum dolor sit amet, consectetur adipiscing elit. "
             << "Sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. "
             << "Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris. "
             << "Duis aute irure dolor in reprehenderit in voluptate velit esse cillum. "
             << "Lorem ipsum dolor sit amet, consectetur adipiscing elit. "
             << "Sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.";
        file.close();
        cout << "Создан тестовый файл test_text.txt" << endl;
    }
}

void runFrequencyDictionary() {
    cout << "\n========== ЧАСТОТНЫЙ СЛОВАРЬ ==========" << endl;
    
    // Создаем тестовый файл
    createTestFile();
    
    FrequencyDictionary dict;
    
    // Загрузка из файла
    if (dict.loadFromFile("test_text.txt")) {
        // Вывод всех слов
        dict.displayAllWords();
        
        // Вывод наиболее часто встречающегося слова
        dict.displayMostFrequent();
        
        // Вывод статистики
        dict.getStatistics();
        
        // Сохранение результата в файл
        if (dict.saveToFile("frequency_result.txt")) {
            cout << "\nРезультат сохранен в файл frequency_result.txt" << endl;
        }
    }
}

int main() {
    // Задание 1: Справочник
    runDirectory();
    
    // Задание 2: Умные указатели
    testSmartPointers();
    
    // Задание 3: Частотный словарь
    runFrequencyDictionary();
    
    return 0;
}
