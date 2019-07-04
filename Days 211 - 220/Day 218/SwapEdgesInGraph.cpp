#include <algorithm>
#include <cstdlib>
#include <initializer_list>
#include <iostream>
#include <utility>
#include <vector>

class Graph
{
private:
	using Node = char;
	using Edge = std::pair<Node, Node>;

	std::vector<Node> m_nodes;
	std::vector<Edge> m_edges;

public:
	Graph(const std::initializer_list<Node>& nodes, const std::initializer_list<Edge>& edges) noexcept
		: m_nodes(nodes), m_edges(edges)
	{ }

	void SwapEdges() noexcept
	{
		for (auto& edge : m_edges)
		{
			SwapEdge(edge);
		}
	}

	inline const std::vector<Edge>& GetEdges() const noexcept{ return m_edges; }

private:
	inline void SwapEdge(Edge& edge) noexcept {	std::swap(edge.first, edge.second); }
};

template <typename T, typename U>
std::ostream& operator <<(std::ostream& outputStream, const std::pair<T, U>& pair) noexcept
{
	outputStream << "( " << pair.first << ", " << pair.second << " )";

	return outputStream;
}

template <typename T>
std::ostream& operator <<(std::ostream& outputStream, const std::vector<T>& vector) noexcept
{
	for (const auto& value : vector)
	{
		outputStream << value << " ";
	}

	return outputStream;
}

int main(int argc, char* argv[])
{
	Graph graph({ 'A', 'B', 'C' }, { { 'A', 'B' }, { 'B', 'C' } });
	std::cout << graph.GetEdges() << "\n";

	graph.SwapEdges();
	std::cout << graph.GetEdges() << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}