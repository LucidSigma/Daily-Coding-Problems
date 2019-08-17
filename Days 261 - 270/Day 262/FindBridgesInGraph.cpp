#include <cstdlib>
#include <initializer_list>
#include <iostream>
#include <unordered_set>
#include <utility>
#include <vector>

class Graph
{
private:
	using Node = char;
	using Edge = std::pair<Node, Node>;

	std::vector<Edge> m_edges;

public:
	Graph(const std::initializer_list<Edge>& edges)
		: m_edges(edges)
	{ }

	std::vector<Edge> GetBridges() const
	{
		std::vector<Edge> bridges;
		const auto nodes = GetNodes();

		for (const auto& edge : m_edges)
		{
			const auto nodesWithoutCurrentEdge = GetNodesWithoutEdge(edge);

			if (nodesWithoutCurrentEdge != nodes)
			{
				bridges.push_back(edge);
			}
		}

		return bridges;
	}

private:
	std::unordered_set<Node> GetNodes() const
	{
		std::unordered_set<Node> nodes;

		for (const auto [source, destination] : m_edges)
		{
			nodes.insert(source);
			nodes.insert(destination);
		}

		return nodes;
	}

	std::unordered_set<Node> GetNodesWithoutEdge(const Edge& removedEdge) const
	{
		std::unordered_set<Node> nodes;

		for (const auto& edge : m_edges)
		{
			if (edge == removedEdge)
			{
				continue;
			}

			const auto [source, destination] = edge;

			nodes.insert(source);
			nodes.insert(destination);
		}

		return nodes;
	}
};

template <typename T, typename U>
inline std::ostream& operator <<(std::ostream& outputStream, const std::pair<T, U>& pair)
{
	outputStream << "( " << pair.first << ", " << pair.second << " )";
	
	return outputStream;
}

template <typename T>
std::ostream& operator <<(std::ostream& outputStream, const std::vector<T>& values)
{
	for (const auto& value : values)
	{
		outputStream << value << " ";
	}

	return outputStream;
}

int main(int argc, char* argv[])
{
	const Graph graph({
		{ 'A', 'B' },
		{ 'A', 'C' },
		{ 'C', 'D' },
		{ 'B', 'E' },
		{ 'B', 'F' },
		{ 'F', 'G' },
		{ 'F', 'H' }
	});

	std::cout << graph.GetBridges() << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}