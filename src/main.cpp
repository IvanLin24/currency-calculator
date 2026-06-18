#include "currency.h"
#include <iostream>

using namespace std;

int main() {
    cout << "КАЛЬКУЛЯТОР ВАЛЮТ" << endl;
    cout << "Поддерживаемые валюты: ";
    for (const string& c : SUPPORTED_CURRENCIES) {
        cout << c << " ";
    }
    cout << endl;

    try {
        loadAllRates();
        displayAllRates();
    }
    catch (const exception& e) {
        cout << "ОШИБКА: Не удалось загрузить курс валют." << endl;
        cout << "Проверьте интернет и перезапустите программу." << endl;
        return 1;
    }

    int choice;
    do {
        showMenu();
        cin >> choice;
        try {
            if (choice == 1) performConversion();
            else if (choice == 2) updateRates();
            else if (choice == 3) showCurrencyHelp();
            else if (choice == 0) cout << "\nДо свидания!" << endl;
            else cout << "Неверный выбор. Введите 0, 1, 2 или 3." << endl;
        }
        catch (const exception& e) {
            cout << "\nОШИБКА: " << e.what() << endl;
        }
    } while (choice != 0);

    return 0;
}