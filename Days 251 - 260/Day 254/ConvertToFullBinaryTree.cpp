#include <cstdlib>
#include <iostream>
#include <memory>

struct Node
{
	int value;

	std::shared_ptr<Node> left;
	std::shared_ptr<Node> right;

	explicit Node(const int value, const std::shared_ptr<Node>& left = nullptr, const std::shared_ptr<Node>& right = nullptr)
		: value(value), left(left), right(right)
	{ }
};

std::shared_ptr<Node> ConvertToFullTree(const std::shared_ptr<Node>& node)
{
	if (node->left == nullptr && node->right == nullptr)
	{
		return node;
	}

	if (node->left != nullptr && node->right == nullptr)
	{
		return ConvertToFullTree(node->left);
	}

	if (node->left == nullptr && node->right != nullptr)
	{
		return ConvertToFullTree(node->right);
	}

	node->left = ConvertToFullTree(node->left);
	node->right = ConvertToFullTree(node->right);

	return node;
}

std::ostream& operator <<(std::ostream& outputStream, const std::shared_ptr<Node>& node)
{
	if (node == nullptr)
	{
		outputStream << "- ";
	}
	else
	{
		outputStream << node->value << " " << node->left << node->right;
	}

	return outputStream;
}

int main(int argc, char* argv[])
{
	const auto leftLeftRight = std::make_shared<Node>(5);
	const auto rightRightLeft= std::make_shared<Node>(6);
	const auto rightRightRight = std::make_shared<Node>(7);

	const auto leftLeft = std::make_shared<Node>(3, nullptr, leftLeftRight);
	const auto rightRight = std::make_shared<Node>(4, rightRightLeft, rightRightRight);

	const auto left = std::make_shared<Node>(1, leftLeft);
	const auto right = std::make_shared<Node>(2, nullptr, rightRight);

	const auto root = std::make_shared<Node>(0, left, right);

	std::cout << root << "\n";
	std::cout << ConvertToFullTree(root) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}