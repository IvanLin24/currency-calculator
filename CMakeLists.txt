cmake_minimum_required(VERSION 3.20)
project(CurrencyCalculator)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH "/opt/homebrew" ${CMAKE_PREFIX_PATH})

enable_testing()

include(FetchContent)

FetchContent_Declare(
        cpr
        GIT_REPOSITORY https://github.com/libcpr/cpr.git
        GIT_TAG 1.10.0
)
FetchContent_MakeAvailable(cpr)

find_package(nlohmann_json CONFIG REQUIRED)
find_package(doctest CONFIG REQUIRED)

add_executable(CurrencyCalculator src/main.cpp src/currency.cpp)
target_link_libraries(CurrencyCalculator cpr::cpr nlohmann_json::nlohmann_json)

add_executable(tests tests/test.cpp src/currency.cpp)
target_link_libraries(tests cpr::cpr nlohmann_json::nlohmann_json doctest::doctest)
add_test(NAME CurrencyTests COMMAND tests)