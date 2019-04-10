#include <iostream>
#include <iterator>
#include <memory>
#include <vector>

struct Node
{
	int value;

	std::shared_ptr<Node> left;
	std::shared_ptr<Node> right;
	std::shared_ptr<Node> parent = nullptr;

	explicit Node(const int value, const std::shared_ptr<Node>& left = nullptr, const std::shared_ptr<Node>& right = nullptr) noexcept
		: value(value), left(left), right(right)
	{ }
};

std::vector<std::shared_ptr<Node>> GetInorderVectorOfNodesFromTree(const std::shared_ptr<Node>& root) noexcept
{
	std::vector<std::shared_ptr<Node>> nodeVector { root };

	if (root->left != nullptr)
	{
		const auto leftInorder = GetInorderVectorOfNodesFromTree(root->left);
		nodeVector.insert(std::cbegin(nodeVector), std::cbegin(leftInorder), std::cend(leftInorder));
	}

	if (root->right != nullptr)
	{
		const auto rightInorder = GetInorderVectorOfNodesFromTree(root->right);
		nodeVector.insert(std::cend(nodeVector), std::cbegin(rightInorder), std::cend(rightInorder));
	}

	return nodeVector;
}

std::shared_ptr<Node> FindInorderSuccessor(const std::shared_ptr<Node>& node) noexcept
{
	auto treeRoot = node;

	while (treeRoot->parent != nullptr)
	{
		treeRoot = treeRoot->parent;
	}

	const auto inorderNodes = GetInorderVectorOfNodesFromTree(treeRoot);

	for (unsigned int i = 0; i < inorderNodes.size(); i++)
	{
		if (inorderNodes[i] == node)
		{
			return i == inorderNodes.size() - 1 ? nullptr : inorderNodes[i + 1];
		}
	}

	return nullptr;
}

int main(int argc, char* argv[])
{
	auto node35 = std::make_shared<Node>(35);
	auto node22 = std::make_shared<Node>(22);
	auto node30 = std::make_shared<Node>(30, node22, node35);
	auto node05 = std::make_shared<Node>(5);
	auto node10 = std::make_shared<Node>(10, node05, node30);

	node05->parent = node10;
	node30->parent = node10;
	node22->parent = node30;
	node35->parent = node30;

	std::cout << FindInorderSuccessor(node22)->value << "\n";

	std::cin.get();

	return 0;
}