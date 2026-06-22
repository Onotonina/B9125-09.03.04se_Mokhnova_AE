#include <iostream>
#include <string>
#include <set>
using namespace std;

struct NumNode
{
	float val{};
	NumNode* next{ nullptr };
};

void addToNumStack(NumNode*& heap, float n);
float takeFromNumStack(NumNode*& heap);

int priority(char op);
bool isNumeric(char c);
bool isNumeric(string s);

string getElem(string line, size_t& id, size_t& pid);

int main()
{
	string line;
	NumNode* numHeap{};

	cout << "Enter: ";
	getline(cin, line);

	size_t pid{ }, id{ line.find(' ') };
	string elem{ getElem(line, id, pid) };

	while (elem != "")
	{
		if (isNumeric(elem))
		{
			float n{ stof(elem) };
			addToNumStack(numHeap, n);
		}
		else
		{
			if (numHeap == nullptr)
			{
				cout << "Wrong Input" << endl;
				return 0;
			}

			float r;

			if (elem == "~")
			{
				float a{ takeFromNumStack(numHeap) };
				r = -a;

				addToNumStack(numHeap, r);
				elem = getElem(line, id, pid);
				continue;
			}

			if (numHeap->next == nullptr)
			{
				cout << "Wrong Input" << endl;
				return 0;
			}

			if (elem == "+")
			{
				float b{ takeFromNumStack(numHeap) };
				float a{ takeFromNumStack(numHeap) };
				r = a + b;
			}
			else if (elem == "-")
			{
				float b{ takeFromNumStack(numHeap) };
				float a{ takeFromNumStack(numHeap) };
				r = a - b;
			}
			else if (elem == "*")
			{
				float b{ takeFromNumStack(numHeap) };
				float a{ takeFromNumStack(numHeap) };
				r = a * b;
			}
			else if (elem == "/")
			{
				float b{ takeFromNumStack(numHeap) };
				float a{ takeFromNumStack(numHeap) };

				if (b != 0)	r = a / b;
				else
				{
					cout << "Wrong Input" << endl;
					return 0;
				}
			}
			else
			{
				cout << "Wrong Input" << endl;
				return 0;
			}

			addToNumStack(numHeap, r);
		}
		elem = getElem(line, id, pid);
	}

	float res{ takeFromNumStack(numHeap) };
	cout << "Result: " << res << endl;
}

bool isNumeric(char c)
{
	set<char> numbers{ '0','1','2','3','4','5','6','7','8','9' };
	return numbers.contains(c);
}

bool isNumeric(string s)
{
	for (char c : s)
	{
		if (!isNumeric(c))	return false;
	}
	return true;
}


void addToNumStack(NumNode*& heap, float n)
{
	NumNode* newElem = new NumNode();
	newElem->val = n;

	if (heap != nullptr)	newElem->next = heap;
	heap = newElem;
}

float takeFromNumStack(NumNode*& heap)
{
	float res{};
	NumNode* p{ heap };
	p = heap;
	heap = heap->next;

	res = p->val;
	delete p;

	return res;
}

string getElem(string line, size_t& id, size_t& pid)
{
	string res{};

	if (id != string::npos)
	{
		if (pid != 0) pid++;
		res = line.substr(pid, id - pid);
	}

	pid = id;
	id = line.find(' ', pid + 1);

	return res;
}
