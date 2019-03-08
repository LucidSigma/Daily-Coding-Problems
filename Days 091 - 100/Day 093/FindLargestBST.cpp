#include <iostream>
#include <limits>
#include <memory>
#include <utility>

struct Node
{
	int value;
	std::shared_ptr<Node> left;
	std::shared_ptr<Node> right;

	explicit Node(int value, std::shared_ptr<Node> left = nullptr, std::shared_ptr<Node> right = nullptr) noexcept
		: value(value), left(left), right(right)
	{ }
};

struct LargetsBSTData
{
	bool isBST;
	std::shared_ptr<Node> node;
	unsigned int nodeCount;
	int minValue;
	int maxValue;
};

LargetsBSTData GetLargestBSTHelper(const std::shared_ptr<Node>& node) noexcept
{
	if (node == nullptr)
	{
		return { true, node, 0, std::numeric_limits<int>::min(), std::numeric_limits<int>::max() };
	}

	if (node->left == nullptr || node->right == nullptr)
	{
		return { true, node, 1, node->value, node->value };
	}

	auto[leftIsBST, leftNode, leftNodeCount, leftMinValue, leftMaxValue] = GetLargestBSTHelper(node->left);
	auto[rightIsBST, rightNode, rightNodeCount, rightMinValue, rightMaxValue] = GetLargestBSTHelper(node->right);

	if (leftIsBST && rightIsBST)
	{
		if (node->left != nullptr && node->right != nullptr)
		{
			if (node->value >= leftMaxValue && node->value <= rightMaxValue)
			{
				return { true, node, leftNodeCount + rightNodeCount + 1, leftMinValue, rightMaxValue };
			}
			else if (node->left != nullptr && node->value >= leftMaxValue)
			{
				return { true, node, leftNodeCount + 1, leftMinValue, node->value };
			}
			else if (node->right != nullptr && node->value >= rightMinValue)
			{
				return { true, node, leftNodeCount + 1, node->value, rightMaxValue };
			}
		}
	}

	if (leftNodeCount > rightNodeCount)
	{
		return { false, leftNode, leftNodeCount, leftMinValue, node->value };
	}
	else
	{
		return { false, rightNode, rightNodeCount, node->value, rightMaxValue };
	}
}

std::pair<std::shared_ptr<Node>, unsigned int> GetLargestBST(const std::shared_ptr<Node>& root) noexcept
{
	auto[_, largestBST, nodeCount, __, ___] = GetLargestBSTHelper(root);

	return { largestBST, nodeCount };
}

int main(int argc, char* argv[])
{
	auto leftLeft = std::make_shared<Node>(3);
	auto leftRight = std::make_shared<Node>(7);
	auto left = std::make_shared<Node>(4, leftLeft, leftRight);
	
	auto rightRight = std::make_shared<Node>(9);
	auto rightLeft = std::make_shared<Node>(15);
	auto right = std::make_shared<Node>(12, rightLeft, rightRight);
	
	auto root = std::make_shared<Node>(10, left, right);

	auto[largestBST, largestBSTSize] = GetLargestBST(root);

	std::cout << "Largest BST is node " << largestBST->value << ".\n";
	std::cout << "It has a size of " << largestBSTSize << ".\n";

	root->value = 2;

	auto[modifiedLargestBST, modifedLargestBSTSize] = GetLargestBST(root);

	std::cout << "\nLargest BST is node " << modifiedLargestBST->value << ".\n";
	std::cout << "It has a size of " << modifedLargestBSTSize << ".\n";

	std::cin.get();

	return 0;
}