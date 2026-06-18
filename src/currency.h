#ifndef CURRENCY_H
#define CURRENCY_H

#include <string>
#include <vector>

using namespace std;

/**
 * @brief Структура для хранения информации о валюте
 */
struct CurrencyRate {
    string code;   ///< Код валюты (USD, EUR, RUB и т.д.)
    double rate;   ///< Курс к рублю (сколько RUB за 1 единицу валюты)
};

/**
 * @brief Вектор с текущими курсами всех валют
 */
extern vector<CurrencyRate> currentRates;

/**
 * @brief Список поддерживаемых валют
 */
extern const vector<string> SUPPORTED_CURRENCIES;

/**
 * @brief Получает курс валюты через API
 * @param currencyCode Код валюты (USD, EUR, RUB и т.д.)
 * @return Курс валюты к рублю (сколько RUB за 1 единицу валюты)
 * @throws runtime_error При ошибке HTTP или если валюта не найдена
 */
double fetchRateFromAPI(const string& currencyCode);

/**
 * @brief Загружает курсы всех валют из API
 */
void loadAllRates();

/**
 * @brief Выводит на экран все актуальные курсы валют (кроме RUB)
 */
void displayAllRates();

/**
 * @brief Конвертирует сумму из одной валюты в другую
 * @param fromCode Код исходной валюты
 * @param toCode Код целевой валюты
 * @param amount Сумма для конвертации
 * @return Сконвертированная сумма
 */
double convertCurrency(const string& fromCode, const string& toCode, double amount);

/**
 * @brief Проверяет, поддерживается ли данная валюта
 * @param code Код валюты для проверки
 * @return true если валюта поддерживается, false в противном случае
 */
bool isCurrencySupported(const string& code);

/**
 * @brief Запрашивает у пользователя код валюты и проверяет его поддержку
 * @param prompt Приглашение для ввода
 * @return Корректный код валюты в верхнем регистре
 */
string getValidCurrency(const string& prompt);

/**
 * @brief Запрашивает у пользователя сумму и проверяет её корректность
 * @return Положительная сумма (0 или больше)
 */
double getValidAmount();

/**
 * @brief Выполняет конвертацию: запрашивает данные, вычисляет и выводит результат
 */
void performConversion();

/**
 * @brief Обновляет курсы валют из API и выводит их
 */
void updateRates();

/**
 * @brief Выводит справочную информацию о кодах валют
 */
void showCurrencyHelp();

/**
 * @brief Выводит главное меню программы
 */
void showMenu();

#endif