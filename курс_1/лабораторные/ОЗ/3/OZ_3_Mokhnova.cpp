#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
using namespace std;

struct Node
{
	int val{};
	Node* next{ nullptr };

	Node(int val, Node* next = nullptr)
		: val{ val }, next{ next } {
	}
};

bool validOptionId(int id, int maxWindowId);

void printList(Node* head);

void addToBeginning(Node*& head);
bool addById(Node*& head, int id);
void addToEnd(Node*& head);

bool deleteById(Node*& head, int id);
bool deleteByVal(Node*& head, int val);
bool deleteFromBeginning(Node*& head);
bool deleteFromEnd(Node*& head);
void clear(Node*& head);


int main()
{
	srand(time(NULL));

	int len;

	do
	{
		cout << "Enter list len: ";
		cin >> len;

		if (len <= 2)	cout << "Enter len > 2" << endl;
	} while (len <= 2);

	// Building list

	int r{ rand() % 100 };
	Node* head = new Node(r);

	Node* p{ head };

	for (int i{}; i < len - 1; i++)
	{
		int r{ rand() % 100 };
		Node* e = new Node(r);
		p->next = e;
		p = e;
	}

	printList(head);

	// Menu

	int window{}, next, option;
	bool leave{ false };

	while (!leave)
	{
		bool invalid;

		switch (window)
		{
		case 0:
			do
			{
				cout << endl << "1 << Add element" << endl;
				cout << "2 << Delete element" << endl;
				cout << "3 << Print list" << endl;
				cout << "4 << Leave" << endl;
				cout << "Go to >> ";
				cin >> next;

				invalid = !validOptionId(next, 4);
				if (invalid)	cout << "Wrong window" << endl;
			} while (invalid);

			cout << endl;

			window = next;
			break;

			// Adding window

		case 1:
			do
			{
				cout << endl << "1 << Add by id" << endl;
				cout << "2 << Add to the beginning" << endl;
				cout << "3 << Add to the end" << endl;
				cout << "4 << Back" << endl;
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

				if (addById(head, id))	cout << "Added to " << id << endl;
				else					cout << "Failed to add to " << id << endl;
				break;

			case 2:
				addToBeginning(head);
				cout << "Added to the beginning" << endl;
				break;

			case 3:
				addToEnd(head);
				cout << "Added to the end" << endl;
				break;

			case 4:
				window = 0;
				break;
			}

			break;

			// Deleting window

		case 2:
			do
			{
				cout << endl << "1 << Delete by id" << endl;
				cout << "2 << Delete by value" << endl;
				cout << "3 << Delete from the beginning" << endl;
				cout << "4 << Delete from the end" << endl;
				cout << "5 << Clear list" << endl;
				cout << "6 << Back" << endl;
				cout << "Go to >> ";
				cin >> option;

				invalid = !validOptionId(option, 6);
				if (invalid)	cout << "Wrong window" << endl;
			} while (invalid);

			cout << endl;

			switch (option)
			{
			case 1:
				int id;
				cout << "Enter id: ";
				cin >> id;

				if (deleteById(head, id))	cout << "Deleted from " << id << endl;
				else						cout << "Failed to delete from " << id << endl;
				break;

			case 2:
				int val;
				cout << "Enter val: ";
				cin >> val;

				if (deleteByVal(head, val))	cout << val << " is deleted" << endl;
				else						cout << "Failed to delete " << val << endl;
				break;

			case 3:
				if (deleteFromBeginning(head))	cout << "Deleted from the beginning" << endl;
				else							cout << "Failed to delete from the beginning" << endl;
				break;

			case 4:
				if (deleteFromEnd(head))	cout << "Deleted from the end" << endl;
				else						cout << "Failed to delete from end" << endl;
				break;

			case 5:
				clear(head);
				cout << "Cleared" << endl;
				break;

			case 6:
				window = 0;
				break;
			}

			break;

		case 3:
			printList(head);

			window = 0;
			break;

		case 4:
			leave = true;
			clear(head);
			cout << "Goodbye!" << endl;
			break;
		}
	}
}


bool validOptionId(int id, int maxWindowId)
{
	return (id >= 1) && (id <= maxWindowId);
}

void printList(Node* head)
{
	if (head != nullptr)
	{
		Node* p{ head };

		do
		{
			cout << "[" << p->val << " | " << p << "]" << setw(4) << fixed;
			p = p->next;
		} while (p != nullptr);
		cout << endl;
	}
	else	cout << "The list is empty" << endl;
}

// Adding

void addToBeginning(Node*& head)
{
	int r{ rand() % 100 };
	Node* newElem = new Node(r);

	if (head != nullptr)	newElem->next = head;
	head = newElem;
}

bool addById(Node*& head, int id)
{
	Node* p{ head };
	Node* prew{};

	if (id == 0)
	{
		addToBeginning(head);
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

				prew->next = newElem;
				return true;
			}

			if (p->next == nullptr)		return false;

			prew = p;
			p = p->next;
		}
	}

	return false;
}

void addToEnd(Node*& head)
{
	int r{ rand() % 100 };
	Node* newElem = new Node(r);

	if (head != nullptr)
	{
		Node* p{ head };
		while (p->next != nullptr) p = p->next;

		p->next = newElem;
	}
	else	head = newElem;
}

// Deleting

bool deleteById(Node*& head, int id)
{
	Node* p{ head };
	Node* prew{};

	if (id == 0)
	{
		return deleteFromBeginning(head);
	}

	for (int i{}; (i <= id); i++)
	{
		if (p != nullptr)
		{
			if (i == id)
			{
				prew->next = p->next;
				delete p;
				p = nullptr;
				return true;
			}
		}
		else	return false;

		prew = p;
		p = p->next;
	}

	return false;
}

bool deleteByVal(Node*& head, int val)
{
	if (head != nullptr)
	{
		Node* p{ head };
		Node* prew{};

		while (p != nullptr)
		{
			if (p->val == val)
			{
				if (prew != nullptr)	prew->next = p->next;
				else					head = p->next;

				delete p;
				p = nullptr;
				return true;
			}

			prew = p;
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

		delete p;
		p = nullptr;
		return true;
	}

	return false;
}

bool deleteFromEnd(Node*& head)
{
	if (head != nullptr)
	{
		Node* p{ head };

		if (p->next != nullptr)
		{
			Node* q{ p->next };

			while (q->next != nullptr)
			{
				p = p->next;
				q = q->next;
			}

			p->next = nullptr;
			delete q;
			q = nullptr;
		}
		else
		{
			delete p;
			head = nullptr;
		}

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
