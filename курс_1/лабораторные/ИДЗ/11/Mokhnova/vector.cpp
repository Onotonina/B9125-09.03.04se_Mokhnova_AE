#include "vector.h"
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;


Vector::Vector(float cords[], size_t size) : size{ size }
{
	if (cords == nullptr && size > 0) throw std::invalid_argument("Null pointer");

	this->cords = new float[size];
	for (size_t i{}; i < size; i++)	this->cords[i] = cords[i];
}

Vector::~Vector()
{
	delete[] cords;
}

// Vectors

Vector Vector::add(Vector b)
{
	if (size != b.size)	return Vector(nullptr, 0);

	float* newCords = new float[size] {};
	for (size_t i{}; i < size; i++)	newCords[i] = cords[i] + b.cords[i];

	return Vector(newCords, size);
}

Vector Vector::minus(Vector b)
{
	if (size != b.size)	return Vector(nullptr, 0);

	b = b.multiply(-1);
	return this->add(b);
}

// Nums

Vector Vector::multiply(float a)
{
	float* newCords = new float[size] {};
	for (size_t i{}; i < size; i++)	newCords[i] = cords[i] * a;

	return Vector(newCords, size);
}

float Vector::scalar(Vector b)
{
	if (size != b.size)	return invalid;
	
	float res{};
	for (size_t i{}; i < size; i++)	res += cords[i] * b.cords[i];

	return res;
}

float Vector::length()
{
	float res{};
	for (size_t i{}; i < size; i++) res += pow(cords[i], 2);

	res = sqrt(res);
	return res;
}

Vector Vector::normal()
{
	if (length() != 0)
	{
		float k{ 1 / length() };
		return this->multiply(k);
	}
	else	return Vector(nullptr, 0);
}
