#include <iostream>
#include <limits>
#include <memory>

struct Node
{
	int value;

	std::shared_ptr<Node> left;
	std::shared_ptr<Node> right;

	explicit Node(int value, const std::shared_ptr<Node>& left = nullptr, const std::shared_ptr<Node>& right = nullptr)
		: value(value), left(left), right(right)
	{ }
};

bool IsValidBinarySearchTreeHelper(const std::shared_ptr<Node>& node, int leftMin, int rightMax) noexcept
{
	if (node != nullptr && node->value <= rightMax && node->value >= leftMin)
	{
		bool isLeftValid = IsValidBinarySearchTreeHelper(node->left, leftMin, node->value);
		bool isRightValid = IsValidBinarySearchTreeHelper(node->right, node->value, rightMax);

		return isLeftValid && isRightValid;
	}

	return node == nullptr;
}

inline bool IsValidBinarySearchTree(const std::shared_ptr<Node>& root) noexcept
{
	return IsValidBinarySearchTreeHelper(root, std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
}

int main(int argc, char* argv[])
{
	auto leftLeft = std::make_shared<Node>(3);
	auto leftRight = std::make_shared<Node>(10);
	auto left = std::make_shared<Node>(6, leftLeft, leftRight);

	auto rightLeft = std::make_shared<Node>(16);
	auto rightRight = std::make_shared<Node>(27);
	auto right = std::make_shared<Node>(17, rightLeft, rightRight);

	auto root = std::make_shared<Node>(14, left, right);

	std::cout << std::boolalpha;
	std::cout << IsValidBinarySearchTree(root) << "\n";

	root->value = 1;
	std::cout << IsValidBinarySearchTree(root) << "\n";

	std::cin.get();

	return 0;
}