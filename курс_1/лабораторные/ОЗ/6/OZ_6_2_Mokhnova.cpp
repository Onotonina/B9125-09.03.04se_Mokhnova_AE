#include <iostream>
#include <string>
#include <set>
#include <fstream>
using namespace std;

struct TreeNode
{
	string val{ "" };
	TreeNode* left{};
	TreeNode* right{};
	TreeNode* parent{};
};

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


bool isNumeric(char c);
bool isNumeric(string s);
int priority(char c);
int priority(string c);

string processToTreeLine(string line);
TreeNode* buildTree(string line);

string processLine(string in);

void addToStack(NumNode*& heap, float n);
float takeFromStack(NumNode*& heap);
void addToStack(OpNode*& heap, char op);
char takeFromStack(OpNode*& heap);

string getElem(string line, size_t& id, size_t& pid);
string reverceBypass(TreeNode* tree);

float calculate(string line, bool& correctInput);


int main()
{
	// Input

	int mode;
	string line;

	do
	{
		cout << "Enter build mode" << endl;
		cout << "0 << Sorting station" << endl;
		cout << "1 << Binary tree" << endl;
		cout << ">> ";
		cin >> mode;
		if (mode != 0 && mode != 1)	cout << "Wrong input" << endl;
	} while (mode != 0 && mode != 1);

	cout << "\nEnter: ";
	cin >> line;

	// Processing

	string expression;

	if (mode == 0)
	{
		expression = processLine(line);
		if (expression == "")
		{
			cout << "Wrong Input" << endl;
			return 0;
		}
	}

	else if (mode == 1)
	{
		line = processToTreeLine(line);
		if (line == "")
		{
			cout << "Wrong Input" << endl;
			return 0;
		}

		TreeNode* root = buildTree(line);
		if (root == nullptr)
		{
			cout << "Wrong Input" << endl;
			return 0;
		}

		expression = reverceBypass(root);
	}

	// Output
	
	cout << expression << endl;

	bool c{ true };
	float res{ calculate(expression, c) };

	if (c)	cout << "Result: " << res << endl;
	else	cout << "Wrong input" << endl;
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

int priority(char c)
{
	if (c == '+' || c == '-')		return 0;
	else if (c == '*' || c == '/')	return 1;
	else if (c == '~')				return 2;
	else	return -1;
}

int priority(string c)
{
	return priority(c[0]);
}

// Processing

string processToTreeLine(string in)
{
	string line{ in };

	// Unary minuses

	int s = line.length();
	for (int i{ s - 1 }; i >= 0; i--)
	{
		if (line[i] == '-')
		{
			if ((i == 0) || (line[i - 1] == '('))	line = line.replace(i, 1, "0-");
			else if (line[i - 1] != '(' && line[i - 1] != ')' && !isNumeric(line[i - 1]))	return "";
		}
	}

	// Brakets

	string ops[]{ "/*", "-+" };

	for (string op : ops)
	{
		size_t id{ line.find_first_of(op) }, pid{};

		while (id != string::npos)
		{
			size_t l{ id }, r{ id };

			if (l > 0 && line[l - 1] == ')')
			{
				int bc{ 1 };
				l--;

				while (l > 0 && bc > 0)
				{
					if (line[l - 1] == ')')		 bc++;
					else if (line[l - 1] == '(') bc--;
					l--;
				}
			}
			else if (l > 0 && isNumeric(line[l - 1]))	while (l > 0 && isNumeric(line[l - 1]))		l--;
			else	return "";

			if (r < line.length() && line[r + 1] == '(')
			{
				int bc{ 1 };
				r++;

				while (r < line.length() && bc > 0)
				{
					if (line[r + 1] == '(')		 bc++;
					else if (line[r + 1] == ')') bc--;
					r++;
				}
			}
			else if (r < line.length() && isNumeric(line[r + 1]))	while (r < line.length() && isNumeric(line[r + 1]))		r++;
			else	return "";

			string token{ line.substr(l, (r - l) + 1) };
			bool betweenBrackets{ (l > 0 && line[l - 1] == '(') && (r < line.length() && line[r + 1] == ')') };

			if (!betweenBrackets || (l == 0 || r == line.length()))
			{
				token = '(' + token + ')';
				id += 2;
			}
			line = line.replace(l, (r - l) + 1, token);

			pid = id;
			id = line.find_first_of(op, pid + 1);
		}
	}

	return line;
}

TreeNode* buildTree(string line)
{
	TreeNode* root = new TreeNode();
	root->val = "";

	string num{};
	TreeNode* p{ root };

	for (char c : line)
	{
		if (p == nullptr)	return nullptr;

		if (isNumeric(c))	num += c;
		else
		{
			if (num != "")
			{
				p->val = num;
				p = p->parent;

				num = "";
			}

			if (c == '(')
			{
				TreeNode* newElem = new TreeNode();
				newElem->parent = p;

				p->left = newElem;
				p = p->left;
			}
			else if (c == ')')
			{
				p = p->parent;
			}

			else if (priority(c) != -1)
			{
				p->val = c;

				TreeNode* newElem = new TreeNode();
				newElem->parent = p;

				p->right = newElem;
				p = p->right;
			}
			else	return nullptr;
		}
	}

	if (num != "")
	{
		TreeNode* newElem = new TreeNode();
		newElem->val = num;
		newElem->parent = p;

		if (p->left == nullptr)			p->left = newElem;
		else if (p->right == nullptr)	p->right = newElem;
	}

	return root;
}

string processLine(string in)
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
				addToStack(heap, c);
				prewIsOp = false;
			}
			else if (c == ')')
			{
				while ((heap != nullptr) && (heap->val != '('))
				{
					out += takeFromStack(heap);
					out += ' ';

					if (heap == nullptr)	return "";
				}

				takeFromStack(heap);
				prewIsOp = false;
			}
			else
			{
				if ((priority(c) == -1) || prewIsOp)	return "";

				while ((heap != nullptr) && (priority(heap->val) >= priority(c)))
				{
					out += takeFromStack(heap);
					out += ' ';
				}

				addToStack(heap, c);
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
		out += takeFromStack(heap);
		out += ' ';
	}

	return out;
}

// Stack

void addToStack(NumNode*& heap, float n)
{
	NumNode* newElem = new NumNode();
	newElem->val = n;

	if (heap != nullptr)	newElem->next = heap;
	heap = newElem;
}

float takeFromStack(NumNode*& heap)
{
	float res{};
	NumNode* p{ heap };
	p = heap;
	heap = heap->next;

	res = p->val;
	delete p;

	return res;
}

void addToStack(OpNode*& heap, char op)
{
	OpNode* newElem = new OpNode();
	newElem->val = op;

	if (heap != nullptr)	newElem->next = heap;
	heap = newElem;
}

char takeFromStack(OpNode*& heap)
{
	char res{};
	OpNode* p{ heap };
	p = heap;
	heap = heap->next;

	res = p->val;
	delete p;

	return res;
}

// Bypass

string reverceBypass(TreeNode* tree)
{
	if (tree != nullptr)	return reverceBypass(tree->left) + reverceBypass(tree->right) + tree->val + " ";
	else	return "";
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
			addToStack(numHeap, n);
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
				float a{ takeFromStack(numHeap) };
				r = -a;

				addToStack(numHeap, r);
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
				float b{ takeFromStack(numHeap) };
				float a{ takeFromStack(numHeap) };
				r = a + b;
			}
			else if (elem == "-")
			{
				float b{ takeFromStack(numHeap) };
				float a{ takeFromStack(numHeap) };
				r = a - b;
			}
			else if (elem == "*")
			{
				float b{ takeFromStack(numHeap) };
				float a{ takeFromStack(numHeap) };
				r = a * b;
			}
			else if (elem == "/")
			{
				float b{ takeFromStack(numHeap) };
				float a{ takeFromStack(numHeap) };

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

			addToStack(numHeap, r);
		}
		elem = getElem(line, id, pid);
	}

	float res{ takeFromStack(numHeap) };
	return res;
}
