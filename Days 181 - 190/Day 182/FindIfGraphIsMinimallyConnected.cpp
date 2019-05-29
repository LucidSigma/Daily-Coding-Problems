#include <iostream>
#include <iterator>
#include <unordered_set>
#include <utility>
#include <vector>

using Node = char;
using Adjacency = std::pair<Node, Node>;

bool IsGraphMinimallyConnected(const std::vector<Adjacency>& adjacencyList) noexcept
{
	std::unordered_set<Node> nodes;

	for (const auto [leftNode, rightNode] : adjacencyList)
	{
		if (nodes.find(leftNode) == std::cend(nodes))
		{
			nodes.insert(leftNode);
		}

		if (nodes.find(rightNode) == std::cend(nodes))
		{
			nodes.insert(rightNode);
		}
	}

	const unsigned int uniqueNodeCount = nodes.size();
	const unsigned int edgeCount = adjacencyList.size();

	return uniqueNodeCount == edgeCount + 1;
}

int main(int argc, char* argv[])
{
	std::vector<Adjacency> adjacencyList
	{
		Adjacency{ 'A', 'B' },
		Adjacency{ 'A', 'C' },
		Adjacency{ 'B', 'D' },
		Adjacency{ 'C', 'E' }
	};

	std::cout << std::boolalpha;
	std::cout << IsGraphMinimallyConnected(adjacencyList) << "\n";

	adjacencyList.emplace_back('B', 'C');

	std::cout << IsGraphMinimallyConnected(adjacencyList) << "\n";

	std::cin.get();

	return 0;
}