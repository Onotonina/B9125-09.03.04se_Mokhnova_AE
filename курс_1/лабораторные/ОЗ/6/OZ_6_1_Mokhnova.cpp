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


bool isNumeric(char c);
int priority(char c);
int priority(string c);

string processLine(string line);
TreeNode* buildTree(string line);

string directBypass(TreeNode* tree);
string reverceBypass(TreeNode* tree);
string symmetricBypass(TreeNode* tree);

void printTree(TreeNode* tree, int i = 0);

int main()
{
	string line;

	cout << "Enter: ";
	getline(cin, line);
	line = processLine(line);

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

	// Output

	printTree(root);

	string outMessage{};
	ofstream out;
	out.open("out61.txt");

	outMessage += "Direct: \t" + directBypass(root);
	outMessage += "\nReverce:\t" + reverceBypass(root);
	outMessage += "\nSymmetric:\t" + symmetricBypass(root);

	out << outMessage;
}

// Check

bool isNumeric(char c)
{
	set<char> numbers{ '0','1','2','3','4','5','6','7','8','9' };
	return numbers.contains(c);
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

string processLine(string in)
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

// Bypasses

string directBypass(TreeNode* tree)
{
	if (tree != nullptr)	return tree->val + " " + directBypass(tree->left) + directBypass(tree->right);
	else	return "";
}

string reverceBypass(TreeNode* tree)
{
	if (tree != nullptr)	return reverceBypass(tree->left) + reverceBypass(tree->right) + tree->val + " ";
	else	return "";
}

string symmetricBypass(TreeNode* tree)
{
	if (tree != nullptr)	return symmetricBypass(tree->left) + tree->val + " " + symmetricBypass(tree->right);
	else	return "";
}

void printTree(TreeNode* tree, int i)
{
	if (tree != nullptr)
	{
		printTree(tree->left, i + 1);
		cout << string(i, '\t') << tree->val << endl;
		printTree(tree->right, i + 1);
	}
}
