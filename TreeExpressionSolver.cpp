#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Tree
{
	string data;
	Tree* left;
	Tree* right;

	Tree(string data = "")
	{
		this->data = data;
		left = nullptr;
		right = nullptr;
	}
};

int getOperatorIndex(string expr)
{
	int index = -1;

	if (expr.find("*") != string::npos || expr.find("/") != string::npos)
	{
		int i1 = -1, i2 = -1;

		if (expr.find("*") != string::npos)
			i1 = expr.rfind("*");
		if (expr.find("/") != string::npos)
			i2 = expr.rfind("/");

		index = max(i1, i2);
	}

	if (expr.find("+") != string::npos || expr.find("-") != string::npos)
	{
		int i1 = -1, i2 = -1;
		
		if (expr.find("+") != string::npos)
			i1 = expr.rfind("+");
		if (expr.find("-") != string::npos)
			i2 = expr.rfind("-");

		index = max(i1, i2);
	}

	return index;
}

Tree* buildTree(string expr)
{
	Tree* tree = new Tree();
	int index = getOperatorIndex(expr);

	if (index != -1)
	{
		tree->data = expr.at(index);
		tree->left = buildTree(expr.substr(0, index));
		tree->right = buildTree(expr.substr(index + 1, expr.size() - index));
	}
	else
	{
		tree->data = expr;
	}

	return tree;
}

float solveExpr(const Tree* t)
{
	if (t->left == nullptr && t->right == nullptr)
	{
		return atoi(t->data.c_str());
	}
	
	float a = solveExpr(t->left);
	float b = solveExpr(t->right);

	if (t->data == "+") return a + b;
	if (t->data == "-") return a - b;
	if (t->data == "*") return a * b;
	if (t->data == "/") return a / b;
}

int main()
{
	Tree* t = buildTree("40-2*3-5*6");
	float answer = solveExpr(t);
	cout << answer;
}