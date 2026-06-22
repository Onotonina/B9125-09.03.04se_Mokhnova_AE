#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Node
{
	string val{};
	Node* next{ nullptr };
};

void addToStack(Node*& heap, Node* elem);
string takeFromStack(Node*& heap);


int main()
{
	Node* heap{};

	ifstream in;
	in.open("in41.txt");

	if (!in)
	{
		cout << "File open error" << endl;
		return 0;
	}

	string line;

	while (getline(in, line))
	{
		size_t pid{};
		size_t id{ line.find(' ') };
		string word;

		while (id != string::npos)
		{
			word = line.substr(pid, id - pid);
			Node* stackElem = new Node();
			stackElem->val = word;

			addToStack(heap, stackElem);

			pid = id + 1;
			id = line.find(' ', pid);
		}

		word = line.substr(pid, line.length() - pid);
		Node* stackElem = new Node();
		stackElem->val = "\n" + word;

		addToStack(heap, stackElem);
	}

	// Out

	cout << "The text backwards:";
	while (heap != nullptr)	cout << takeFromStack(heap) << " ";
}

void addToStack(Node*& heap, Node* newElem)
{
	if (heap != nullptr)	newElem->next = heap;
	heap = newElem;
}

string takeFromStack(Node*& heap)
{
	string res{};
	Node* p{ heap };
	p = heap;
	heap = heap->next;

	res = p->val;
	delete p;

	return res;
}
