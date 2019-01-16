#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

struct Node
{
	std::string value;

	Node* left;
	Node* right;

	explicit Node(std::string value, Node* left = nullptr, Node* right = nullptr) noexcept
		: value(value), left(left), right(right)
	{ }

	~Node() noexcept
	{
		if (left != nullptr)
		{
			delete left;
		}

		if (right != nullptr)
		{
			delete right;
		}
	}
};

int StringToInt(const std::string& string)
{
	std::istringstream parser(string);
	int value;
	parser >> value;

	return value;
}

inline bool IsNumericString(const std::string& string) { return std::to_string(StringToInt(string)) == string; }

int SolveTreeExpression(Node* node)
{
	if (IsNumericString(node->value))
	{
		return StringToInt(node->value);
	}
	else
	{
		switch (node->value[0])
		{
		case '+':
			return SolveTreeExpression(node->left) + SolveTreeExpression(node->right);

		case '-':
			return SolveTreeExpression(node->left) - SolveTreeExpression(node->right);

		case '*':
			return SolveTreeExpression(node->left) * SolveTreeExpression(node->right);

		case '/':
			return SolveTreeExpression(node->left) / SolveTreeExpression(node->right);
			
		default:
			throw std::invalid_argument("Invalid operator.");
		}	
	}
}

int main(int argc, const char* argv[])
{
	Node* leftLeft = new Node("3");
	Node* leftRight = new Node("2");
	Node* rightLeft = new Node("4");
	Node* rightRight = new Node("5");
	Node* left = new Node("+", leftLeft, leftRight);
	Node* right = new Node("+", rightLeft, rightRight);
	Node* root = new Node("*", left, right);

	std::cout << SolveTreeExpression(root) << "\n";

	delete root;

	std::cin.get();

	return 0;
}