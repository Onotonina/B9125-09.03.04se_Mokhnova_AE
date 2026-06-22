#ifndef VECTOR_H
#define VECTOR_H

/*
Модуль ОПЕРАЦИИ НАД ВЕКТОРАМИ
	Vector vector = Vector(coords, dimentions);

	float[] coords - координаты вектора (массив чисел с плавающей точкой)
	size_t dimentions - размерность (длина массива coords)
		Если dimentions < длины массива, лишние элементы cords отбрасываются
		Если dimentions > 0, а coords пуст, ошибка std::invalid_argument

	Vector add(Vector b);
	Прибавляет к вектору вектор b той же длины, возвращает результирующий вектор.
	Если векторы разной длины, возвращает Vector с пустыми координатами и размерностью 0.

	Vector minus(Vector b);
	Вычитает из вектора вектор b той же длины, возвращает результирующий вектор.
	Если векторы разной длины, возвращает Vector с пустыми координатами и размерностью 0.

	Vector multiply(float a);
	Умножает вектор на число a, возвращает полученное число.

	float scalar(Vector b);
	Скалярно перемножает вектор и вектор b той же длины, возвращает полученное число.
	Если векторы разной длины, возвращает число Vector::invalid.

	float length();
	Возвращает длину вектора.

	Vector normal();
	Возвращает вектор длины 1, коллинеарный вектору.
*/

using namespace std;


class Vector
{
public:
	const static int invalid{ -323232 };
	float* cords;
	size_t size;

	Vector(float cords[], size_t size);
	~Vector();

	Vector add(Vector b);
	Vector minus(Vector b);
	Vector multiply(float a);

	float scalar(Vector b);
	float length();
	
	Vector normal();
};

#endif
