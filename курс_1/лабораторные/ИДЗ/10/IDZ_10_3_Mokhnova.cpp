#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
using namespace std;

struct Node
{
	int val{};
	Node* next{ nullptr };
	Node* prew{ nullptr };

	Node(int val, Node* next = nullptr, Node* prew = nullptr)
		: val{ val }, next{ next }, prew{ prew } {
	}
};

bool validOptionId(int id, int maxWindowId);

void newList(int len, Node*& head, Node*& tail);
void printList(Node* head, Node* tail);

void addToBeginning(Node*& head, Node*& tail);
bool addById(Node*& head, Node*& tail, int id);
void addToEnd(Node*& head, Node*& tail);

bool deleteById(Node*& head, Node*& tail, int id);
bool deleteByVal(Node*& head, Node*& tail, int val);
bool deleteFromBeginning(Node*& head);
bool deleteFromEnd(Node*& tail);
void clear(Node*& head);

int task2(Node*& head);


int main()
{
	srand(time(NULL));

	Node* head{}, * tail{};

	// Menu

	int window{}, next, option;
	int n{};
	bool leave{ false };
	int res;

	while (!leave)
	{
		bool invalid;

		switch (window)
		{
		case 0:
			do
			{
				cout << endl << "(1) Create list" << endl;
				cout << "(2) Print list" << endl;
				cout << "(3) Clear list" << endl;
				cout << "(4) Add element" << endl;
				cout << "(5) Delete element" << endl;
				cout << "(6) Task 2" << endl;
				cout << "(7) Stop" << endl;
				cout << "Go to >> ";
				cin >> next;

				invalid = !validOptionId(next, 7);
				if (invalid)	cout << "Wrong window" << endl;
			} while (invalid);

			cout << endl;

			window = next;
			break;

			// Creation

		case 1:
			clear(head);

			do
			{
				cout << "List len is equal to 2*n" << endl;
				cout << "Enter n: ";
				cin >> n;

				if (n < 1)	cout << "Enter len >= 1" << endl;
			} while (n < 1);

			newList(n * 2, head, tail);
			printList(head, tail);

			window = 0;
			break;

			// Print List

		case 2:
			printList(head, tail);

			window = 0;
			break;

			// Clear list

		case 3:
			clear(head);
			cout << "Cleared" << endl;

			window = 0;
			break;

			// Adding window

		case 4:
			do
			{
				cout << endl << "(1) Add by id" << endl;
				cout << "(2) Add to the beginning" << endl;
				cout << "(3) Add to the end" << endl;
				cout << "(4) Back" << endl;
				cout << "Go to >> ";
				cin >> option;

				invalid = !validOptionId(option, 4);
				if (invalid)	cout << "Wrong window" << endl;
			} while (invalid);

			cout << endl;

			switch (option)
			{
			case 1:
				int id;
				cout << "Enter id: ";
				cin >> id;

				if (addById(head, tail, id))	cout << "Added to " << id << endl;
				else					cout << "Failed to add to " << id << endl;
				break;

			case 2:
				addToBeginning(head, tail);
				cout << "Added to the beginning" << endl;
				break;

			case 3:
				addToEnd(head, tail);
				cout << "Added to the end" << endl;
				break;

			case 4:
				window = 0;
				break;
			}

			break;

			// Deleting window

		case 5:
			do
			{
				cout << endl << "(1) Delete by id" << endl;
				cout << "(2) Delete by value" << endl;
				cout << "(3) Delete from the beginning" << endl;
				cout << "(4) Delete from the end" << endl;
				cout << "(5) Back" << endl;
				cout << "Go to >> ";
				cin >> option;

				invalid = !validOptionId(option, 5);
				if (invalid)	cout << "Wrong window" << endl;
			} while (invalid);

			cout << endl;

			switch (option)
			{
			case 1:
				int id;
				cout << "Enter id: ";
				cin >> id;

				if (deleteById(head, tail, id))	cout << "Deleted from " << id << endl;
				else						cout << "Failed to delete from " << id << endl;
				break;

			case 2:
				int val;
				cout << "Enter val: ";
				cin >> val;

				if (deleteByVal(head, tail, val))	cout << val << " is deleted" << endl;
				else						cout << "Failed to delete " << val << endl;
				break;

			case 3:
				if (deleteFromBeginning(head))	cout << "Deleted from the beginning" << endl;
				else							cout << "Failed to delete from the beginning" << endl;
				break;

			case 4:
				if (deleteFromEnd(tail))	cout << "Deleted from the end" << endl;
				else						cout << "Failed to delete from end" << endl;
				break;

			case 5:
				window = 0;
				break;
			}

			break;

			// Task 2

		case 6:
			res = task2(head);

			cout << "Task 2:" << endl;
			if (res != -1)	cout << "S_min(x_1 + x_n+1 ,.. x_n + x_2n) = " << task2(head) << endl;
			else			cout << "Failed" << endl;

			window = 0;
			break;

			// Leave

		case 7:
			leave = true;
			clear(head);

			cout << "Goodbye!" << endl;
			break;
		}
	}
}


bool validOptionId(int id, int maxWindowId) { return (id >= 1) && (id <= maxWindowId); }

void newList(int len, Node*& head, Node*& tail)
{
	int r{ rand() % 100 };
	head = new Node(r);
	Node* p{ head };

	for (int i{}; i < len - 1; i++)
	{
		int r{ rand() % 100 };
		Node* e = new Node(r);

		p->next = e;
		e->prew = p;
		p = e;
		tail = e;
	}
}

void printList(Node* head, Node* tail)
{
	if (head != nullptr)
	{
		if (head->next != nullptr)
		{
			cout << "From head to tail: ";

			Node* p{ head };

			while (p != nullptr)
			{
				cout << p->val << setw(4) << fixed;
				if (p->next != nullptr)	cout << " => ";
				p = p->next;
			}
			cout << endl;

			cout << "From tail to head: ";

			p = tail;

			while (p != nullptr)
			{
				cout << p->val << setw(4) << fixed;
				if (p->prew != nullptr)	cout << " => ";
				p = p->prew;
			}
			cout << endl;
		}
		else
		{
			cout << "From head to tail: " << head->val << endl;
			cout << "From tail to head: " << head->val << endl;
		}
	}
	else	cout << "List is empty" << endl;
}

// Adding

void addToBeginning(Node*& head, Node*& tail)
{
	int r{ rand() % 100 };
	Node* newElem = new Node(r);

	if (head != nullptr)
	{
		newElem->next = head;
		head->prew = newElem;
		head = newElem;
	}
	else
	{
		head = newElem;
		tail = newElem;
	}
}

bool addById(Node*& head, Node*& tail, int id)
{
	Node* p{ head };

	if (id == 0)
	{
		addToBeginning(head, tail);
		return true;
	}

	if (head != nullptr)
	{
		for (int i{}; (i <= id); i++)
		{
			if (i == id)
			{
				int r{ rand() % 100 };
				Node* newElem = new Node(r, p);

				if (p->prew != nullptr)
				{
					p->prew->next = newElem;
					newElem->prew = p->prew;
					p->prew = newElem;
				}
				return true;
			}

			if (p->next == nullptr)		return false;
			p = p->next;
		}
	}

	return false;
}

void addToEnd(Node*& head, Node*& tail)
{
	int r{ rand() % 100 };
	Node* newElem = new Node(r);

	if (head != nullptr)
	{
		Node* p{ head };
		while (p->next != nullptr) p = p->next;

		p->next = newElem;
		newElem->prew = p;
		tail = newElem;
	}
	else
	{
		head = newElem;
		tail = newElem;
	}
}

// Deleting

bool deleteById(Node*& head, Node*& tail, int id)
{
	Node* p{ head };

	for (int i{}; (i <= id); i++)
	{
		if (p != nullptr)
		{
			if (i == id)
			{
				if (p->prew != nullptr)	p->prew->next = p->next;
				else					head = p->next;

				if (p->next != nullptr)	p->next->prew = p->prew;
				else					tail = p->prew;

				delete p;
				return true;
			}
		}
		else	return false;

		p = p->next;
	}

	return false;
}

bool deleteByVal(Node*& head, Node*& tail, int val)
{
	if (head != nullptr)
	{
		Node* p{ head };

		while (p != nullptr)
		{
			if (p->val == val)
			{
				if (p->prew != nullptr)	p->prew->next = p->next;
				else					head = p->next;

				if (p->next != nullptr) p->next->prew = p->prew;
				else					tail = p->prew;

				delete p;
				return true;
			}

			p = p->next;
		}
	}

	return false;
}

bool deleteFromBeginning(Node*& head)
{
	if (head != nullptr)
	{
		Node* p{ head };

		head = head->next;
		if (head != nullptr)	head->prew = nullptr;

		delete p;
		return true;
	}

	return false;
}

bool deleteFromEnd(Node*& tail)
{
	if (tail != nullptr)
	{
		Node* p{ tail };

		tail = tail->prew;
		if (tail != nullptr)	tail->next = nullptr;

		delete p;
		return true;
	}

	return false;
}

void clear(Node*& head)
{
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
}

// Task

int task2(Node*& head)
{
	if (head == nullptr) return -1;

	Node* p{ head };
	int n{};

	while (p != nullptr)
	{
		n++;
		p = p->next;
	}
	if (n % 2 != 0)	return -1;

	int min{ 200 };
	Node* p1{ head }, * p2{ head };

	for (int i{}; i < n / 2; i++)	p2 = p2->next;

	for (int i{}; i < n / 2; i++)
	{
		int s{ p1->val + p2->val };
		if (s < min)	min = s;

		p1 = p1->next;
		p2 = p2->next;
	}

	return min;
}
