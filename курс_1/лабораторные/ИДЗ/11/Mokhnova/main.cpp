#include <iostream>
#include <cmath>    // Для fabs
#include <cassert>  // Для assert
#include "vector.h"

using namespace std;

// Вспомогательная функция для сравнения float с погрешностью
bool areEqual(float a, float b, float epsilon = 1e-5) {
    return fabs(a - b) < epsilon;
}

void testConstructor() {
    cout << "Testing Constructor..." << endl;

    // Нормальное создание
    float coords[] = { 1.0f, 2.0f, 3.0f };
    Vector v(coords, 3);
    assert(v.size == 3);
    assert(areEqual(v.cords[0], 1.0f));
    assert(areEqual(v.cords[1], 2.0f));
    assert(areEqual(v.cords[2], 3.0f));

    // Проверка исключения при nullptr
    try {
        Vector v_err(nullptr, 5);
        assert(false); // Должны были попасть в catch
    }
    catch (const invalid_argument& e) {
        // Ожидается
    }

    cout << "Constructor tests passed." << endl << endl;
}

void testAddAndMinus() {
    cout << "Testing Add and Minus..." << endl;

    float c1[] = { 1.0f, 2.0f, 3.0f };
    float c2[] = { 4.0f, 5.0f, 6.0f };
    Vector v1(c1, 3);
    Vector v2(c2, 3);

    // Сложение: (1+4, 2+5, 3+6) = (5, 7, 9)
    Vector vSum = v1.add(v2);
    assert(vSum.size == 3);
    assert(areEqual(vSum.cords[0], 5.0f));
    assert(areEqual(vSum.cords[1], 7.0f));
    assert(areEqual(vSum.cords[2], 9.0f));

    // Вычитание: (1-4, 2-5, 3-6) = (-3, -3, -3)
    Vector vDiff = v1.minus(v2);
    assert(vDiff.size == 3);
    assert(areEqual(vDiff.cords[0], -3.0f));
    assert(areEqual(vDiff.cords[1], -3.0f));
    assert(areEqual(vDiff.cords[2], -3.0f));

    // Тест разной размерности
    float c3[] = { 1.0f, 2.0f };
    Vector v3(c3, 2);
    Vector vErr = v1.add(v3);
    assert(vErr.size == 0); // Согласно спецификации, возвращается пустой вектор

    cout << "Add and Minus tests passed." << endl << endl;
}

void testMultiply() {
    cout << "Testing Multiply..." << endl;

    float c[] = { 1.0f, 2.0f, 3.0f };
    Vector v(c, 3);

    // Умножение на 2: (2, 4, 6)
    Vector vMult = v.multiply(2.0f);
    assert(areEqual(vMult.cords[0], 2.0f));
    assert(areEqual(vMult.cords[1], 4.0f));
    assert(areEqual(vMult.cords[2], 6.0f));

    cout << "Multiply tests passed." << endl << endl;
}

void testScalarAndLength() {
    cout << "Testing Scalar Product and Length..." << endl;

    float c1[] = { 1.0f, 2.0f, 3.0f };
    float c2[] = { 4.0f, 5.0f, 6.0f };
    Vector v1(c1, 3);
    Vector v2(c2, 3);

    // Скалярное произведение: 1*4 + 2*5 + 3*6 = 4 + 10 + 18 = 32
    float sc = v1.scalar(v2);
    assert(areEqual(sc, 32.0f));

    // Длина v1: sqrt(1^2 + 2^2 + 3^2) = sqrt(14) ≈ 3.741657
    float len = v1.length();
    assert(areEqual(len, sqrt(14.0f)));

    // Тест разной размерности для scalar
    float c3[] = { 1.0f };
    Vector v3(c3, 1);
    float scErr = v1.scalar(v3);
    assert(scErr == Vector::invalid);

    cout << "Scalar and Length tests passed." << endl << endl;
}

void testNormal() {
    cout << "Testing Normalization..." << endl;

    float c[] = { 3.0f, 4.0f }; // Длина 5
    Vector v(c, 2);

    Vector vNorm = v.normal();
    // Нормализованный вектор должен быть {0.6, 0.8}
    assert(areEqual(vNorm.cords[0], 0.6f));
    assert(areEqual(vNorm.cords[1], 0.8f));

    // Длина нормализованного вектора должна быть 1
    assert(areEqual(vNorm.length(), 1.0f));

    cout << "Normalization tests passed." << endl << endl;
}

int main() {
    cout << "=== Starting Vector Module Tests ===" << endl << endl;

    try {
        testConstructor();
        testAddAndMinus();
        testMultiply();
        testScalarAndLength();
        testNormal();

        cout << "=== ALL TESTS PASSED SUCCESSFULLY ===" << endl;
    }
    catch (const exception& e) {
        cerr << "Test failed with exception: " << e.what() << endl;
        return 1;
    }
    catch (...) {
        cerr << "Test failed with unknown exception." << endl;
        return 1;
    }

    return 0;
}