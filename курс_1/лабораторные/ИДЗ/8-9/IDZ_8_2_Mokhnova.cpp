#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>
using namespace std;

struct Student
{
	string surName{};
	string name{};
	string fatherName{};

	char gender{};
	int age{};
	int year{};

	Student(string surName, string name, string fatherName,
		char gender, int age, int year)
		: surName{ surName }, name{ name }, fatherName{ fatherName },
		gender{ gender }, age{ age }, year{ year }
	{
	};
};

bool isNumeric(string s);
string readSegment(string line, size_t& pid, size_t& id);
void formatError(int lineid, string segment, string outFileName);


int main()
{
	string outFileName;

	cout << "Enter output file name: ";
	getline(cin, outFileName);

	ifstream in;
	in.open("in1.txt");

	if (!in)
	{
		string outMessage{ "Input file open error" };
		ofstream out;
		out.open(outFileName + ".txt");

		if (out)
		{
			out << outMessage;
			cout << outMessage;
		}
		else cout << "Output file open error" << endl;

		return 0;
	}

	vector<Student> students{};
	string outMessage{}, line{};
	int i{ 1 };

	while (getline(in, line) && (i <= 2000))
	{
		if (line == "") continue;

		string surName{};
		string name{};
		string fatherName{};

		char gender{};
		int age{};
		int year{};

		size_t pid{ }, id{ line.find(';') };

		surName = readSegment(line, pid, id);

		if (!((surName.length() <= 12) && (surName.length() > 0)))
		{
			formatError(i, "surname", outFileName);
			return 0;
		}

		name = readSegment(line, pid, id);

		if (!((name.length() <= 12) && (name.length() > 0)))
		{
			formatError(i, "name", outFileName);
			return 0;
		}

		fatherName = readSegment(line, pid, id);

		if (!((fatherName.length() <= 12) && (fatherName.length() > 0)))
		{
			formatError(i, "father name", outFileName);
			return 0;
		}


		set<char> genderAllowed{ 'M', 'F' };
		string sgender{ readSegment(line, pid, id) };

		if (sgender.length() == 1)
		{
			if (genderAllowed.contains(sgender[0]))
			{
				gender = sgender[0];
			}
			else
			{
				formatError(i, "gender", outFileName);
				return 0;
			}
		}
		else
		{
			formatError(i, "gender", outFileName);
			return 0;
		}

		string sage{ readSegment(line, pid, id) };

		if ((sage.length() == 2) && (isNumeric(sage)))
		{
			age = stoi(sage);

			if (!((age >= 16) && (age <= 35)))
			{
				formatError(i, "age", outFileName);
				return 0;
			}
		}
		else
		{
			formatError(i, "age", outFileName);
			return 0;
		}

		string syear{ readSegment(line, pid, id) };

		if ((syear.length() == 1) && (isNumeric(syear)))
		{
			year = stoi(syear);

			if (!((year >= 1) && (year <= 6)))
			{
				formatError(i, "year", outFileName);
				return 0;
			}
		}
		else
		{
			formatError(i, "year", outFileName);
			return 0;
		}


		Student student{ surName, name, fatherName, gender, age, year };
		students.push_back(student);

		i++;
	}

	// Results

	if (students.size() > 0)
	{
		// #1

		float maxp{ 0 };
		int maxpy{ 1 };

		for (int i{ 1 }; i <= 6; i++)
		{
			float c{}, mc{};

			for (Student s : students)
			{
				if (s.year == i)
				{
					if (s.gender == 'M')	mc++;
					c++;
				}
			}

			float p{ mc / c };

			if (maxp < p)
			{
				maxp = p;
				maxpy = i;
			}
		}

		outMessage += string("Max men: ");

		if (maxp != 0)	outMessage += to_string(maxpy) + string(" year\n");
		else			outMessage += "no men in list\n";

		// #2

		set<string> names{};
		set<string> mostPopularNames{};

		for (Student s : students)
		{
			if (s.gender == 'M')	names.insert(s.name);
		}

		for (int i{}; i < 3; i++)
		{
			int maxc{ -1 };
			string maxcn{};

			for (string name : names)
			{
				if (!mostPopularNames.contains(name))
				{
					int c{};

					for (Student s : students)
					{
						if (s.name == name) c++;
					}

					if (c > maxc)
					{
						maxc = c;
						maxcn = name;
					}
				}
			}

			mostPopularNames.insert(maxcn);
		}

		outMessage += string("Most popular male names: ");

		if (!mostPopularNames.empty())
		{
			for (string n : mostPopularNames) outMessage += n + " ";
		}
		else	outMessage += "no male names";

		outMessage += "\n";

		// #3

		int mmina{ 100 }, fmina{ 100 };
		string mminan{ "no males" }, fminan{ "no females" };

		for (Student s : students)
		{
			if (s.gender == 'M')
			{
				if (s.age < mmina)
				{
					mmina = s.age;
					mminan = s.name + " " + s.surName;
				}
			}
			else
			{
				if (s.age < fmina)
				{
					fmina = s.age;
					fminan = s.name + " " + s.surName;
				}
			}
		}

		outMessage += string("Youngest male: ") + mminan + string("\n");
		outMessage += string("Youngest female: ") + fminan + string("\n");
	}
	else
	{
		outMessage += string("The input file is empty");
	}

	// Output

	ofstream out;
	out.open(outFileName + ".txt");

	if (out)
	{
		out << outMessage;
		cout << outMessage;
	}
	else cout << "Output file open error" << endl;
}


bool isNumeric(string s)
{
	set<char> numbers{ '0','1','2','3','4','5','6','7','8','9' };

	for (char c : s)
	{
		if (!numbers.contains(c)) return false;
	}

	return true;
}

string readSegment(string line, size_t& pid, size_t& id)
{
	string res{};

	if (id != string::npos)
	{
		if (pid != 0) pid++;
		res = line.substr(pid, id - pid);
	}

	pid = id;
	id = line.find(';', pid + 1);

	return res;
}

void formatError(int lineid, string segment, string outFileName)
{
	string outMessage{ string("line ") + to_string(lineid) + string(": format error (") + segment + ")" };

	ofstream out;
	out.open(outFileName + ".txt");

	if (out)
	{
		out << outMessage;
		cout << outMessage;
	}
	else cout << "Output file open error" << endl;
}
