#include <iostream>
#include <string>
#include <set>
using namespace std;

struct NumNode
{
	float val{};
	NumNode* next{ nullptr };
};

struct OpNode
{
	char val{};
	OpNode* next{ nullptr };
};


string processExpression(string in);
float calculate(string line, bool& correctInput);

void addToNumStack(NumNode*& heap, float n);
float takeFromNumStack(NumNode*& heap);
void addToOpStack(OpNode*& heap, char op);
char takeFromOpStack(OpNode*& heap);

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

	string exp{ processExpression(line) };

	cout << exp << endl;

	bool c{ true };
	float res;

	if (exp != "")	res = calculate(exp, c);
	else
	{
		cout << "Wrong input" << endl;
		return 0;
	}

	if (c)	cout << "Result: " << res << endl;
	else	cout << "Wrong input" << endl;
}

float calculate(string line, bool& correctInput)
{
	NumNode* numHeap{};
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
				correctInput = false;
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
				correctInput = false;
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
					correctInput = false;
					return 0;
				}
			}
			else
			{
				correctInput = false;
				return 0;
			}

			addToNumStack(numHeap, r);
		}
		elem = getElem(line, id, pid);
	}

	float res{ takeFromNumStack(numHeap) };
	return res;
}

string processExpression(string in)
{
	OpNode* heap{};
	string line{}, out;
	char cOld{};

	for (char c : in)
	{
		if ((c == '-') && (!isNumeric(cOld)) && (cOld != ')'))	line += '~';
		else	line += c;
		cOld = c;
	}

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

					if (heap == nullptr)	return "";
				}

				takeFromOpStack(heap);
				prewIsOp = false;
			}
			else
			{
				if ((priority(c) == -1) || prewIsOp)	return "";

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

	return out;
}

// Check

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

int priority(char op)
{
	int priority[]{ '+', '-', '*', '/', '~' };

	for (int i{}; i < 5; i++)
	{
		if (priority[i] == op) return i;
	}

	return -1;
}

// Stack

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

// Other

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
