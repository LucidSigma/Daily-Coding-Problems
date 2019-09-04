#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <memory>
#include <unordered_set>
#include <vector>

struct Node
{
	char value;
	std::unordered_set<std::shared_ptr<Node>> adjacentNodes;

	explicit Node(const char value, const std::unordered_set<std::shared_ptr<Node>>& adjacentNodes = { })
		: value(value), adjacentNodes(adjacentNodes)
	{ }
};

template <>
struct std::hash<Node>
{
	inline size_t operator ()(const Node& node) const noexcept
	{
		return std::hash<char>()(node.value) ^ (std::hash<size_t>()(node.adjacentNodes.size()) << 1);
	}
};

class Graph
{
private:
	std::unordered_set<std::shared_ptr<Node>> m_nodes;

public:
	explicit Graph(const std::initializer_list<std::shared_ptr<Node>>& nodes)
		: m_nodes(nodes)
	{ }

	bool HasCycle() const
	{
		const auto firstNode = *std::cbegin(m_nodes);
		std::unordered_set<std::shared_ptr<Node>> unvisitedNodes = m_nodes;

		return HasCycleHelper(firstNode, { }, unvisitedNodes);
	}

private:
	bool HasCycleHelper(const std::shared_ptr<Node>& node, const std::vector<std::shared_ptr<Node>>& currentPath, std::unordered_set<std::shared_ptr<Node>>& unvisitedNodes) const
	{
		if (unvisitedNodes.find(node) != std::cend(unvisitedNodes))
		{
			unvisitedNodes.erase(node);
		}

		for (const auto& adjacentNode : node->adjacentNodes)
		{
			if (std::find(std::cbegin(currentPath), std::cend(currentPath), adjacentNode) != std::cend(currentPath) && adjacentNode != currentPath.back())
			{
				return true;
			}

			if (!unvisitedNodes.empty())
			{
				auto newPath = currentPath;
				newPath.push_back(node);

				return HasCycleHelper(adjacentNode, newPath, unvisitedNodes);
			}
		}

		return false;
	}
};

int main(int argc, char* argv[])
{
	auto nodeA = std::make_shared<Node>('A');
	const auto nodeB = std::make_shared<Node>('B', std::unordered_set<std::shared_ptr<Node>>{ nodeA });
	const auto nodeC = std::make_shared<Node>('C', std::unordered_set<std::shared_ptr<Node>>{ nodeB });
	const auto nodeD = std::make_shared<Node>('D', std::unordered_set<std::shared_ptr<Node>>{ nodeC });
	nodeA->adjacentNodes = { nodeD };

	Graph graph({ nodeA, nodeB, nodeC, nodeD });

	std::cout << std::boolalpha;
	std::cout << graph.HasCycle() << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}