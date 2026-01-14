#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>

namespace fs = std::filesystem;

class WordSearcher {
private:
    std::string searchWord;
    std::vector<std::pair<std::string, int>> results;
    int totalMatches;

    // Функция для поиска слова в одном файле
    int searchInFile(const fs::path& filePath) {
        int matches = 0;
        
        try {
            std::ifstream file(filePath, std::ios::in);
            if (!file.is_open()) {
                std::cerr << "Не удалось открыть файл: " << filePath << std::endl;
                return 0;
            }

            std::string line;
            while (std::getline(file, line)) {
                // Простой поиск слова (регистрозависимый)
                size_t pos = 0;
                while ((pos = line.find(searchWord, pos)) != std::string::npos) {
                    matches++;
                    pos += searchWord.length();
                }
            }
            file.close();
        } catch (const std::exception& e) {
            std::cerr << "Ошибка при чтении файла " << filePath << ": " << e.what() << std::endl;
        }
        
        return matches;
    }

    // Рекурсивный обход директорий
    void traverseDirectory(const fs::path& directory) {
        try {
            for (const auto& entry : fs::recursive_directory_iterator(directory)) {
                if (entry.is_regular_file()) {
                    // Можно добавить фильтр по расширению файлов
                    std::string extension = entry.path().extension().string();
                    
                    // Игнорируем некоторые бинарные файлы (опционально)
                    std::vector<std::string> textExtensions = {
                        ".txt", ".cpp", ".h", ".hpp", ".c", ".py", 
                        ".java", ".js", ".html", ".css", ".xml", ".json"
                    };
                    
                    // Если хотите искать во всех файлах, уберите эту проверку
                    bool isTextFile = std::find(textExtensions.begin(), 
                                               textExtensions.end(), 
                                               extension) != textExtensions.end();
                    
                    if (isTextFile || textExtensions.empty()) {
                        int matches = searchInFile(entry.path());
                        if (matches > 0) {
                            results.emplace_back(entry.path().string(), matches);
                            totalMatches += matches;
                        }
                    }
                }
            }
        } catch (const fs::filesystem_error& e) {
            std::cerr << "Ошибка доступа к директории: " << e.what() << std::endl;
        }
    }

public:
    WordSearcher() : totalMatches(0) {}

    // Основная функция поиска
    void search(const std::string& directoryPath, const std::string& word) {
        searchWord = word;
        totalMatches = 0;
        results.clear();

        fs::path dir(directoryPath);
        
        if (!fs::exists(dir)) {
            std::cerr << "Директория не существует: " << directoryPath << std::endl;
            return;
        }

        if (!fs::is_directory(dir)) {
            std::cerr << "Указанный путь не является директорией: " << directoryPath << std::endl;
            return;
        }

        std::cout << "Начинаю поиск слова \"" << word << "\" в директории: " 
                  << directoryPath << std::endl;
        
        traverseDirectory(dir);
    }

    // Генерация отчета
    void generateReport(const std::string& reportFileName = "search_report.txt") {
        std::ofstream report(reportFileName);
        
        if (!report.is_open()) {
            std::cerr << "Не удалось создать файл отчета: " << reportFileName << std::endl;
            return;
        }

        // Заголовок отчета
        report << "========================================\n";
        report << "ОТЧЕТ О ПОИСКЕ СЛОВА\n";
        report << "========================================\n";
        report << "Искомое слово: " << searchWord << "\n";
        report << "Общее количество совпадений: " << totalMatches << "\n";
        report << "Найдено в " << results.size() << " файлах\n";
        report << "========================================\n\n";

        if (results.empty()) {
            report << "Совпадений не найдено.\n";
        } else {
            report << "ДЕТАЛЬНЫЕ РЕЗУЛЬТАТЫ:\n";
            report << "========================================\n";
            
            for (size_t i = 0; i < results.size(); ++i) {
                report << std::setw(3) << (i + 1) << ". Файл: " << results[i].first << "\n";
                report << "    Совпадений: " << results[i].second << "\n";
                report << "----------------------------------------\n";
            }
        }

        report << "\nОтчет сгенерирован: " << __DATE__ << " " << __TIME__ << "\n";
        report.close();

        std::cout << "\nОтчет сохранен в файл: " << reportFileName << std::endl;
    }

    // Вывод результатов в консоль
    void printResults() const {
        std::cout << "\n========================================" << std::endl;
        std::cout << "РЕЗУЛЬТАТЫ ПОИСКА" << std::endl;
        std::cout << "========================================" << std::endl;
        std::cout << "Искомое слово: " << searchWord << std::endl;
        std::cout << "Общее количество совпадений: " << totalMatches << std::endl;
        std::cout << "Найдено в " << results.size() << " файлах" << std::endl;
        
        if (!results.empty()) {
            std::cout << "\nСписок файлов с совпадениями:\n";
            for (size_t i = 0; i < results.size(); ++i) {
                std::cout << i + 1 << ". " << results[i].first 
                         << " (совпадений: " << results[i].second << ")\n";
            }
        }
        std::cout << "========================================" << std::endl;
    }

    // Геттер для общего количества совпадений
    int getTotalMatches() const {
        return totalMatches;
    }

    // Геттер для результатов
    const std::vector<std::pair<std::string, int>>& getResults() const {
        return results;
    }
};

// Функция для ввода данных от пользователя
void getUserInput(std::string& directoryPath, std::string& searchWord) {
    std::cout << "Введите путь к папке для поиска: ";
    std::getline(std::cin, directoryPath);
    
    // Убираем кавычки, если они есть (удобно для копирования пути)
    if (!directoryPath.empty() && directoryPath.front() == '"' && directoryPath.back() == '"') {
        directoryPath = directoryPath.substr(1, directoryPath.length() - 2);
    }
    
    std::cout << "Введите слово для поиска: ";
    std::getline(std::cin, searchWord);
}

int main() {
    // Установка локализации для корректного отображения русских символов
    #ifdef _WIN32
        system("chcp 65001 > nul"); // UTF-8 в Windows
    #endif
    
    std::cout << "=== ПРОГРАММА ПОИСКА СЛОВ В ФАЙЛАХ ===\n" << std::endl;

    std::string directoryPath, searchWord;
    
    // Получаем ввод от пользователя
    getUserInput(directoryPath, searchWord);
    
    if (directoryPath.empty() || searchWord.empty()) {
        std::cerr << "Ошибка: путь к директории и искомое слово не могут быть пустыми." << std::endl;
        return 1;
    }
    
    // Создаем объект поисковика и выполняем поиск
    WordSearcher searcher;
    searcher.search(directoryPath, searchWord);
    
    // Выводим результаты в консоль
    searcher.printResults();
    
    // Генерируем отчет в файл
    std::string reportName = "search_report_" + searchWord + ".txt";
    searcher.generateReport(reportName);
    
    // Дополнительная информация
    if (searcher.getTotalMatches() == 0) {
        std::cout << "\nСовпадений не найдено." << std::endl;
    } else {
        std::cout << "\nПоиск завершен успешно." << std::endl;
    }
    
    return 0;
}
