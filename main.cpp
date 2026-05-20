#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <iomanip>
#include <memory>
#include <numeric>
#include <set>

using namespace std;

// Класс автомобиля
class Car {
private:
    string name;
    int year;
    double engineVolume;
    double price;

public:
    // Конструкторы
    Car() : name(""), year(0), engineVolume(0.0), price(0.0) {}
    
    Car(const string& n, int y, double ev, double p) 
        : name(n), year(y), engineVolume(ev), price(p) {}
    
    // Конструктор копирования
    Car(const Car& other) 
        : name(other.name), year(other.year), 
          engineVolume(other.engineVolume), price(other.price) {}
    
    // Геттеры
    string getName() const { return name; }
    int getYear() const { return year; }
    double getEngineVolume() const { return engineVolume; }
    double getPrice() const { return price; }
    
    // Сеттеры
    void setName(const string& n) { name = n; }
    void setYear(int y) { year = y; }
    void setEngineVolume(double ev) { engineVolume = ev; }
    void setPrice(double p) { price = p; }
    
    // Перегрузка оператора вывода
    friend ostream& operator<<(ostream& os, const Car& car) {
        os << left << setw(25) << car.name 
           << setw(10) << car.year 
           << setw(12) << fixed << setprecision(1) << car.engineVolume
           << setw(15) << fixed << setprecision(2) << car.price << " руб.";
        return os;
    }
    
    // Перегрузка оператора сравнения для поиска
    bool operator==(const Car& other) const {
        return name == other.name && year == other.year && 
               engineVolume == other.engineVolume && price == other.price;
    }
};

// Функторы для сравнения
struct CompareByName {
    bool operator()(const Car& a, const Car& b) const {
        return a.getName() < b.getName();
    }
};

struct CompareByYear {
    bool operator()(const Car& a, const Car& b) const {
        return a.getYear() < b.getYear();
    }
};

struct CompareByEngineVolume {
    bool operator()(const Car& a, const Car& b) const {
        return a.getEngineVolume() < b.getEngineVolume();
    }
};

struct CompareByPrice {
    bool operator()(const Car& a, const Car& b) const {
        return a.getPrice() < b.getPrice();
    }
};

// Функторы для поиска
struct FindByName {
    string name;
    FindByName(const string& n) : name(n) {}
    
    bool operator()(const Car& car) const {
        return car.getName() == name;
    }
};

struct FindByYear {
    int year;
    FindByYear(int y) : year(y) {}
    
    bool operator()(const Car& car) const {
        return car.getYear() == year;
    }
};

struct FindByEngineRange {
    double minVolume;
    double maxVolume;
    
    FindByEngineRange(double minVol, double maxVol) 
        : minVolume(minVol), maxVolume(maxVol) {}
    
    bool operator()(const Car& car) const {
        return car.getEngineVolume() >= minVolume && 
               car.getEngineVolume() <= maxVolume;
    }
};

struct FindByPriceRange {
    double minPrice;
    double maxPrice;
    
    FindByPriceRange(double minP, double maxP) 
        : minPrice(minP), maxPrice(maxP) {}
    
    bool operator()(const Car& car) const {
        return car.getPrice() >= minPrice && car.getPrice() <= maxPrice;
    }
};

struct FindByYearRange {
    int minYear;
    int maxYear;
    
    FindByYearRange(int minY, int maxY) 
        : minYear(minY), maxYear(maxY) {}
    
    bool operator()(const Car& car) const {
        return car.getYear() >= minYear && car.getYear() <= maxYear;
    }
};

// Функтор для отображения автомобиля
struct DisplayCar {
    void operator()(const Car& car) const {
        cout << car << endl;
    }
};

// Функтор для обновления цены
struct UpdatePrice {
    double percentage;
    
    UpdatePrice(double p) : percentage(p) {}
    
    void operator()(Car& car) const {
        double newPrice = car.getPrice() * (1 + percentage / 100.0);
        car.setPrice(newPrice);
    }
};

// Класс автосалона
class CarDealership {
private:
    vector<Car> cars;
    
public:
    // Добавление автомобиля
    void addCar(const Car& car) {
        cars.push_back(car);
        cout << "Автомобиль успешно добавлен!" << endl;
    }
    
    // Добавление автомобиля (перемещение)
    void addCar(Car&& car) {
        cars.push_back(move(car));
        cout << "Автомобиль успешно добавлен!" << endl;
    }
    
    // Удаление автомобиля по индексу
    bool removeCar(int index) {
        if (index >= 0 && index < cars.size()) {
            cars.erase(cars.begin() + index);
            cout << "Автомобиль успешно удален!" << endl;
            return true;
        }
        cout << "Ошибка: неверный индекс!" << endl;
        return false;
    }
    
    // Удаление автомобиля по имени
    bool removeCarByName(const string& name) {
        auto it = remove_if(cars.begin(), cars.end(), 
                           [&name](const Car& car) { 
                               return car.getName() == name; 
                           });
        
        if (it != cars.end()) {
            cars.erase(it, cars.end());
            cout << "Все автомобили с именем \"" << name << "\" удалены!" << endl;
            return true;
        }
        cout << "Автомобиль с именем \"" << name << "\" не найден!" << endl;
        return false;
    }
    
    // Отображение всех автомобилей
    void displayAll() const {
        if (cars.empty()) {
            cout << "Нет автомобилей в базе данных!" << endl;
            return;
        }
        
        cout << "\n" << string(70, '=') << endl;
        cout << left << setw(25) << "Марка и модель" 
             << setw(10) << "Год" 
             << setw(12) << "Объем двигателя" 
             << setw(15) << "Цена" << endl;
        cout << string(70, '-') << endl;
        
        for_each(cars.begin(), cars.end(), DisplayCar());
        cout << string(70, '=') << endl;
    }
    
    // Сортировка по различным параметрам
    void sortByName() {
        sort(cars.begin(), cars.end(), CompareByName());
        cout << "Сортировка по названию выполнена!" << endl;
        displayAll();
    }
    
    void sortByYear() {
        sort(cars.begin(), cars.end(), CompareByYear());
        cout << "Сортировка по году выпуска выполнена!" << endl;
        displayAll();
    }
    
    void sortByEngineVolume() {
        sort(cars.begin(), cars.end(), CompareByEngineVolume());
        cout << "Сортировка по объему двигателя выполнена!" << endl;
        displayAll();
    }
    
    void sortByPrice() {
        sort(cars.begin(), cars.end(), CompareByPrice());
        cout << "Сортировка по цене выполнена!" << endl;
        displayAll();
    }
    
    // Поиск по различным параметрам
    vector<Car> searchByName(const string& name) const {
        vector<Car> result;
        copy_if(cars.begin(), cars.end(), back_inserter(result), FindByName(name));
        return result;
    }
    
    vector<Car> searchByYear(int year) const {
        vector<Car> result;
        copy_if(cars.begin(), cars.end(), back_inserter(result), FindByYear(year));
        return result;
    }
    
    vector<Car> searchByEngineVolume(double minVol, double maxVol) const {
        vector<Car> result;
        copy_if(cars.begin(), cars.end(), back_inserter(result), 
                FindByEngineRange(minVol, maxVol));
        return result;
    }
    
    vector<Car> searchByPrice(double minPrice, double maxPrice) const {
        vector<Car> result;
        copy_if(cars.begin(), cars.end(), back_inserter(result), 
                FindByPriceRange(minPrice, maxPrice));
        return result;
    }
    
    vector<Car> searchByYearRange(int minYear, int maxYear) const {
        vector<Car> result;
        copy_if(cars.begin(), cars.end(), back_inserter(result), 
                FindByYearRange(minYear, maxYear));
        return result;
    }
    
    // Универсальный поиск с использованием функтора
    template<typename Predicate>
    vector<Car> search(Predicate pred) const {
        vector<Car> result;
        copy_if(cars.begin(), cars.end(), back_inserter(result), pred);
        return result;
    }
    
    // Вывод результатов поиска
    void displaySearchResults(const vector<Car>& results, const string& searchType) const {
        if (results.empty()) {
            cout << "По запросу \"" << searchType << "\" ничего не найдено!" << endl;
            return;
        }
        
        cout << "\nРезультаты поиска (" << results.size() << " записей):" << endl;
        cout << string(70, '-') << endl;
        cout << left << setw(25) << "Марка и модель" 
             << setw(10) << "Год" 
             << setw(12) << "Объем двигателя" 
             << setw(15) << "Цена" << endl;
        cout << string(70, '-') << endl;
        
        for_each(results.begin(), results.end(), DisplayCar());
    }
    
    // Обновление цен
    void updatePrices(double percentage) {
        for_each(cars.begin(), cars.end(), UpdatePrice(percentage));
        cout << "Цены обновлены на " << percentage << "%!" << endl;
        displayAll();
    }
    
    // Получение статистики
    void showStatistics() const {
        if (cars.empty()) {
            cout << "Нет данных для статистики!" << endl;
            return;
        }
        
        cout << "\n=== СТАТИСТИКА АВТОСАЛОНА ===" << endl;
        cout << "Всего автомобилей: " << cars.size() << endl;
        
        // Средняя цена
        double totalPrice = accumulate(cars.begin(), cars.end(), 0.0,
            [](double sum, const Car& car) { return sum + car.getPrice(); });
        double avgPrice = totalPrice / cars.size();
        cout << "Средняя цена: " << fixed << setprecision(2) << avgPrice << " руб." << endl;
        
        // Диапазон цен
        auto priceMinMax = minmax_element(cars.begin(), cars.end(), 
            [](const Car& a, const Car& b) { return a.getPrice() < b.getPrice(); });
        cout << "Минимальная цена: " << priceMinMax.first->getPrice() << " руб." << endl;
        cout << "Максимальная цена: " << priceMinMax.second->getPrice() << " руб." << endl;
        
        // Диапазон годов выпуска
        auto yearMinMax = minmax_element(cars.begin(), cars.end(),
            [](const Car& a, const Car& b) { return a.getYear() < b.getYear(); });
        cout << "Самый старый автомобиль: " << yearMinMax.first->getYear() << " год" << endl;
        cout << "Самый новый автомобиль: " << yearMinMax.second->getYear() << " год" << endl;
        
        // Список уникальных марок
        set<string> uniqueNames;
        for_each(cars.begin(), cars.end(), 
            [&uniqueNames](const Car& car) { uniqueNames.insert(car.getName()); });
        
        cout << "Количество уникальных марок: " << uniqueNames.size() << endl;
    }
    
    // Сохранение в файл (для примера)
    void saveToFile(const string& filename) const {
        // Здесь можно реализовать сохранение в файл
        cout << "Сохранение в файл \"" << filename << "\" (демонстрация)" << endl;
    }
    
    // Загрузка из файла (для примера)
    void loadFromFile(const string& filename) {
        // Здесь можно реализовать загрузку из файла
        cout << "Загрузка из файла \"" << filename << "\" (демонстрация)" << endl;
    }
};

// Функция для отображения меню
void showMenu() {
    cout << "\n" << string(50, '=') << endl;
    cout << "        СИСТЕМА УПРАВЛЕНИЯ АВТОСАЛОНОМ" << endl;
    cout << string(50, '=') << endl;
    cout << "1. Добавить автомобиль" << endl;
    cout << "2. Удалить автомобиль" << endl;
    cout << "3. Показать все автомобили" << endl;
    cout << "4. Сортировка по названию" << endl;
    cout << "5. Сортировка по году выпуска" << endl;
    cout << "6. Сортировка по объему двигателя" << endl;
    cout << "7. Сортировка по цене" << endl;
    cout << "8. Поиск по названию" << endl;
    cout << "9. Поиск по году выпуска" << endl;
    cout << "10. Поиск по диапазону объема двигателя" << endl;
    cout << "11. Поиск по диапазону цены" << endl;
    cout << "12. Поиск по диапазону годов выпуска" << endl;
    cout << "13. Обновить цены (на процент)" << endl;
    cout << "14. Показать статистику" << endl;
    cout << "15. Очистить базу данных" << endl;
    cout << "0. Выход" << endl;
    cout << string(50, '-') << endl;
    cout << "Выберите действие: ";
}

// Функция для ввода данных автомобиля
Car inputCar() {
    string name;
    int year;
    double engineVolume;
    double price;
    
    cin.ignore();
    cout << "Введите название автомобиля: ";
    getline(cin, name);
    
    cout << "Введите год выпуска: ";
    cin >> year;
    
    cout << "Введите объем двигателя (л): ";
    cin >> engineVolume;
    
    cout << "Введите цену (руб.): ";
    cin >> price;
    
    return Car(name, year, engineVolume, price);
}

int main() {
    CarDealership dealership;
    int choice;
    
    // Добавляем несколько тестовых автомобилей
    dealership.addCar(Car("Toyota Camry", 2022, 2.5, 3500000));
    dealership.addCar(Car("BMW X5", 2023, 3.0, 6500000));
    dealership.addCar(Car("Mercedes-Benz E-Class", 2021, 2.0, 4500000));
    dealership.addCar(Car("Honda Civic", 2022, 1.8, 2200000));
    dealership.addCar(Car("Kia Sportage", 2023, 2.0, 2800000));
    dealership.addCar(Car("Hyundai Tucson", 2021, 2.0, 2600000));
    dealership.addCar(Car("Nissan Qashqai", 2022, 1.6, 2300000));
    dealership.addCar(Car("Volkswagen Tiguan", 2023, 2.0, 3000000));
    
    do {
        showMenu();
        cin >> choice;
        
        switch (choice) {
            case 1: {
                Car car = inputCar();
                dealership.addCar(move(car));
                break;
            }
            case 2: {
                int index;
                cout << "Введите индекс автомобиля для удаления: ";
                cin >> index;
                dealership.removeCar(index);
                break;
            }
            case 3:
                dealership.displayAll();
                break;
            case 4:
                dealership.sortByName();
                break;
            case 5:
                dealership.sortByYear();
                break;
            case 6:
                dealership.sortByEngineVolume();
                break;
            case 7:
                dealership.sortByPrice();
                break;
            case 8: {
                string name;
                cin.ignore();
                cout << "Введите название: ";
                getline(cin, name);
                vector<Car> results = dealership.searchByName(name);
                dealership.displaySearchResults(results, "по названию: " + name);
                break;
            }
            case 9: {
                int year;
                cout << "Введите год выпуска: ";
                cin >> year;
                vector<Car> results = dealership.searchByYear(year);
                dealership.displaySearchResults(results, "по году: " + to_string(year));
                break;
            }
            case 10: {
                double minVol, maxVol;
                cout << "Введите минимальный объем двигателя: ";
                cin >> minVol;
                cout << "Введите максимальный объем двигателя: ";
                cin >> maxVol;
                vector<Car> results = dealership.searchByEngineVolume(minVol, maxVol);
                dealership.displaySearchResults(results, "по объему двигателя от " + 
                                                to_string(minVol) + " до " + to_string(maxVol));
                break;
            }
            case 11: {
                double minPrice, maxPrice;
                cout << "Введите минимальную цену: ";
                cin >> minPrice;
                cout << "Введите максимальную цену: ";
                cin >> maxPrice;
                vector<Car> results = dealership.searchByPrice(minPrice, maxPrice);
                dealership.displaySearchResults(results, "по цене от " + 
                                                to_string(minPrice) + " до " + to_string(maxPrice));
                break;
            }
            case 12: {
                int minYear, maxYear;
                cout << "Введите минимальный год: ";
                cin >> minYear;
                cout << "Введите максимальный год: ";
                cin >> maxYear;
                vector<Car> results = dealership.searchByYearRange(minYear, maxYear);
                dealership.displaySearchResults(results, "по году от " + 
                                                to_string(minYear) + " до " + to_string(maxYear));
                break;
            }
            case 13: {
                double percentage;
                cout << "Введите процент изменения цены (положительный - увеличение, отрицательный - уменьшение): ";
                cin >> percentage;
                dealership.updatePrices(percentage);
                break;
            }
            case 14:
                dealership.showStatistics();
                break;
            case 15: {
                char confirm;
                cout << "Вы уверены, что хотите очистить базу данных? (y/n): ";
                cin >> confirm;
                if (confirm == 'y' || confirm == 'Y') {
                    // Создаем новый объект вместо очистки
                    dealership = CarDealership();
                    cout << "База данных очищена!" << endl;
                }
                break;
            }
            case 0:
                cout << "До свидания!" << endl;
                break;
            default:
                cout << "Неверный выбор! Попробуйте снова." << endl;
        }
    } while (choice != 0);
    
    return 0;
}
