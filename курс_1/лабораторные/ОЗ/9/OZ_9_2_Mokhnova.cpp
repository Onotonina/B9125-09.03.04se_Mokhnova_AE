#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

void printBin(unsigned long long n, size_t s);

int main()
{
    unsigned int x, n;
    size_t s{ 8 * (sizeof x) };

    cout << "Enter x: ";
    cin >> x;
    cout << "Enter n: ";
    cin >> n;

    cout << endl << "X:" << endl;
    cout << fixed << setw(10) << x << "\t";
    printBin(x, s);

    size_t k = s - n;
    unsigned int x1 = x << n % s;
    unsigned int x2 = x >> k % s;

    x = x1 | x2;

    cout << "Result:" << endl;
    cout << fixed << setw(10) << x << "\t";
    printBin(x, s);
}

void printBin(unsigned long long n, size_t s)
{
    string res{};

    while (n > 0)
    {
        res = (char)((n % 2) + '0') + res;
        n /= 2;
    }

    cout << string(s - res.length(), '0') << res << endl;
}
