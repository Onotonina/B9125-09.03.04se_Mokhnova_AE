/**
 * @file algebra.h
 * @brief Модуль элементарной алгебры
 *
 * Содержит функции для:
 * - Вычисления корней любой степени
 * - Возведения числа в произвольную степень
 * - Вычисления логарифмов по любому основанию
 * - Вычисления факториалов
 */

#ifndef ALGEBRA_H
#define ALGEBRA_H



namespace Algebra {

    /**
     * @brief Вычисление корня n-й степени из числа
     * @param number Число, из которого извлекается корень
     * @param degree Степень корня (n)
     * @return double Результат вычисления
     * @throws std::invalid_argument если degree <= 0
     * @throws std::domain_error если number < 0 и degree чётное
     */
    double nthRoot(double number, int degree);

    /**
     * @brief Возведение числа в произвольную степень
     * @param base Основание степени
     * @param exponent Показатель степени
     * @return double Результат вычисления
     */
    double power(double base, double exponent);

    /**
     * @brief Вычисление логарифма по произвольному основанию
     * @param number Число, для которого вычисляется логарифм
     * @param base Основание логарифма
     * @return double Результат вычисления
     * @throws std::invalid_argument если base <= 0 или base == 1
     * @throws std::domain_error если number <= 0
     */
    double logarithm(double number, double base);


    /**
     * @brief Вычисление факториала числа (для небольших чисел)
     * @param n Неотрицательное целое число
     * @return unsigned long long Результат вычисления
     * @throws std::invalid_argument если n < 0
     * @throws std::overflow_error если результат переполняет unsigned long long
     */
    unsigned long long factorial(int n);

    /**
     * @brief Вычисление факториала большого числа (возвращает строку)
     * @param n Неотрицательное целое число
     * @return std::string Строковое представление факториала
     * @throws std::invalid_argument если n < 0
     */
} 

#endif 