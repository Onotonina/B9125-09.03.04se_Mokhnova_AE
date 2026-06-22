#include <iostream>
using namespace std;

void printBin(unsigned int n);

int main()
{
    unsigned int x;
    cout << "Enter x: ";
    cin >> x;

    cout << endl << "X:  ";
    printBin(x);

    int n{};

    while (x > 0)
    {
        x = x >> 1;
        n++;
    }

    cout << "Count: " << n << endl;
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
