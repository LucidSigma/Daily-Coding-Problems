#include <cmath>
#include <iostream>
#include <memory>

struct Node
{
	int value;

	std::shared_ptr<Node> left;
	std::shared_ptr<Node> right;

	explicit Node(const int value, const std::shared_ptr<Node>& left = nullptr, const std::shared_ptr<Node>& right = nullptr) noexcept
		: value(value), left(left), right(right)
	{ }
};

unsigned int TreeNodeCountHelper(const std::shared_ptr<Node>& node, unsigned int leftCount, unsigned int rightCount) noexcept
{
	if (node == nullptr)
	{
		return 0;
	}

	if (leftCount == 0)
	{
		auto currentNode = node;

		while (currentNode != nullptr)
		{
			currentNode = currentNode->left;
			++leftCount;
		}
	}

	if (rightCount == 0)
	{
		auto currentNode = node;

		while (currentNode != nullptr)
		{
			currentNode = currentNode->right;
			++rightCount;
		}
	}

	if (leftCount == rightCount)
	{
		return static_cast<unsigned int>(std::pow(2, leftCount)) - 1;
	}

	return TreeNodeCountHelper(node->left, leftCount - 1, 0) + TreeNodeCountHelper(node->right, 0, rightCount - 1) + 1;
}

inline unsigned int TreeNodeCount(const std::shared_ptr<Node>& root) noexcept
{
	return TreeNodeCountHelper(root, 0, 0);
}

int main(int argc, char* argv[])
{
	const auto leftLeft = std::make_shared<Node>(4);
	const auto leftRight = std::make_shared<Node>(5);

	const auto left = std::make_shared<Node>(3, leftLeft, leftRight);
	const auto right = std::make_shared<Node>(2);

	const auto root = std::make_shared<Node>(1, left, right);

	std::cout << TreeNodeCount(root) << "\n";

	std::cin.get();

	return 0;
}