#include <iostream>
#include <string>

using namespace std;

void printFigureA() {
    cout << "Фигура а:\n";
    cout << "*******\n";
    cout << "*     *\n";
    cout << "*     *\n";
    cout << "*******\n\n";
}

void printFigureB() {
    cout << "Фигура б:\n";
    cout << "*\n";
    cout << "**\n";
    cout << "***\n";
    cout << "****\n";
    cout << "*****\n\n";
}

void printFigureC() {
    cout << "Фигура в:\n";
    cout << "    *\n";
    cout << "   ***\n";
    cout << "  *****\n";
    cout << " *******\n";
    cout << "*********\n\n";
}

void printFigureD() {
    cout << "Фигура г:\n";
    cout << "*     *\n";
    cout << " *   *\n";
    cout << "  * *\n";
    cout << "   *\n";
    cout << "  * *\n";
    cout << " *   *\n";
    cout << "*     *\n\n";
}

void printFigureE() {
    cout << "Фигура д:\n";
    cout << "   ***\n";
    cout << "  *   *\n";
    cout << " *     *\n";
    cout << "*       *\n";
    cout << " *     *\n";
    cout << "  *   *\n";
    cout << "   ***\n\n";
}

void printFigureF() {
    cout << "Фигура е:\n";
    cout << "    *\n";
    cout << "   * *\n";
    cout << "  *   *\n";
    cout << " *     *\n";
    cout << "*       *\n";
    cout << " *     *\n";
    cout << "  *   *\n";
    cout << "   * *\n";
    cout << "    *\n\n";
}

void printFigureG() {
    cout << "Фигура ж:\n";
    cout << "*********\n";
    cout << " *******\n";
    cout << "  *****\n";
    cout << "   ***\n";
    cout << "    *\n\n";
}

void printFigureH() {
    cout << "Фигура з:\n";
    cout << "    *\n";
    cout << "   ***\n";
    cout << "  *****\n";
    cout << " *******\n";
    cout << "*********\n";
    cout << " *******\n";
    cout << "  *****\n";
    cout << "   ***\n";
    cout << "    *\n\n";
}

void printFigureI() {
    cout << "Фигура и:\n";
    cout << "*       *\n";
    cout << " *     *\n";
    cout << "  *   *\n";
    cout << "   * *\n";
    cout << "    *\n";
    cout << "   * *\n";
    cout << "  *   *\n";
    cout << " *     *\n";
    cout << "*       *\n\n";
}

void printFigureJ() {
    cout << "Фигура к:\n";
    cout << "    *****\n";
    cout << "   *     *\n";
    cout << "  *       *\n";
    cout << " *         *\n";
    cout << "*           *\n";
    cout << " *         *\n";
    cout << "  *       *\n";
    cout << "   *     *\n";
    cout << "    *****\n\n";
}

void printAllFigures() {
    printFigureA();
    printFigureB();
    printFigureC();
    printFigureD();
    printFigureE();
    printFigureF();
    printFigureG();
    printFigureH();
    printFigureI();
    printFigureJ();
}

int main() {
    int choice;
    
    do {
        cout << "=====================================\n";
        cout << "МЕНЮ ВЫБОРА ФИГУР\n";
        cout << "=====================================\n";
        cout << "1. Фигура а (прямоугольник)\n";
        cout << "2. Фигура б (прямоугольный треугольник слева)\n";
        cout << "3. Фигура в (равнобедренный треугольник)\n";
        cout << "4. Фигура г (крест)\n";
        cout << "5. Фигура д (ромб)\n";
        cout << "6. Фигура е (алмаз)\n";
        cout << "7. Фигура ж (перевернутый треугольник)\n";
        cout << "8. Фигура з (песочные часы)\n";
        cout << "9. Фигура и (двойной крест)\n";
        cout << "10. Фигура к (овал)\n";
        cout << "11. Вывести все фигуры\n";
        cout << "0. Выход\n";
        cout << "=====================================\n";
        cout << "Выберите фигуру (0-11): ";
        cin >> choice;
        
        switch(choice) {
            case 1:
                printFigureA();
                break;
            case 2:
                printFigureB();
                break;
            case 3:
                printFigureC();
                break;
            case 4:
                printFigureD();
                break;
            case 5:
                printFigureE();
                break;
            case 6:
                printFigureF();
                break;
            case 7:
                printFigureG();
                break;
            case 8:
                printFigureH();
                break;
            case 9:
                printFigureI();
                break;
            case 10:
                printFigureJ();
                break;
            case 11:
                printAllFigures();
                break;
            case 0:
                cout << "Выход из программы.\n";
                break;
            default:
                cout << "Неверный выбор! Попробуйте снова.\n";
        }
        
        if (choice != 0) {
            cout << "Нажмите Enter для продолжения...";
            cin.ignore();
            cin.get();
        }
        
    } while (choice != 0);
    
    return 0;
}
