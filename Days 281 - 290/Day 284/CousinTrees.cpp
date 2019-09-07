#include <cstdlib>
#include <iostream>
#include <iterator>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <vector>

struct Node
{
	int value;
	unsigned int level = 0;

	std::shared_ptr<Node> left;
	std::shared_ptr<Node> right;
	std::shared_ptr<Node> parent = nullptr;

	explicit Node(const int value, const std::shared_ptr<Node>& left = nullptr, const std::shared_ptr<Node>& right = nullptr)
		: value(value), left(left), right(right)
	{ }
};

void GetCousinTreesHelper(const std::shared_ptr<Node>& node, std::unordered_map<unsigned int, std::unordered_set<std::shared_ptr<Node>>>& nodeLevels, const std::shared_ptr<Node>& parent, const unsigned int currentLevel)
{
	if (node == nullptr)
	{
		return;
	}

	node->parent = parent;
	node->level = currentLevel;

	if (nodeLevels.find(currentLevel) == std::cend(nodeLevels))
	{
		nodeLevels[currentLevel] = { };
	}

	nodeLevels[currentLevel].insert(node);

	GetCousinTreesHelper(node->left, nodeLevels, node, currentLevel + 1);
	GetCousinTreesHelper(node->right, nodeLevels, node, currentLevel + 1);
}

std::vector<std::shared_ptr<Node>> GetCousinTrees(const std::shared_ptr<Node>& tree, const std::shared_ptr<Node>& node)
{
	std::unordered_map<unsigned int, std::unordered_set<std::shared_ptr<Node>>> nodeLevels;
	std::vector<std::shared_ptr<Node>> cousinTrees;

	GetCousinTreesHelper(tree, nodeLevels, nullptr, 0);

	for (const auto& subNode : nodeLevels[node->level])
	{
		if (subNode->parent != node->parent)
		{
			cousinTrees.push_back(subNode);
		}
	}

	return cousinTrees;
}

std::ostream& operator <<(std::ostream& outputStream, const std::shared_ptr<Node>& node)
{
	if (node == nullptr)
	{
		outputStream << "- ";
	}
	else
	{
		outputStream << node->value << " " << node->left << " " << node->right;
	}

	return outputStream;
}

template <typename T>
std::ostream& operator <<(std::ostream& outputStream, const std::vector<T>& values)
{
	for (const auto& value : values)
	{
		outputStream << value << "\n";
	}

	return outputStream;
}

int main(int argc, char* argv[])
{
	const auto node6 = std::make_shared<Node>(6);
	const auto node5 = std::make_shared<Node>(5);
	const auto node4 = std::make_shared<Node>(4);

	const auto node3 = std::make_shared<Node>(3, nullptr, node6);
	const auto node2 = std::make_shared<Node>(2, node4, node5);

	const auto node1 = std::make_shared<Node>(1, node2, node3);

	std::cout << GetCousinTrees(node1, node2) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}