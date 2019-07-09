#include <cstdlib>
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

void PrintInorder(const std::shared_ptr<Node>& root) noexcept
{
	if (root->left != nullptr)
	{
		PrintInorder(root->left);
	}

	std::cout << root->value << " ";

	if (root->right != nullptr)
	{
		PrintInorder(root->right);
	}
}

int main(int argc, char* argv[])
{
	const auto leftLeft = std::make_shared<Node>(4);
	const auto leftRight = std::make_shared<Node>(5);
	const auto rightLeft= std::make_shared<Node>(6);
	const auto rightRight = std::make_shared<Node>(7);

	const auto left= std::make_shared<Node>(2, leftLeft, leftRight);
	const auto right = std::make_shared<Node>(3, rightLeft, rightRight);

	const auto root = std::make_shared<Node>(1, left, right);

	PrintInorder(root);

	std::cin.get();

	return EXIT_SUCCESS;
}