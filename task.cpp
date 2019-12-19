#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

using ull = unsigned long long;

ull getNOD(ull a, ull b)
{
	while (a && b)
	{
		if (a > b)
			a %= b;
		else
			b %= a;
	}
	return a + b;
}

int main() 
{
	ull a, b, c, d, limit, n;
	cin >> a >> b >> c >> d >> limit >> n;

	set<pair<ull, ull> > fractions;

	double left = a / (double)b;
	double right = c / (double)d;

	ull currNumerator = a;
	ull currDenominator = b;

	while (true)
	{
		currNumerator = a;
		
		while ((double)currNumerator / currDenominator < right)
		{		
			if (++currNumerator > limit)
				break;

			double currNum = (double)currNumerator / currDenominator;

			if (currNum >= right)
				break;

			if (currNum > left)
			{
				ull nod = getNOD(currNumerator, currDenominator);
				fractions.insert(pair<ull, ull>(currDenominator / nod, currNumerator / nod));
			}

			if (fractions.size() == n)
				break;
		}
		
		if (++currDenominator > limit)
			break;

		if (fractions.size() >= n)
			break;
	}

	cout << fractions.size() << '\n';
	for (auto it : fractions)
	{
		cout << it.second << " " << it.first << '\n';
	}
}
