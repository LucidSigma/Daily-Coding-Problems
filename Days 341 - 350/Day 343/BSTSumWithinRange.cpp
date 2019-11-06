#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>

struct Node
{
	int value;
	
	std::shared_ptr<Node> left;
	std::shared_ptr<Node> right;

	inline explicit Node(const int value, const std::shared_ptr<Node>& left = nullptr, const std::shared_ptr<Node>& right = nullptr)
		: value(value), left(left), right(right)
	{ }
};

int GetSumWithinRange(const std::shared_ptr<Node>& node, const std::pair<int, int>& range)
{
	if (const auto [low, high] = range; 
		node == nullptr)
	{
		return 0;
	}
	else if (node->value < low)
	{
		return GetSumWithinRange(node->right, range);
	}
	else if (node->value > high)
	{
		return GetSumWithinRange(node->left, range);
	}
	else
	{
		return node->value + GetSumWithinRange(node->left, range) + GetSumWithinRange(node->right, range);
	}
}

int main(const int argc, const char* const argv[])
{
	const auto leftLeft = std::make_shared<Node>(2);
	const auto leftRight = std::make_shared<Node>(4);
	const auto rightLeft = std::make_shared<Node>(6);
	const auto rightRight = std::make_shared<Node>(10);

	const auto left = std::make_shared<Node>(3, leftLeft, leftRight);
	const auto right= std::make_shared<Node>(8, rightLeft, rightRight);

	const auto root = std::make_shared<Node>(5, left, right);

	std::cout << GetSumWithinRange(root, { 4, 9 }) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}