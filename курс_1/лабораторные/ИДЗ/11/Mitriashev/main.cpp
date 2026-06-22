
#include <iostream>
#include <iomanip>
#include <cassert>

#include "algebra.h"

using namespace Algebra;

// Тестирование nthRoot
void testNthRoot() {
    std::cout << "\n=== Тестирование nthRoot ===\n";

    // Тест 1: Кубический корень из 27
    double result = nthRoot(27.0, 3);
    std::cout << "nthRoot(27, 3) = " << result << " (ожидается: 3)\n";
    assert(std::abs(result - 3.0) < 0.0001);

    // Тест 2: Квадратный корень из 16
    result = nthRoot(16.0, 2);
    std::cout << "nthRoot(16, 2) = " << result << " (ожидается: 4)\n";
    assert(std::abs(result - 4.0) < 0.0001);

    // Тест 3: Корень 4-й степени из 81
    result = nthRoot(81.0, 4);
    std::cout << "nthRoot(81, 4) = " << result << " (ожидается: 3)\n";
    assert(std::abs(result - 3.0) < 0.0001);

    std::cout << "✓ Все тесты nthRoot пройдены!\n";
}

// Тестирование power
void testPower() {
    std::cout << "\n=== Тестирование power ===\n";

    // Тест 1: 2^10
    double result = power(2.0, 10);
    std::cout << "power(2, 10) = " << result << " (ожидается: 1024)\n";
    assert(std::abs(result - 1024.0) < 0.0001);

    // Тест 2: 3^4
    result = power(3.0, 4);
    std::cout << "power(3, 4) = " << result << " (ожидается: 81)\n";
    assert(std::abs(result - 81.0) < 0.0001);

    // Тест 3: Дробная степень (квадратный корень)
    result = power(16.0, 0.5);
    std::cout << "power(16, 0.5) = " << result << " (ожидается: 4)\n";
    assert(std::abs(result - 4.0) < 0.0001);

    std::cout << "✓ Все тесты power пройдены!\n";
}

// Тестирование logarithm
void testLogarithm() {
    std::cout << "\n=== Тестирование logarithm ===\n";

    // Тест 1: log2(8)
    double result = logarithm(8.0, 2.0);
    std::cout << "logarithm(8, 2) = " << result << " (ожидается: 3)\n";
    assert(std::abs(result - 3.0) < 0.0001);

    // Тест 2: log10(100)
    result = logarithm(100.0, 10.0);
    std::cout << "logarithm(100, 10) = " << result << " (ожидается: 2)\n";
    assert(std::abs(result - 2.0) < 0.0001);

    // Тест 3: ln(e) ≈ 1
    result = logarithm(2.718281828, 2.718281828);
    std::cout << "logarithm(e, e) = " << result << " (ожидается: 1)\n";
    assert(std::abs(result - 1.0) < 0.0001);

    // Тест 4: log3(27)
    result = logarithm(27.0, 3.0);
    std::cout << "logarithm(27, 3) = " << result << " (ожидается: 3)\n";
    assert(std::abs(result - 3.0) < 0.0001);

    std::cout << "Все тесты logarithm пройдены!\n";
}

// Тестирование factorial
void testFactorial() {
    std::cout << "\n=== Тестирование factorial ===\n";

    // Тест 1: 0! = 1
    unsigned long long result = factorial(0);
    std::cout << "factorial(0) = " << result << " (ожидается: 1)\n";
    assert(result == 1);

    // Тест 2: 5! = 120
    result = factorial(5);
    std::cout << "factorial(5) = " << result << " (ожидается: 120)\n";
    assert(result == 120);

    // Тест 3: 10! = 3628800
    result = factorial(10);
    std::cout << "factorial(10) = " << result << " (ожидается: 3628800)\n";
    assert(result == 3628800);

    // Тест 4: 20!
    result = factorial(20);
    std::cout << "factorial(20) = " << result << "\n";
    assert(result == 2432902008176640000ULL);

    std::cout << "Все тесты factorial пройдены!\n";
}

void testErrorHandling() {
    std::cout << "\n=== Тестирование обработки ошибок ===\n";

    // Тест 1: Отрицательная степень корня
    try {
        nthRoot(16.0, -2);
        std::cout << "Ошибка: должно было выбросить исключение\n";
    }
    catch (const std::invalid_argument& e) {
        std::cout << "nthRoot с отрицательной степенью: " << e.what() << "\n";
    }

    // Тест 2: Корень чётной степени из отрицательного числа
    try {
        nthRoot(-16.0, 2);
        std::cout << "Ошибка: должно было выбросить исключение\n";
    }
    catch (const std::domain_error& e) {
        std::cout << "nthRoot из отрицательного числа: " << e.what() << "\n";
    }

    // Тест 3: Логарифм с неправильным основанием
    try {
        logarithm(10.0, 1.0);
        std::cout << "Ошибка: должно было выбросить исключение\n";
    }
    catch (const std::invalid_argument& e) {
        std::cout << "logarithm с base=1: " << e.what() << "\n";
    }

    // Тест 4: Логарифм от отрицательного числа
    try {
        logarithm(-10.0, 2.0);
        std::cout << "Ошибка: должно было выбросить исключение\n";
    }
    catch (const std::domain_error& e) {
        std::cout << "logarithm от отрицательного числа: " << e.what() << "\n";
    }

    // Тест 5: Факториал отрицательного числа
    try {
        factorial(-5);
        std::cout << "Ошибка: должно было выбросить исключение\n";
    }
    catch (const std::invalid_argument& e) {
        std::cout << "factorial от отрицательного числа: " << e.what() << "\n";
    }

    std::cout << "Все тесты обработки ошибок пройдены!\n";
}

int main() {
    setlocale(LC_ALL, "Russian");
    std::cout << "========================================\n";
    std::cout << "  ТЕСТИРОВАНИЕ МОДУЛЯ ALGEBRA v1.0\n";
    std::cout << "  Метод чёрного ящика\n";
    std::cout << "========================================\n";


    // Запуск тестов
    try {
        testNthRoot();
        testPower();
        testLogarithm();
        testFactorial();
        testErrorHandling();
    }
    catch (const std::exception& e) {
        std::cerr << "\nОшибка тестирования: " << e.what() << "\n";
        return 1;
    }

    return 0;
}