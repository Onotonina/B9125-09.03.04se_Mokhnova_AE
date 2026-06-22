#include <iostream>
using namespace std;

int main()
{
	int n;

	do
	{
		cout << "Enter n (100-999): ";
		cin >> n;
		if (n < 100 || n > 999)	cout << "Wrong input" << endl;
	} while (n < 100 || n > 999);

	char a, b, c;
	c = (n % 10) + '0';
	b = ((n / 10) % 10) + '0';
	a = ((n / 100) % 10) + '0';

	cout << endl;
	cout << "a:  " << (int)a << " [" << a << "]" << endl;
	cout << "b:  " << (int)b << " [" << b << "]" << endl;
	cout << "c:  " << (int)c << " [" << c << "]" << endl;
	cout << "ASCII a + b + c\t" << a + b + c << endl;
}
