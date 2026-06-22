#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

int main()
{
	// Input

	int n, m;

	do
	{
		cout << "Enter n (30/31/28): ";
		cin >> n;
		if (n != 31 && n != 30 && n != 28)	cout << "Wrong input" << endl;
	} while (n != 31 && n != 30 && n != 28);

	do
	{
		cout << "Enter m (1-7): ";
		cin >> m;
		if (m < 1 || m > 7)	cout << "Wrong input" << endl;
	} while (m < 1 || m > 7);

	int a1{ n + (m - 1) };
	const int k{ (a1 % 7 == 0) ? a1 / 7 : a1 / 7 + 1 };
	const int pn{ (n == 28 || n == 30) ? 31 : 30 };

	// Building

	string month[7][7]{};

	for (int i{}; i < k; i++)
	{
		if (i == 0)		// First line
		{
			for (int j{}; j < 7; j++)
			{
				string d;
				int k;

				if (j < m - 1)
				{
					k = pn - (m - 1 - (j + 1));
					d = '[' + to_string(k) +']';
				}
				else
				{
					k = j - m + 2;
					d = to_string(k);
				}

				month[i][j] = d;
			}
		}
		
		else if (i == k - 1)	// Last line
		{
			for (int j{}; j < 7; j++)
			{
				string d;
				int k{ 7 * i - (m - 2) + j };

				if (k > n)
				{
					k -= n;
					d = '[' + to_string(k) + ']';
				}
				else
				{
					d = to_string(k);
				}

				month[i][j] = d;
			}
		}

		else	// Other lines
		{
			for (int j{}; j < 7; j++)
			{
				int d{ 7 * i - (m - 2) + j };
				month[i][j] = to_string(d);
			}
		}
	}

	// Output

	string weekDays[]{ "", "Mo", "Tu", "We", "Th", "Fr", "St", "Su" };

	for (int i{}; i < k + 2; i++)
	{
		if (i == 0)		// First line
		{
			for (int j{}; j < 8; j++)	cout << fixed << setw(4) << weekDays[j] << " ";
		}
		else if (i == 1)		// Second line
		{
			cout << fixed << setw(4) << "      ----------------------------------";
		}

		else	// Other lines
		{
			cout << fixed << setw(4) << i - 1 << " |";
			for(int j{}; j < 7; j++)	cout << fixed << setw(4) << month[i - 2][j] << " ";	
		}
		
		cout << endl;
	}
}
