#include <iostream>
#include <memory>

struct Node
{
	bool value;

	std::shared_ptr<Node> left;
	std::shared_ptr<Node> right;

	explicit Node(const bool value, const std::shared_ptr<Node>& left = nullptr, const std::shared_ptr<Node>& right = nullptr) noexcept
		: value(value), left(left), right(right)
	{ }
};

bool IsZeroSubtree(const std::shared_ptr<Node>& node) noexcept
{
	if (node == nullptr)
	{
		return true;
	}

	if (node->value)
	{
		return false;
	}

	return IsZeroSubtree(node->left) && IsZeroSubtree(node->right);
}

void PruneBinaryTreeOfZeroSubtrees(std::shared_ptr<Node>& root) noexcept
{
	if (root == nullptr)
	{
		return;
	}

	if (IsZeroSubtree(root->left))
	{
		root->left = nullptr;
	}
	else
	{
		PruneBinaryTreeOfZeroSubtrees(root->left);
	}

	if (IsZeroSubtree(root->right))
	{
		root->right = nullptr;
	}
	else
	{
		PruneBinaryTreeOfZeroSubtrees(root->right);
	}
}

void PrintBinaryTreeHelper(const std::shared_ptr<Node>& node) noexcept
{
	if (node == nullptr)
	{
		std::cout << "- ";
	}
	else
	{
		std::cout << node->value << " ";

		PrintBinaryTreeHelper(node->left);
		PrintBinaryTreeHelper(node->right);
	}
}

void PrintBinaryTree(const std::shared_ptr<Node>& root) noexcept
{
	PrintBinaryTreeHelper(root);
	std::cout << "\n";
}

int main(int argc, char* argv[])
{
	auto rightLeftLeft = std::make_shared<Node>(0);
	auto rightLeftRight = std::make_shared<Node>(0);

	auto rightLeft = std::make_shared<Node>(1, rightLeftLeft, rightLeftRight);
	auto rightRight = std::make_shared<Node>(0);

	auto right = std::make_shared<Node>(0, rightLeft, rightRight);
	auto left = std::make_shared<Node>(1);

	auto root = std::make_shared<Node>(0, left, right);

	PrintBinaryTree(root);

	PruneBinaryTreeOfZeroSubtrees(root);

	PrintBinaryTree(root);

	std::cin.get();

	return 0;
}
