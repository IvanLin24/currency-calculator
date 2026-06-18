#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include "../src/currency.h"

using namespace std;

TEST_CASE("Конвертация USD в RUB") {
    currentRates.clear();
    currentRates.push_back({"USD", 92.50});
    currentRates.push_back({"RUB", 1.0});
    
    CHECK(convertCurrency("USD", "RUB", 1.0) == 92.50);
}

TEST_CASE("Конвертация RUB в USD") {
    currentRates.clear();
    currentRates.push_back({"USD", 92.50});
    currentRates.push_back({"RUB", 1.0});
    
    CHECK(convertCurrency("RUB", "USD", 100.0) == doctest::Approx(100.0 / 92.50));
}

TEST_CASE("Одинаковые валюты") {
    CHECK(convertCurrency("USD", "USD", 100) == 100);
}

TEST_CASE("Поддержка валют") {
    CHECK(isCurrencySupported("USD"));
    CHECK(isCurrencySupported("EUR"));
    CHECK_FALSE(isCurrencySupported("BTC"));
}
