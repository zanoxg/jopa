#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <iomanip>

namespace fs = std::filesystem;

// Функция для проверки, содержится ли слово в файле
bool findWordInFile(const fs::path& filePath, const std::string& searchWord, 
                    std::vector<std::pair<fs::path, int>>& results) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        return false;
    }
    
    std::string line;
    int totalCount = 0;
    std::string lowerSearchWord = searchWord;
    
    // Преобразуем искомое слово в нижний регистр
    std::transform(lowerSearchWord.begin(), lowerSearchWord.end(), 
                   lowerSearchWord.begin(), ::tolower);
    
    while (std::getline(file, line)) {
        std::string lowerLine = line;
        // Преобразуем строку в нижний регистр для регистронезависимого поиска
        std::transform(lowerLine.begin(), lowerLine.end(), 
                       lowerLine.begin(), ::tolower);
        
        size_t pos = 0;
        while ((pos = lowerLine.find(lowerSearchWord, pos)) != std::string::npos) {
            totalCount++;
            pos += lowerSearchWord.length();
        }
    }
    
    file.close();
    
    if (totalCount > 0) {
        results.emplace_back(filePath, totalCount);
        return true;
    }
    
    return false;
}

// Функция для поиска слова во всех файлах директории
void searchWordInDirectory(const fs::path& directory, const std::string& searchWord,
                          std::vector<std::pair<fs::path, int>>& results) {
    try {
        // Рекурсивно проходим по всем файлам и подпапкам
        for (const auto& entry : fs::recursive_directory_iterator(directory)) {
            if (entry.is_regular_file()) {
                findWordInFile(entry.path(), searchWord, results);
            }
        }
    }
    catch (const fs::filesystem_error& e) {
        std::cerr << "Ошибка доступа к файловой системе: " << e.what() << std::endl;
    }
}

// Функция для вывода отчета
void generateReport(const std::vector<std::pair<fs::path, int>>& results,
                   const fs::path& directory, const std::string& searchWord) {
    std::cout << "\n========== ОТЧЕТ О ПОИСКЕ ==========\n";
    std::cout << "Искомое слово: \"" << searchWord << "\"\n";
    std::cout << "Поиск в папке: " << directory << "\n";
    std::cout << "-------------------------------------\n";
    
    if (results.empty()) {
        std::cout << "Слово не найдено в указанной папке.\n";
        return;
    }
    
    std::cout << "Найдено в " << results.size() << " файлах:\n";
    std::cout << std::left << std::setw(5) << "№" 
              << std::setw(50) << "Файл" 
              << std::setw(10) << "Совпадений" << "\n";
    std::cout << std::string(65, '-') << "\n";
    
    int totalMatches = 0;
    for (size_t i = 0; i < results.size(); ++i) {
        std::cout << std::left << std::setw(5) << i + 1
                  << std::setw(50) << results[i].first.filename().string()
                  << std::setw(10) << results[i].second << "\n";
        totalMatches += results[i].second;
    }
    
    std::cout << std::string(65, '-') << "\n";
    std::cout << "Всего совпадений: " << totalMatches << "\n";
    
    // Сохраняем отчет в файл
    std::ofstream reportFile("search_report.txt");
    if (reportFile.is_open()) {
        reportFile << "Отчет о поиске слова: \"" << searchWord << "\"\n";
        reportFile << "Путь поиска: " << directory << "\n\n";
        
        if (results.empty()) {
            reportFile << "Слово не найдено.\n";
        } else {
            reportFile << "Найдено в " << results.size() << " файлах:\n\n";
            
            for (size_t i = 0; i < results.size(); ++i) {
                reportFile << i + 1 << ". " << results[i].first.string() 
                          << " - " << results[i].second << " совпадений\n";
            }
            
            reportFile << "\nВсего совпадений: " << totalMatches << "\n";
        }
        
        reportFile.close();
        std::cout << "Отчет сохранен в файл: search_report.txt\n";
    }
}

int main() {
    // Установка локализации для поддержки кириллицы
    setlocale(LC_ALL, "ru_RU.UTF-8");
    
    std::string folderPath, searchWord;
    
    std::cout << "=== ПОИСК СЛОВА В ФАЙЛАХ ПАПКИ ===\n";
    
    // Ввод пути к папке
    std::cout << "Введите путь к папке: ";
    std::getline(std::cin, folderPath);
    
    // Проверка существования папки
    if (!fs::exists(folderPath) || !fs::is_directory(folderPath)) {
        std::cerr << "Ошибка: указанная папка не существует или недоступна!\n";
        return 1;
    }
    
    // Ввод искомого слова
    std::cout << "Введите искомое слово: ";
    std::getline(std::cin, searchWord);
    
    if (searchWord.empty()) {
        std::cerr << "Ошибка: искомое слово не может быть пустым!\n";
        return 1;
    }
    
    std::cout << "\nИдет поиск...\n";
    
    // Вектор для хранения результатов (путь к файлу, количество совпадений)
    std::vector<std::pair<fs::path, int>> searchResults;
    
    // Поиск слова в папке
    searchWordInDirectory(folderPath, searchWord, searchResults);
    
    // Генерация и вывод отчета
    generateReport(searchResults, folderPath, searchWord);
    
    return 0;
}
