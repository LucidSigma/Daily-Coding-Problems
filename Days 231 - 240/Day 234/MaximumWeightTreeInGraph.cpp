#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <deque>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using Node = char;

struct NodeEdge
{
	Node target;
	unsigned int weight;
};

inline bool operator ==(const NodeEdge& lhs, const NodeEdge& rhs) noexcept
{
	return lhs.target == rhs.target && lhs.weight == rhs.weight;
}

template <>
struct std::hash<NodeEdge>
{
	inline size_t operator ()(const NodeEdge& nodeEdge) const noexcept
	{
		return std::hash<Node>()(nodeEdge.target) ^ std::hash<unsigned int>()(nodeEdge.weight);
	}
};

class Graph
{
private:
	std::unordered_set<Node> m_nodes;
	std::unordered_map<Node, std::unordered_set<NodeEdge>> m_edges;

public:
	Graph() = default;

	Graph(const std::initializer_list<Node>& nodes, const std::initializer_list<std::tuple<Node, Node, unsigned int>>& edges) noexcept
	{
		AddNodes(nodes);
		AddEdges(edges);
	}

	~Graph() noexcept = default;

	void AddNodes(const std::initializer_list<Node>& nodes) noexcept
	{
		for (const auto node : nodes)
		{
			m_nodes.insert(node);
			m_edges[node] = std::unordered_set<NodeEdge>();
		}
	}

	void AddEdges(const std::initializer_list<std::tuple<Node, Node, unsigned int>>& edges) noexcept
	{
		for (const auto [source, target, weight] : edges)
		{
			m_edges[source].insert({ target, weight });
			m_edges[target].insert({ source, weight });
		}
	}

	unsigned int MaxWeightSpanningTree() noexcept
	{
		std::deque<Node> remainingNodes;

		for (const auto node : m_nodes)
		{
			remainingNodes.push_back(node);
		}

		const Node firstNode = remainingNodes[0];
		remainingNodes.pop_front();

		const unsigned int maxWeight = MaxWeightSpanningTreeHelper(firstNode, remainingNodes, 0);

		return maxWeight;
	}

private:
	unsigned int MaxWeightSpanningTreeHelper(const Node firstNode, const std::deque<Node>& remainingNodes, const unsigned int currentWeight) noexcept
	{
		if (remainingNodes.empty())
		{
			return currentWeight;
		}

		std::vector<unsigned int> weights;

		for (const auto [target, weight] : m_edges[firstNode])
		{
			if (const auto targetLocation = std::find(std::cbegin(remainingNodes), std::cend(remainingNodes), target);
				targetLocation != std::cend(remainingNodes))
			{
				auto currentNodes = remainingNodes;
				currentNodes.erase(targetLocation);

				weights.push_back(MaxWeightSpanningTreeHelper(target, currentNodes, currentWeight + weight));
			}
		}

		return *std::max_element(std::cbegin(weights), std::cend(weights));
	}
};

int main(int argc, char* argv[])
{
	Graph graph;
	graph.AddNodes({ 'A', 'B', 'C', 'D', 'E' });
	graph.AddEdges(
		{
			{ 'A', 'B', 2 },
			{ 'A', 'D', 5 },
			{ 'B', 'C', 10 },
			{ 'B', 'D', 14 },
			{ 'B', 'E', 9 },
			{ 'C', 'E', 7 },
			{ 'D', 'E', 19 }
		}
	);

	std::cout << graph.MaxWeightSpanningTree() << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}