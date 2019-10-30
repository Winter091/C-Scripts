#include <iostream>
#include <string>
#include <map>
using namespace std;

std::map<int, char> table;

void fillMap()
{
	// '0' - '9'
	for (int i = 0; i < 10; i++)
	{
		table[i] = 48 + i;
	}
	
	// 'A' - 'Z'
	for (int i = 10; i < 36; i++)
	{
		table[i] = 'A' + (i - 10);
	}
}

// For example, returns 'F' if n is 15
char getLetterFromNumber(int n)
{
	return table[n];
}

// For example, return 15 if letter is 'F'
int getNumberFromLetter(char letter)
{
	for (int i = 0; i < 36; i++)
	{
		if (table[i] == letter) return i;
	}
	return -1;
}

// Check if digits of the number can be in that specific numerical base
// For example, 'F' cannot be in the base 10
bool numberIsCorrect(const string& n, int base)
{
	for (int i = 0; i < n.length(); i++)
	{
		if (getNumberFromLetter(n[i]) >= base) return false;
	}
	return true;
}

string convertInt(const string& n, int baseFrom, int baseTo)
{
	if (!numberIsCorrect(n, baseFrom))
		return "Error";

	if (baseFrom < 2 || baseTo < 2) return "Error";
	if (baseFrom > 36 || baseTo > 36) return "Error";

	// Firstly convert to base 10 
	unsigned long long inBase10 = 0;
	for (int i = 0; i < n.length(); i++)
	{
		inBase10 += getNumberFromLetter(n[i]) * pow(baseFrom, n.length() - 1 - i);
	}

	// Convert to desirable base
	string inNeededBase;
	while (inBase10 >= baseTo)
	{
		inNeededBase += getLetterFromNumber(inBase10 % baseTo);
		inBase10 /= baseTo;
	}
	inNeededBase += getLetterFromNumber(inBase10 % baseTo);
	reverse(inNeededBase.begin(), inNeededBase.end());

	return inNeededBase;
}

string toUpperAndNoSpaces(string& str)
{
	string ret;
	for (char &ch : str)
	{
		if (ch >= 'a' && ch <= 'z') ch -= 32;
		if (ch != ' ') ret += ch;
	}
	return ret;
}

int main()
{
	fillMap();
	
	while (true)
	{
		cout << "\n  Enter the number: ";
		string s; getline(cin, s);
		if (s == "q" || s == "Q" || s == "quit")
			break;

		string temp;

		cout << "    Enter its base: ";
		int baseFrom; cin >> temp;
		baseFrom = atoi(temp.c_str());

		cout << " Enter needed base: ";
		int baseTo; cin >> temp;
		baseTo = atoi(temp.c_str());

		s = toUpperAndNoSpaces(s);
		cout << "            Result: " << convertInt(s, baseFrom, baseTo);
		cout << '\n';

		// getline() doesn't work properly without this
		cin.ignore(256, '\n');
	}
}