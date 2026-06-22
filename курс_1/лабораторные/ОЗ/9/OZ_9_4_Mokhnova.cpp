#include <iostream>
#include <iomanip>
using namespace std;

void printBin(unsigned int n, size_t s);

int main()
{
	unsigned int x;

	cout << "Enter x: ";
	cin >> x;

	int s{ 8 * (sizeof x) };
	unsigned int m{};
	m--;

	cout << "x";
	printBin(x, s);
	cout << endl;

	unsigned int m1{};
	for (unsigned int i{ 1 }, j{}; j < s; i *= 4, j++)	m1 += i;

	// Processing

	unsigned int x1{ x | m1 };
	unsigned int x2{ x & m1 };

	unsigned int m2{};
	for (unsigned int i{ 8 }, j{}; j < s; i *= 16, j++)	m2 += i;

	unsigned int x3{ x ^ m2 };

	cout << fixed << setw(20) << "turn odds on";
	cout << fixed << setw(16) << x1;
	printBin(x1, s);

	cout << fixed << setw(20) << "turn even off";
	cout << fixed << setw(16) << x2;
	printBin(x2, s);

	cout << fixed << setw(20) << "switch each fourth";
	cout << fixed << setw(16) << x3;
	printBin(x3, s);

	cout << endl;


	unsigned int x4{ x };

	for (int i{ 1 }; i <= s; i++)
	{
		if (i > s - 4)
		{
			string s{ (x4 % 2 == 0) ? "off" : "on" };
			cout << "\tbit " << i << " - " << s << endl;
		}
		x4 = x4 >> 1;
	}
}


void printBin(unsigned int n, size_t s)
{
	string res{};

	while (n > 0)
	{
		res = (char)((n % 2) + '0') + res;
		n /= 2;
	}

	cout << "\t" << string(s - res.length(), '0') << res << endl;
}
