#include <iostream>
using namespace std;

void printBin(unsigned int n);

int main()
{
	unsigned int x;
	int n;

	cout << "Enter x: ";
	cin >> x;
	cout << "Enter n: ";
	cin >> n;

	cout << "x:  ";
	printBin(x);

	unsigned int x1;
	unsigned int x2;

	if (n >= 0)
	{
		x1 = x >> n;
		x2 = x << n;
	}
	else
	{
		x1 = x << (-n);
		x2 = x >> (-n);
	}

	cout << endl;
	cout << "x / 2^n = " << x1 << "\t";
	printBin(x1);

	cout << "x * 2^n = " << x2 << "\t";
	printBin(x2);
}


void printBin(unsigned int n)
{
	string res{};

	while (n > 0)
	{
		res = (char)((n % 2) + '0') + res;
		n /= 2;
	}

	size_t s{ (sizeof n) * 8 };
	cout << "\t" << string(s - res.length(), '0') << res << endl;
}
