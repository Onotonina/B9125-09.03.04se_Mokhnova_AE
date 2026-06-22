#include <iostream>
#include <random>
#include <ctime>
#include <iomanip>
using namespace std;

struct Node
{
	int val;
	Node* next{ nullptr };
};

void printRing(Node* head, int n);


int main()
{
	srand(time(NULL));

	int k, n;

	do
	{
		cout << "Enter count of words (k): ";
		cin >> k;
		if (k <= 0)	cout << "Enter valid k (>0)" << endl;
	} while (k <= 0);

	do
	{
		cout << "Enter count of players (n > k): ";
		cin >> n;
		if (n <= k)	cout << "Enter valid n" << endl;
	} while (n <= k);

	// Create list

	Node* first = new Node();
	first->val = 1;
	Node* prew{ first };

	for (int i{ 2 }; i <= n; i++)
	{
		Node* p = new Node();
		p->val = i;

		prew->next = p;
		prew = p;
	}
	prew->next = first;

	printRing(first, n);

	// Game

	Node* p{ first };

	while (first->next != first)
	{
		for (int i{}; i < k - 1; i++)
		{
			prew = p;
			p = p->next;
		}
		prew->next = p->next;

		if (p != first) delete p;
		else
		{
			delete p;
			first = nullptr;
		}
		p = prew->next;

		if (first == nullptr)				first = p;
		else if (first->next == nullptr)	first->next = p->next;

		n--;
		printRing(p, n);
	}

	// Output

	cout << endl << "Winner: player " << first->val << endl;
	delete first;
}

void printRing(Node* first, int n)
{
	cout << endl;

	Node* p{ first };

	for (int i{}; i < n; i++)
	{
		cout << fixed << setw(2) << p->val << " => ";
		p = p->next;

		if (i == n - 1)	cout << fixed << setw(2) << " . . . ";
	}

	cout << endl;
}
