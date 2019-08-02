#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <memory>

struct Node
{
	char value;

	std::shared_ptr<Node> left;
	std::shared_ptr<Node> right;

	explicit Node(const char value, const std::shared_ptr<Node>& left = nullptr, const std::shared_ptr<Node>& right = nullptr)
		: value(value), left(left), right(right)
	{ }
};

int GetNodeHeight(const std::shared_ptr<Node>& node)
{
	if (node == nullptr)
	{
		return 0;
	}

	const int leftHeight = GetNodeHeight(node->left);
	const int rightHeight = GetNodeHeight(node->right);

	return std::max(leftHeight, rightHeight) + 1;
}

bool IsHeightBalanced(const std::shared_ptr<Node>& root)
{
	const int leftHeight = GetNodeHeight(root->left);
	const int rightHeight = GetNodeHeight(root->right);

	return std::abs(leftHeight - rightHeight) <= 1;
}

int main(int argc, char* argv[])
{
	const auto leftLeft = std::make_shared<Node>('d');
	const auto leftRight = std::make_shared<Node>('e');
	const auto left = std::make_shared<Node>('b', leftLeft, leftRight);
	const auto root = std::make_shared<Node>('a', left);

	std::cout << std::boolalpha;
	std::cout << IsHeightBalanced(root) << "\n";

	const auto rightLeft = std::make_shared<Node>('f');
	const auto rightRight = std::make_shared<Node>('g');
	const auto right = std::make_shared<Node>('c', rightLeft, rightRight);
	root->right = right;

	std::cout << IsHeightBalanced(root) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}