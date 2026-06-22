#include <iostream>
#include <random>
#include <iomanip>
#include <string>
using namespace std;

struct Node
{
	int val;
	Node* up, * down, * left, * right;
};


void printMatrix(Node* first);

int main()
{
	srand(time(NULL));

	int m, n;

	do
	{
		cout << "Enter N: ";
		cin >> n;
		cout << "Enter M: ";
		cin >> m;
		if (n <= 0 || m <= 0)	cout << "Wrong input" << endl;
	} while (n <= 0 || m <= 0);

	// Building

	Node* first = new Node();
	first->val = rand() % 100;

	Node* pv{ first }, * pvOld{};

	for (int i{}; i < m; i++)
	{
		if (pv == nullptr)
		{
			Node* newElem = new Node();
			newElem->val = rand() % 100;

			newElem->up = pvOld;
			pvOld->down = newElem;
			pv = newElem;
		}

		Node* ph{ pv };
		Node* phUp{ pvOld };

		for (int j{}; j < n - 1; j++)
		{
			Node* rightElem = new Node();
			rightElem->val = rand() % 100;

			rightElem->left = ph;
			ph->right = rightElem;

			ph = ph->right;
			if (phUp != nullptr)	phUp = phUp->right;

			rightElem->up = phUp;
			if (phUp != nullptr)	phUp->down = rightElem;
		}

		pvOld = pv;
		pv = pv->down;
	}

	cout << endl;
	printMatrix(first);

	// Output

	Node* minNode{ first };
	int hmin{}, vmin{};
	pv = first;

	for (int i{}; pv != nullptr; i++)
	{
		Node* ph{ pv };

		for (int j{}; ph != nullptr; j++)
		{
			if (ph->val < minNode->val)
			{
				minNode = ph;
				vmin = i;
				hmin = j;
			}
			ph = ph->right;
		}

		pv = pv->down;
	}

	cout << endl;

	cout << "Min node info:" << endl;
	cout << "\tval: " << minNode->val << endl;
	cout << "\tadress: " << minNode << endl;
	cout << "\tindex (h): " << hmin << endl;
	cout << "\tindex (v): " << vmin << endl;
}


void printMatrix(Node* first)
{
	Node* pv{ first };

	while (pv != nullptr)
	{
		Node* ph{ pv };

		while (ph != nullptr)
		{
			cout << fixed << setw(4) << ph->val;
			ph = ph->right;
		}
		cout << endl;

		pv = pv->down;
	}
}
