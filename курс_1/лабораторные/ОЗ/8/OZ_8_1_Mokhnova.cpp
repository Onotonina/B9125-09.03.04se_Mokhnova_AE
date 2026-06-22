#include <iostream>
using namespace std;

int main()
{
	int n;

	cout << "Enter N: ";
	cin >> n;
	cout << endl;

	// 1

	long long res{ 1 }, res_stop{ 1 };
	int i{ 1 }, n_stop{ 1 };

	while (i <= n && res > 0)
	{
		res_stop = res;
		n_stop = i;
		res *= i;
		i++;
	}

	if (res > 0)	cout << "while\t\t" << res;
	else		cout << "(n_stop) while\t\t" << res_stop << "\t(" << n_stop - 1 << ")";
	cout << endl;

	// 2

	res = 1;
	res_stop = 1;
	i = 0;
	n_stop = 0;

	do
	{
		n_stop = i;
		i++;
		res_stop = res;
		res *= i;
	} while (i < n && res > 0);

	if (res > 0)	cout << "do-while\t" << res;
	else		cout << "(n_stop) do-while\t" << res_stop << "\t(" << n_stop << ")";
	cout << endl;

	// 3

	res = 1;
	res_stop = 1;
	n_stop = 0;

	for (int i{ 1 }; i <= n && res > 0; i++)
	{
		res_stop = res;
		res *= i;
		n_stop = i;
	}

	if (res > 0)	cout << "for\t\t" << res;
	else		cout << "(n_stop) for\t\t" << res_stop << "\t(" << n_stop - 1 << ")";
	cout << endl;
}
