#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <memory>
#include <vector>

struct Node;

using NodeWeight = std::pair<std::shared_ptr<Node>, unsigned int>;

struct Node
{
	char value;
	unsigned int heaviestPath = 0;

	std::vector<NodeWeight> children;

	explicit Node(const char value, const std::initializer_list<NodeWeight>& children = { }) noexcept
		: value(value), children(children)
	{ }
};

void UpdateTreeHeaviestPaths(const std::shared_ptr<Node>& node) noexcept
{
	if (node->children.empty())
	{
		node->heaviestPath = 0;

		return;
	}

	std::vector<unsigned int> nodePaths;

	for (const auto [child, weight] : node->children)
	{
		UpdateTreeHeaviestPaths(child);
		nodePaths.push_back(child->heaviestPath + weight);
	}

	node->heaviestPath = *std::max_element(std::cbegin(nodePaths), std::cend(nodePaths));
}

unsigned int GetHeaviestPathHelper(const std::shared_ptr<Node>& node) noexcept
{
	if (node->children.empty())
	{
		return 0;
	}

	std::vector<unsigned int> aggregateWeights;
	std::vector<unsigned int> childrenLengths;

	for (const auto [child, weight] : node->children)
	{
		aggregateWeights.push_back(child->heaviestPath + weight);
		childrenLengths.push_back(GetHeaviestPathHelper(child));
	}

	unsigned int maxChildPathLength = *std::max_element(std::cbegin(childrenLengths), std::cend(childrenLengths));
	std::sort(std::begin(aggregateWeights), std::end(aggregateWeights));

	return std::max(aggregateWeights.back() + *(std::cend(aggregateWeights) - 2), maxChildPathLength);
}

inline unsigned int GetHeaviestPath(const std::shared_ptr<Node>& root) noexcept
{
	return UpdateTreeHeaviestPaths(root), GetHeaviestPathHelper(root);
}

int main(int argc, char* argv[])
{
	const auto nodeH = std::make_shared<Node>('h');
	const auto nodeG = std::make_shared<Node>('g');

	const auto nodeF = std::make_shared<Node>('f');
	const auto nodeE = std::make_shared<Node>('e', std::initializer_list<NodeWeight>{ { nodeG, 1 }, { nodeH, 1 } });

	const auto nodeD = std::make_shared<Node>('d', std::initializer_list<NodeWeight>{ { nodeE, 2 }, { nodeF, 4 } });
	const auto nodeC = std::make_shared<Node>('c');
	const auto nodeB = std::make_shared<Node>('b');

	const auto nodeA = std::make_shared<Node>('a', std::initializer_list<NodeWeight>{ { nodeB, 3 }, { nodeC, 5 }, { nodeD, 8 } });

	std::cout << GetHeaviestPath(nodeA) << "\n";

	std::cin.get();

	return 0;
}