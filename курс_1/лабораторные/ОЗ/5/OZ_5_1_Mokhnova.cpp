#include <iostream>
#include <string>
#include <set>
using namespace std;

struct OpNode
{
	char val{};
	OpNode* next{ nullptr };
};


void addToOpStack(OpNode*& heap, char op);
char takeFromOpStack(OpNode*& heap);

void printList(OpNode*& head);

int priority(char op);
bool isNumeric(char c);

int main()
{
	string in, line{}, out;
	OpNode* heap{};

	cout << "Enter: ";
	getline(cin, in);

	char cOld{};

	for (char c : in)
	{
		if ((c == '-') && (!isNumeric(cOld)) && (cOld != ')'))	line += '~';
		else	line += c;
		cOld = c;
	}

	// Processing

	bool prewIsOp{ false };
	string num{};

	for (char c : line)
	{
		if (isNumeric(c))	num += c;
		else
		{
			if (num != "")
			{
				out += num;
				out += ' ';
				num = "";
				prewIsOp = false;
			}

			if (c == '(')
			{
				addToOpStack(heap, c);
				prewIsOp = false;
			}
			else if (c == ')')
			{
				while ((heap != nullptr) && (heap->val != '('))
				{
					out += takeFromOpStack(heap);
					out += ' ';

					if (heap == nullptr)
					{
						cout << "Wrong input" << endl;
						return 0;
					}
				}

				takeFromOpStack(heap);
				prewIsOp = false;
			}
			else
			{
				if ((priority(c) == -1) || prewIsOp)
				{
					cout << "Wrong input" << endl;
					return 0;
				}

				while ((heap != nullptr) && (priority(heap->val) >= priority(c)))
				{
					out += takeFromOpStack(heap);
					out += ' ';
				}

				addToOpStack(heap, c);
				prewIsOp = true;
			}
		}
	}
	if (num != "")
	{
		out += num;
		out += ' ';
	}

	while (heap != nullptr)
	{
		out += takeFromOpStack(heap);
		out += ' ';
	}

	// Output

	cout << out << endl;
}

int priority(char op)
{
	int priority[]{ '+', '-', '*', '/', '~' };

	for (int i{}; i < 5; i++)
	{
		if (priority[i] == op) return i;
	}

	return -1;
}

bool isNumeric(char c)
{
	set<char> numbers{ '0','1','2','3','4','5','6','7','8','9' };
	return numbers.contains(c);
}

// Stack

void addToOpStack(OpNode*& heap, char op)
{
	OpNode* newElem = new OpNode();
	newElem->val = op;

	if (heap != nullptr)	newElem->next = heap;
	heap = newElem;
}

char takeFromOpStack(OpNode*& heap)
{
	char res{};
	OpNode* p{ heap };
	p = heap;
	heap = heap->next;

	res = p->val;
	delete p;

	return res;
}

void printList(OpNode*& head)
{
	OpNode* p{ head };

	if (head == nullptr)	cout << "Empty query";

	while (p != nullptr)
	{
		cout << " " << p->val << " ";
		if (p->next != nullptr)	cout << "<=";

		p = p->next;
	}

	cout << endl;
}
