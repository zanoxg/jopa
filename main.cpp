#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

// ============================
// ЗАДАНИЕ 1: Удаление последней строки из файла
// ============================

bool removeLastLine(const string& inputFile, const string& outputFile) {
    ifstream fin(inputFile);
    
    // Проверка открытия входного файла
    if (!fin.is_open()) {
        cerr << "Ошибка: не удалось открыть файл " << inputFile << endl;
        return false;
    }
    
    // Читаем все строки файла в вектор
    vector<string> lines;
    string line;
    
    while (getline(fin, line)) {
        lines.push_back(line);
    }
    fin.close();
    
    // Проверяем, есть ли строки в файле
    if (lines.empty()) {
        cout << "Файл " << inputFile << " пуст.\n";
        
        // Создаем пустой выходной файл
        ofstream fout(outputFile);
        if (fout.is_open()) {
            fout.close();
        }
        return true;
    }
    
    // Удаляем последнюю строку
    cout << "Удалена последняя строка: \"" << lines.back() << "\"\n";
    lines.pop_back();
    
    // Записываем результат в выходной файл
    ofstream fout(outputFile);
    if (!fout.is_open()) {
        cerr << "Ошибка: не удалось создать файл " << outputFile << endl;
        return false;
    }
    
    for (size_t i = 0; i < lines.size(); i++) {
        fout << lines[i];
        // Не добавляем перевод строки после последней строки
        if (i != lines.size() - 1) {
            fout << "\n";
        }
    }
    fout.close();
    
    cout << "Результат записан в файл " << outputFile << endl;
    cout << "Осталось строк: " << lines.size() << endl;
    
    return true;
}

void createTestFileForTask1() {
    ofstream fout("input_task1.txt");
    
    if (fout.is_open()) {
        fout << "Первая строка файла\n";
        fout << "Вторая строка файла\n";
        fout << "Третья строка файла\n";
        fout << "Четвертая строка файла\n";
        fout << "Пятая строка (последняя, будет удалена)\n";
        fout.close();
        cout << "Создан тестовый файл: input_task1.txt\n";
    }
}

void displayFileContent(const string& filename, const string& title) {
    ifstream fin(filename);
    
    if (!fin.is_open()) {
        cout << "Файл " << filename << " не найден или не может быть открыт.\n";
        return;
    }
    
    cout << "\n=== " << title << " ===\n";
    string line;
    int lineNumber = 1;
    
    while (getline(fin, line)) {
        cout << lineNumber++ << ": " << line << endl;
    }
    
    fin.close();
}

void task1() {
    cout << "\n=== ЗАДАНИЕ 1: УДАЛЕНИЕ ПОСЛЕДНЕЙ СТРОКИ ИЗ ФАЙЛА ===\n";
    
    int choice;
    cout << "1. Использовать тестовый файл\n";
    cout << "2. Ввести имена файлов вручную\n";
    cout << "Выберите вариант: ";
    cin >> choice;
    cin.ignore(); // Очищаем буфер ввода
    
    string inputFile, outputFile;
    
    if (choice == 1) {
        createTestFileForTask1();
        inputFile = "input_task1.txt";
        outputFile = "output_task1.txt";
        
        cout << "\nСодержимое исходного файла:\n";
        displayFileContent(inputFile, "ИСХОДНЫЙ ФАЙЛ");
    } else {
        cout << "Введите имя исходного файла: ";
        getline(cin, inputFile);
        cout << "Введите имя выходного файла: ";
        getline(cin, outputFile);
    }
    
    if (removeLastLine(inputFile, outputFile)) {
        cout << "\nСодержимое полученного файла:\n";
        displayFileContent(outputFile, "ФАЙЛ ПОСЛЕ УДАЛЕНИЯ ПОСЛЕДНЕЙ СТРОКИ");
    } else {
        cout << "Ошибка при обработке файлов!\n";
    }
}

// ============================
// ЗАДАНИЕ 2: Поиск длины самой длинной строки в файле
// ============================

struct LineInfo {
    int number;
    string content;
    int length;
};

bool findLongestLine(const string& filename) {
    ifstream fin(filename);
    
    // Проверка открытия файла
    if (!fin.is_open()) {
        cerr << "Ошибка: не удалось открыть файл " << filename << endl;
        return false;
    }
    
    // Переменные для поиска самой длинной строки
    vector<LineInfo> longestLines;
    string line;
    int lineNumber = 0;
    int maxLength = -1;
    
    // Читаем файл построчно
    while (getline(fin, line)) {
        lineNumber++;
        int currentLength = line.length();
        
        if (currentLength > maxLength) {
            // Нашли строку длиннее всех предыдущих
            maxLength = currentLength;
            longestLines.clear(); // Очищаем список самых длинных строк
            longestLines.push_back({lineNumber, line, currentLength});
        } else if (currentLength == maxLength && maxLength > -1) {
            // Нашли строку такой же длины
            longestLines.push_back({lineNumber, line, currentLength});
        }
    }
    fin.close();
    
    // Проверяем, был ли файл пустым
    if (lineNumber == 0) {
        cout << "Файл " << filename << " пуст.\n";
        return true;
    }
    
    // Выводим результаты
    cout << "\n=== РЕЗУЛЬТАТЫ АНАЛИЗА ФАЙЛА " << filename << " ===\n";
    cout << "Всего строк в файле: " << lineNumber << endl;
    cout << "Длина самой длинной строки: " << maxLength << " символов\n";
    cout << "Количество строк максимальной длины: " << longestLines.size() << endl;
    
    if (longestLines.size() == 1) {
        cout << "\nСамая длинная строка:\n";
        cout << "Строка " << longestLines[0].number << ": \"" 
             << longestLines[0].content << "\"\n";
        cout << "Длина: " << longestLines[0].length << " символов\n";
    } else {
        cout << "\nСамые длинные строки (одинаковой длины):\n";
        for (const auto& lineInfo : longestLines) {
            cout << "Строка " << lineInfo.number << ": \"" 
                 << lineInfo.content << "\" (" 
                 << lineInfo.length << " символов)\n";
        }
    }
    
    // Дополнительная статистика
    cout << "\n=== ДОПОЛНИТЕЛЬНАЯ СТАТИСТИКА ===\n";
    
    // Переоткрываем файл для подсчета общей статистики
    fin.open(filename);
    lineNumber = 0;
    int totalChars = 0;
    int shortestLineLength = numeric_limits<int>::max();
    vector<LineInfo> shortestLines;
    
    while (getline(fin, line)) {
        lineNumber++;
        int currentLength = line.length();
        totalChars += currentLength;
        
        if (currentLength < shortestLineLength) {
            shortestLineLength = currentLength;
            shortestLines.clear();
            shortestLines.push_back({lineNumber, line, currentLength});
        } else if (currentLength == shortestLineLength) {
            shortestLines.push_back({lineNumber, line, currentLength});
        }
    }
    fin.close();
    
    double averageLength = static_cast<double>(totalChars) / lineNumber;
    
    cout << "Общее количество символов: " << totalChars << endl;
    cout << "Средняя длина строки: " << averageLength << " символов\n";
    cout << "Длина самой короткой строки: " << shortestLineLength << " символов\n";
    
    return true;
}

void createTestFileForTask2() {
    ofstream fout("input_task2.txt");
    
    if (fout.is_open()) {
        fout << "Короткая строка\n";
        fout << "Более длинная строка\n";
        fout << "Самая длинная строка в этом файле, действительно очень длинная\n";
        fout << "Еще одна строка\n";
        fout << "Другая очень длинная строка, почти такая же как самая длинная\n";
        fout << "Коротко\n";
        fout << "Строка средней длины\n";
        fout << "Самая длинная строка в этом файле, действительно очень длинная\n";
        fout.close();
        cout << "Создан тестовый файл: input_task2.txt\n";
    }
}

void task2() {
    cout << "\n=== ЗАДАНИЕ 2: ПОИСК ДЛИНЫ САМОЙ ДЛИННОЙ СТРОКИ ===\n";
    
    int choice;
    cout << "1. Использовать тестовый файл\n";
    cout << "2. Ввести имя файла вручную\n";
    cout << "Выберите вариант: ";
    cin >> choice;
    cin.ignore(); // Очищаем буфер ввода
    
    string filename;
    
    if (choice == 1) {
        createTestFileForTask2();
        filename = "input_task2.txt";
        
        cout << "\nСодержимое файла для анализа:\n";
        displayFileContent(filename, "ФАЙЛ ДЛЯ АНАЛИЗА");
    } else {
        cout << "Введите имя файла для анализа: ";
        getline(cin, filename);
    }
    
    if (!findLongestLine(filename)) {
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
        cout << "1. Задание 1: Удаление последней строки из файла\n";
        cout << "2. Задание 2: Поиск длины самой длинной строки\n";
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
                
                // Создаем тестовые файлы
                createTestFileForTask1();
                createTestFileForTask2();
                
                cout << "\n--- Задание 1 ---\n";
                cout << "\nСодержимое исходного файла:\n";
                displayFileContent("input_task1.txt", "ИСХОДНЫЙ ФАЙЛ (ЗАДАНИЕ 1)");
                removeLastLine("input_task1.txt", "output_task1.txt");
                cout << "\nСодержимое полученного файла:\n";
                displayFileContent("output_task1.txt", "ФАЙЛ ПОСЛЕ УДАЛЕНИЯ ПОСЛЕДНЕЙ СТРОКИ");
                
                cout << "\n--- Задание 2 ---\n";
                cout << "\nСодержимое файла для анализа:\n";
                displayFileContent("input_task2.txt", "ФАЙЛ ДЛЯ АНАЛИЗА (ЗАДАНИЕ 2)");
                findLongestLine("input_task2.txt");
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
