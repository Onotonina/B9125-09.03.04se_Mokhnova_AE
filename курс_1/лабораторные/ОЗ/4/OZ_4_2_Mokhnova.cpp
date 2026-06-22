#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
using namespace std;

struct Node
{
	int val{};
	Node* next{ nullptr };
};

void addToQuery(int n, Node*& head, Node*& tail);
bool removeFromQuery(Node*& head, Node*& tail);

void printList(Node*& head);


int main()
{
	srand(time(NULL));

	Node* head{}, * tail{};
	bool leave{ false };
	int i{};

	while (!leave)
	{
		int option;
		bool service{};

		do
		{
			cout << endl << "1 << Action" << endl;
			cout << "2 << Stop" << endl;
			cout << "Option >> ";
			cin >> option;

			if ((option < 1) || (option > 2))	cout << "Wrong option";
		} while ((option < 1) || (option > 2));

		cout << endl;

		switch (option)
		{
		case 1:
			service = rand() % 2 == 0;

			if (service)
			{
				cout << "Service. ";

				if (removeFromQuery(head, tail))
				{
					cout << "Service finished" << endl;
					printList(head);
				}
				else	cout << "No people in query" << endl;
			}
			else
			{
				cout << "Queuing" << endl;

				addToQuery(i, head, tail);
				printList(head);

				i++;
			}

			break;

		case 2:
			cout << "Goodbye!" << endl;
			leave = true;

			if (head != nullptr)
			{
				Node* p{ head };

				while (head != nullptr)
				{
					head = head->next;
					delete p;
					p = head;
				}
			}

			break;
		}
	}
}

void addToQuery(int n, Node*& head, Node*& tail)
{
	Node* newElem = new Node();
	newElem->val = n;

	if (tail != nullptr)
	{
		tail->next = newElem;
		tail = newElem;
		if (head->next == nullptr)	head->next = tail;
	}
	else
	{
		tail = newElem;
		head = newElem;
	}
}

bool removeFromQuery(Node*& head, Node*& tail)
{
	if (head != nullptr)
	{
		Node* p{ head };

		head = head->next;
		delete p;
		if (head == nullptr)	tail = nullptr;

		return true;
	}

	return false;
}

void printList(Node*& head)
{
	Node* p{ head };

	if (head == nullptr)	cout << "Empty query";

	while (p != nullptr)
	{
		cout << " " << p->val << " ";
		if (p->next != nullptr)	cout << "<=";

		p = p->next;
	}

	cout << endl;
}
