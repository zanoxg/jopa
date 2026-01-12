#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <iomanip>

using namespace std;

// ============================
// ЗАДАНИЕ 1: Сравнение строк двух файлов
// ============================

bool compareFiles(const string& file1, const string& file2) {
    ifstream fin1(file1);
    ifstream fin2(file2);
    
    // Проверка открытия файлов
    if (!fin1.is_open()) {
        cerr << "Ошибка: не удалось открыть файл " << file1 << endl;
        return false;
    }
    
    if (!fin2.is_open()) {
        cerr << "Ошибка: не удалось открыть файл " << file2 << endl;
        fin1.close();
        return false;
    }
    
    string line1, line2;
    int lineNumber = 1;
    bool filesAreEqual = true;
    
    cout << "\n=== СРАВНЕНИЕ ФАЙЛОВ ===\n";
    cout << "Файл 1: " << file1 << endl;
    cout << "Файл 2: " << file2 << endl;
    cout << string(50, '=') << endl;
    
    // Построчное сравнение файлов
    while (getline(fin1, line1) || getline(fin2, line2)) {
        bool line1Exists = !fin1.eof() || !line1.empty();
        bool line2Exists = !fin2.eof() || !line2.empty();
        
        if (line1Exists && line2Exists) {
            if (line1 != line2) {
                cout << "\nСтрока " << lineNumber << " не совпадает:\n";
                cout << "Файл 1: \"" << line1 << "\"\n";
                cout << "Файл 2: \"" << line2 << "\"\n";
                filesAreEqual = false;
            }
        } else if (line1Exists && !line2Exists) {
            cout << "\nФайл 2 короче. Строка " << lineNumber << " есть только в файле 1:\n";
            cout << "Файл 1: \"" << line1 << "\"\n";
            filesAreEqual = false;
        } else if (!line1Exists && line2Exists) {
            cout << "\nФайл 1 короче. Строка " << lineNumber << " есть только в файле 2:\n";
            cout << "Файл 2: \"" << line2 << "\"\n";
            filesAreEqual = false;
        }
        
        // Очищаем строки для следующей итерации
        line1.clear();
        line2.clear();
        lineNumber++;
    }
    
    // Проверяем, не остались ли строки в каком-то файле
    if (getline(fin1, line1)) {
        cout << "\nФайл 2 короче. Оставшиеся строки в файле 1:\n";
        while (getline(fin1, line1)) {
            cout << "Строка " << lineNumber++ << ": \"" << line1 << "\"\n";
        }
        filesAreEqual = false;
    }
    
    if (getline(fin2, line2)) {
        cout << "\nФайл 1 короче. Оставшиеся строки в файле 2:\n";
        while (getline(fin2, line2)) {
            cout << "Строка " << lineNumber++ << ": \"" << line2 << "\"\n";
        }
        filesAreEqual = false;
    }
    
    if (filesAreEqual) {
        cout << "Файлы полностью идентичны!\n";
    } else {
        cout << "\n" << string(50, '=') << endl;
        cout << "Файлы не совпадают.\n";
    }
    
    fin1.close();
    fin2.close();
    return filesAreEqual;
}

void createTestFiles() {
    // Создаем тестовые файлы для демонстрации
    ofstream fout1("file1.txt");
    ofstream fout2("file2.txt");
    
    if (fout1.is_open()) {
        fout1 << "Первая строка файла 1\n";
        fout1 << "Вторая строка файла 1\n";
        fout1 << "Третья строка файла 1\n";
        fout1 << "Эта строка отличается\n";
        fout1 << "Пятая строка файла 1\n";
        fout1.close();
        cout << "Создан тестовый файл: file1.txt\n";
    }
    
    if (fout2.is_open()) {
        fout2 << "Первая строка файла 1\n";
        fout2 << "Вторая строка файла 1\n";
        fout2 << "Третья строка файла 1\n";
        fout2 << "А эта строка другая\n";
        fout2 << "Пятая строка файла 1\n";
        fout2 << "Шестая строка (только во втором файле)\n";
        fout2.close();
        cout << "Создан тестовый файл: file2.txt\n";
    }
}

void task1() {
    cout << "\n=== ЗАДАНИЕ 1: СРАВНЕНИЕ СТРОК ДВУХ ФАЙЛОВ ===\n";
    
    int choice;
    cout << "1. Использовать тестовые файлы\n";
    cout << "2. Ввести имена файлов вручную\n";
    cout << "Выберите вариант: ";
    cin >> choice;
    cin.ignore(); // Очищаем буфер ввода
    
    string file1, file2;
    
    if (choice == 1) {
        createTestFiles();
        file1 = "file1.txt";
        file2 = "file2.txt";
    } else {
        cout << "Введите имя первого файла: ";
        getline(cin, file1);
        cout << "Введите имя второго файла: ";
        getline(cin, file2);
    }
    
    compareFiles(file1, file2);
}

// ============================
// ЗАДАНИЕ 2: Статистика по файлу
// ============================

// Функция для проверки, является ли символ гласной буквой (русской или английской)
bool isVowel(char c) {
    c = tolower(c);
    // Английские гласные
    if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || 
        c == 'y') {
        return true;
    }
    // Русские гласные
    if (c == 'а' || c == 'е' || c == 'ё' || c == 'и' || c == 'о' || 
        c == 'у' || c == 'ы' || c == 'э' || c == 'ю' || c == 'я') {
        return true;
    }
    return false;
}

// Функция для проверки, является ли символ согласной буквой (русской или английской)
bool isConsonant(char c) {
    c = tolower(c);
    // Проверяем, является ли символ буквой
    if (!isalpha(c)) {
        return false;
    }
    // Если это не гласная, значит это согласная
    return !isVowel(c);
}

// Функция для проверки, является ли символ цифрой
bool isDigit(char c) {
    return isdigit(static_cast<unsigned char>(c));
}

// Функция для сбора статистики по файлу
bool analyzeFile(const string& inputFile, const string& outputFile) {
    ifstream fin(inputFile);
    ofstream fout(outputFile);
    
    // Проверка открытия файлов
    if (!fin.is_open()) {
        cerr << "Ошибка: не удалось открыть файл " << inputFile << endl;
        return false;
    }
    
    if (!fout.is_open()) {
        cerr << "Ошибка: не удалось создать файл " << outputFile << endl;
        fin.close();
        return false;
    }
    
    // Статистика
    int totalChars = 0;
    int totalLines = 0;
    int vowelsCount = 0;
    int consonantsCount = 0;
    int digitsCount = 0;
    
    string line;
    
    // Чтение файла построчно
    while (getline(fin, line)) {
        totalLines++;
        totalChars += line.length() + 1; // +1 для символа новой строки
        
        // Анализ символов в строке
        for (char c : line) {
            if (isVowel(c)) {
                vowelsCount++;
            } else if (isConsonant(c)) {
                consonantsCount++;
            } else if (isDigit(c)) {
                digitsCount++;
            }
        }
    }
    
    // Корректировка общего количества символов (последняя строка не имеет \n)
    if (totalLines > 0 && !fin.eof()) {
        totalChars--;
    }
    
    // Вывод статистики в консоль
    cout << "\n=== СТАТИСТИКА ПО ФАЙЛУ " << inputFile << " ===\n";
    cout << string(40, '-') << endl;
    cout << left << setw(25) << "Количество символов:" << totalChars << endl;
    cout << left << setw(25) << "Количество строк:" << totalLines << endl;
    cout << left << setw(25) << "Количество гласных букв:" << vowelsCount << endl;
    cout << left << setw(25) << "Количество согласных букв:" << consonantsCount << endl;
    cout << left << setw(25) << "Количество цифр:" << digitsCount << endl;
    
    // Запись статистики в выходной файл
    fout << "=== СТАТИСТИКА ПО ФАЙЛУ " << inputFile << " ===\n";
    fout << string(40, '-') << endl;
    fout << left << setw(25) << "Количество символов:" << totalChars << endl;
    fout << left << setw(25) << "Количество строк:" << totalLines << endl;
    fout << left << setw(25) << "Количество гласных букв:" << vowelsCount << endl;
    fout << left << setw(25) << "Количество согласных букв:" << consonantsCount << endl;
    fout << left << setw(25) << "Количество цифр:" << digitsCount << endl;
    fout << string(40, '-') << endl;
    
    // Дополнительная статистика
    int lettersCount = vowelsCount + consonantsCount;
    int otherChars = totalChars - lettersCount - digitsCount - totalLines + 1;
    
    fout << left << setw(25) << "Всего букв:" << lettersCount << endl;
    fout << left << setw(25) << "Других символов:" << otherChars << endl;
    
    cout << "\nСтатистика сохранена в файл: " << outputFile << endl;
    
    fin.close();
    fout.close();
    return true;
}

void createTestFileForAnalysis() {
    ofstream fout("text_for_analysis.txt");
    
    if (fout.is_open()) {
        fout << "Это тестовый файл для анализа.\n";
        fout << "Здесь содержится несколько строк текста.\n";
        fout << "В тексте есть цифры: 12345 и 67890.\n";
        fout << "А также английские слова: Hello World!\n";
        fout << "И русские слова: Привет Мир!\n";
        fout << "Последняя строка без точки в конце";
        fout.close();
        cout << "Создан тестовый файл: text_for_analysis.txt\n";
    }
}

void task2() {
    cout << "\n=== ЗАДАНИЕ 2: СТАТИСТИКА ПО ФАЙЛУ ===\n";
    
    int choice;
    cout << "1. Использовать тестовый файл\n";
    cout << "2. Ввести имя файла вручную\n";
    cout << "Выберите вариант: ";
    cin >> choice;
    cin.ignore(); // Очищаем буфер ввода
    
    string inputFile, outputFile;
    
    if (choice == 1) {
        createTestFileForAnalysis();
        inputFile = "text_for_analysis.txt";
        outputFile = "statistics.txt";
    } else {
        cout << "Введите имя анализируемого файла: ";
        getline(cin, inputFile);
        cout << "Введите имя файла для сохранения статистики: ";
        getline(cin, outputFile);
    }
    
    if (analyzeFile(inputFile, outputFile)) {
        cout << "Анализ завершен успешно!\n";
        
        // Показываем содержимое созданного файла со статистикой
        cout << "\nСодержимое файла со статистикой:\n";
        ifstream fin(outputFile);
        if (fin.is_open()) {
            string line;
            while (getline(fin, line)) {
                cout << line << endl;
            }
            fin.close();
        }
    } else {
        cout << "Ошибка при анализе файла!\n";
    }
}

// ============================
// Главное меню программы
// ============================
int main() {
    int mainChoice;
    
    do {
        cout << "\n=== ГЛАВНОЕ МЕНЮ ===\n";
        cout << "1. Задание 1: Сравнение строк двух файлов\n";
        cout << "2. Задание 2: Статистика по файлу\n";
        cout << "3. Выполнить оба задания (демо)\n";
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
            case 3:
                cout << "\n=== ВЫПОЛНЕНИЕ ОБОИХ ЗАДАНИЙ ===\n";
                createTestFiles();
                createTestFileForAnalysis();
                cout << "\n--- Задание 1 ---\n";
                compareFiles("file1.txt", "file2.txt");
                cout << "\n--- Задание 2 ---\n";
                analyzeFile("text_for_analysis.txt", "statistics.txt");
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
