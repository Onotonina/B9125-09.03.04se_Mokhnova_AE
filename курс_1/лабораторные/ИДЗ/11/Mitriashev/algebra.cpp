/**
 * @file algebra.cpp
 * @brief Реализация модуля элементарной алгебры
 */

#include "algebra.h"
#include <cmath>
#include <iomanip>

namespace Algebra {

    double nthRoot(double number, int degree) {
        if (degree <= 0) {
            throw std::invalid_argument("Степень корня должна быть больше 0");
        }

        if (number < 0 && degree % 2 == 0) {
            throw std::domain_error("Невозможно извлечь корень чётной степени из отрицательного числа");
        }

        // Извлечение корня n-й степени эквивалентно возведению в степень 1/n [[6]]
        return std::pow(number, 1.0 / degree);
    }

    double power(double base, double exponent) {
        return std::pow(base, exponent);
    }

    double logarithm(double number, double base) {
        if (base <= 0 || base == 1) {
            throw std::invalid_argument("Основание логарифма должно быть > 0 и != 1");
        }
        if (number <= 0) {
            throw std::domain_error("Аргумент логарифма должен быть > 0");
        }

        // Формула перехода: log_b(x) = log(x) / log(b) [[10]][[11]]
        return std::log(number) / std::log(base);
    }


    unsigned long long factorial(int n) {
        if (n < 0) {
            throw std::invalid_argument("Факториал определён только для неотрицательных чисел");
        }

        if (n > 20) {
            throw std::overflow_error("Переполнение: используйте factorialLarge для n > 20");
        }

        unsigned long long result = 1;
        for (int i = 2; i <= n; ++i) {
            result *= i;
        }
        return result;
    }

} // namespace Algebra