#include <iostream>
#include <iterator>
#include <memory>
#include <unordered_map>
#include <utility>
#include <vector>

struct Node
{
	int value;

	std::shared_ptr<Node> left;
	std::shared_ptr<Node> right;

	explicit Node(const int value, const std::shared_ptr<Node>& left = nullptr, const std::shared_ptr<Node>& right = nullptr) noexcept
		: value(value), left(left), right(right)
	{ }
};

using NodePair = std::pair<std::shared_ptr<Node>, std::shared_ptr<Node>>;

void GetNodesFromTreeHelper(const std::shared_ptr<Node>& node, std::vector<std::shared_ptr<Node>>& nodes) noexcept
{
	nodes.push_back(node);

	if (node->left != nullptr)
	{
		GetNodesFromTreeHelper(node->left, nodes);
	}

	if (node->right != nullptr)
	{
		GetNodesFromTreeHelper(node->right, nodes);
	}
}

std::vector<std::shared_ptr<Node>> GetNodesFromTree(const std::shared_ptr<Node>& root) noexcept
{
	std::vector<std::shared_ptr<Node>> nodes;
	GetNodesFromTreeHelper(root, nodes);

	return nodes;
}

NodePair GetTwoNodesForSum(const std::shared_ptr<Node>& root, const int target) noexcept
{
	const auto nodes = GetNodesFromTree(root);
	std::unordered_multimap<int, std::shared_ptr<Node>> processedValues;

	for (const auto& node : nodes)
	{
		if (const auto differenceLocation = processedValues.find(target - node->value);
			differenceLocation != std::cend(processedValues))
		{
			return { node, differenceLocation->second };
		}

		processedValues.insert({ node->value, node });
	}

	return { nullptr, nullptr };
}

void PrintNodePair(const NodePair& nodePair) noexcept
{
	if (nodePair.first == nullptr || nodePair.second == nullptr)
	{
		std::cout << "Pointers are null.\n";
	}
	else
	{
		std::cout << nodePair.first->value << ", " << nodePair.second->value << "\n";
	}
}

int main(int argc, char* argv[])
{
	const auto rightLeft = std::make_shared<Node>(11);
	const auto rightRight = std::make_shared<Node>(15);
	const auto right = std::make_shared<Node>(15, rightLeft, rightRight);
	const auto left = std::make_shared<Node>(5);
	const auto root = std::make_shared<Node>(10, left, right);

	PrintNodePair(GetTwoNodesForSum(root, 20));
	PrintNodePair(GetTwoNodesForSum(root, 16));
	PrintNodePair(GetTwoNodesForSum(root, 30));
	PrintNodePair(GetTwoNodesForSum(root, 5));

	std::cin.get();

	return 0;
}