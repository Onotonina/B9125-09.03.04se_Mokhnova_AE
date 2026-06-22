#include <iostream>
using namespace std;

bool lastByteOn(unsigned int x);

int main()
{
	unsigned int f;
	
	do
	{
		cout << "Enter F: ";
		cin >> f;
		if (f > 65536 || f < 256)	cout << "Wrong input" << endl;
	} while (f > 65536 || f < 256);

	// Process

	unsigned int fp{ f };
	bool isHotel{ lastByteOn(fp) };

	fp = fp >> 1;
	bool hasRooms{ lastByteOn(fp) };

	fp = fp >> 3;
	bool earlyArrive{ lastByteOn(fp) };

	fp = fp >> 1;
	bool lateLeave{ lastByteOn(fp) };

	fp = fp >> 3;
	unsigned int id{ fp };

	// Output

	cout << "Hotel info:" << endl;
	cout << "\tid\t\t" << id << endl;

	cout << "\ttype\t\t";
	cout << ((isHotel) ? "Hotel" : "Hostel");
	cout << endl;

	cout << "\thas rooms\t";
	cout << ((hasRooms) ? "Yes" : "No");
	cout << endl;

	cout << "\tearly arriving\n\tand late leave\t";
	cout << ((earlyArrive && lateLeave) ? "Yes" : "No");
	cout << endl;
}


bool lastByteOn(unsigned int x) { return x % 2 != 0; };
