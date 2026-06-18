#include "currency.h"
#include <iostream>
#include <stdexcept>
#include <iomanip>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

const vector<string> SUPPORTED_CURRENCIES = {"RUB", "USD", "EUR", "GBP", "CNY", "JPY"};
const string BASE_CURRENCY = "RUB";
const string API_URL = "https://api.exchangerate-api.com/v4/latest/";

vector<CurrencyRate> currentRates;

double fetchRateFromAPI(const string& currencyCode) {
    if (currencyCode == "RUB") {
        return 1.0;
    }
    
    string url = API_URL + BASE_CURRENCY;
    cpr::Response response = cpr::Get(cpr::Url{url});
    
    if (response.status_code != 200) {
        throw runtime_error("Ошибка HTTP: " + to_string(response.status_code));
    }
    
    json data = json::parse(response.text);
    
    if (!data.contains("rates")) {
        throw runtime_error("API не вернул курсы валют");
    }
    
    if (!data["rates"].contains(currencyCode)) {
        throw runtime_error("Валюта " + currencyCode + " не найдена");
    }

    double rateFromAPI = data["rates"][currencyCode].get<double>();
    double invertedRate = 1.0 / rateFromAPI;
    
    return invertedRate;
}

void loadAllRates() {
    currentRates.clear();
    for (const string& currency : SUPPORTED_CURRENCIES) {
        try {
            double rate = fetchRateFromAPI(currency);
            currentRates.push_back({currency, rate});
        }
        catch (const exception& e) {
            cout << "Ошибка загрузки " << currency << ": " << e.what() << endl;
        }
    }
}

void displayAllRates() {
    cout << "\nАКТУАЛЬНЫЙ КУРС ВАЛЮТ" << endl;
    cout << fixed << setprecision(4);
    for (const auto& cr : currentRates) {
        if (cr.code != "RUB") {
            cout << "1 " << cr.code << " = " << cr.rate << " RUB" << endl;
        }
    }
}

double convertCurrency(const string& fromCode, const string& toCode, double amount) {
    if (fromCode == toCode) {
        return amount;
    }
    
    double fromRate = 1.0;
    double toRate = 1.0;
    
    for (const auto& cr : currentRates) {
        if (cr.code == fromCode) {
            fromRate = cr.rate;
        }
        if (cr.code == toCode) {
            toRate = cr.rate;
        }
    }
    
    double inRubles = amount * fromRate;
    double result = inRubles / toRate;
    
    return result;
}

bool isCurrencySupported(const string& code) {
    for (const string& c : SUPPORTED_CURRENCIES) {
        if (c == code) {
            return true;
        }
    }
    return false;
}

string getValidCurrency(const string& prompt) {
    string code;
    while (true) {
        cout << prompt;
        cin >> code;
        for (char& c : code) {
            c = toupper(c);
        }
        if (isCurrencySupported(code)) {
            return code;
        }
        cout << "Ошибка: валюта " << code << " не поддерживается." << endl;
        cout << "Поддерживаемые валюты: ";
        for (const string& c : SUPPORTED_CURRENCIES) {
            cout << c << " ";
        }
        cout << endl;
    }
}

double getValidAmount() {
    double amount;
    while (true) {
        cout << "Сумма: ";
        cin >> amount;
        if (amount < 0) {
            cout << "Ошибка: сумма не может быть отрицательной" << endl;
            continue;
        }
        return amount;
    }
}

void performConversion() {
    cout << "\n--- КОНВЕРТАЦИЯ ВАЛЮТ ---" << endl;
    string fromCode = getValidCurrency("Из какой валюты: ");
    string toCode = getValidCurrency("В какую валюту: ");
    double amount = getValidAmount();
    double result = convertCurrency(fromCode, toCode, amount);
    cout << fixed << setprecision(2);
    cout << "\nРЕЗУЛЬТАТ: " << amount << " " << fromCode << " = " << result << " " << toCode << endl;
}

void updateRates() {
    cout << "\nОбновление курса..." << endl;
    try {
        loadAllRates();
        cout << "Курс успешно обновлён!" << endl;
        displayAllRates();
    }
    catch (const exception& e) {
        cout << "Ошибка: " << e.what() << endl;
    }
}

void showCurrencyHelp() {
    cout << "Код | Валюта | Страна" << endl;
    cout << "RUB | Рубль | Россия" << endl;
    cout << "USD | Доллар США | США" << endl;
    cout << "EUR | Евро | Евросоюз" << endl;
    cout << "GBP | Фунт | Великобритания" << endl;
    cout << "CNY | Юань | Китай" << endl;
    cout << "JPY | Иена | Япония" << endl;
}

void showMenu() {
    cout << "\n========== МЕНЮ ==========" << endl;
    cout << "1. Конвертировать валюту" << endl;
    cout << "2. Обновить курс" << endl;
    cout << "3. Справка по валютам" << endl;
    cout << "0. Выход" << endl;
    cout << "Выбор: ";
}