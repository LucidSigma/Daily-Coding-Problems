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

void MergeBinaryTreesHelper(const std::shared_ptr<Node>& treeA, const std::shared_ptr<Node>& treeB, const std::shared_ptr<Node>& previousNode, const bool isLeftMerge)
{
	if (treeA == nullptr && treeB == nullptr)
	{
		return;
	}

	if (treeA != nullptr && treeB != nullptr)
	{
		const auto currentNode = std::make_shared<Node>(treeA->value + treeB->value);
		(isLeftMerge ? previousNode->left : previousNode->right) = currentNode;

		MergeBinaryTreesHelper(treeA->left, treeB->left, currentNode, true);
		MergeBinaryTreesHelper(treeA->right, treeB->right, currentNode, false);

		return;
	}

	if (const auto node = treeA != nullptr ? treeA : treeB;
		isLeftMerge)
	{
		previousNode->left = node;
	}
	else
	{
		previousNode->right = node;
	}
}

std::shared_ptr<Node> MergeBinaryTrees(const std::shared_ptr<Node>& treeA, const std::shared_ptr<Node>& treeB)
{
	const std::shared_ptr<Node> mergedTree(0);

	MergeBinaryTreesHelper(treeA, treeB, mergedTree, true);

	return mergedTree;
}

std::ostream& operator <<(std::ostream& outputStream, const std::shared_ptr<Node>& node)
{
	if (node == nullptr)
	{
		outputStream << "-";
	}
	else
	{
		outputStream << node->value << " " << node->left << " " << node->right;
	}

	return outputStream;
}

int main(const int argc, const char* const argv[])
{
	const auto leftA = std::make_shared<Node>(2);
	const auto rightA = std::make_shared<Node>(3);
	const auto rootA = std::make_shared<Node>(1, leftA, rightA);

	const auto leftB = std::make_shared<Node>(5);
	const auto rightB = std::make_shared<Node>(6);
	const auto rootB = std::make_shared<Node>(4, leftB, rightB);

	std::cout << MergeBinaryTrees(rootA, rootB) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}