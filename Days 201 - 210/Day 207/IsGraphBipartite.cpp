#include <algorithm>
#include <array>
#include <cstddef>
#include <iostream>
#include <iterator>

template <std::size_t Size>
using Graph = std::array<std::array<unsigned int, Size>, Size>;

static constexpr int NullColour = -1;

template <std::size_t Size>
bool IsBipartiteGraphHelper(const Graph<Size>& graph, std::array<int, Size>& graphColouring, const std::size_t currentPosition, const int colour) noexcept
{
	if (graphColouring[currentPosition] != NullColour && graphColouring[currentPosition != colour])
	{
		return false;
	}

	graphColouring[currentPosition] = colour;
	bool isBipartite = true;

	for (std::size_t i = 0; i < Size; ++i)
	{
		if (graph[currentPosition][i] != 0)
		{
			if (graphColouring[i] == NullColour)
			{
				isBipartite &= IsBipartiteGraphHelper(graph, graphColouring, i, 1 - colour);
			}

			if (graphColouring[i] != NullColour && graphColouring[i] != 1 - colour)
			{
				return false;
			}
		}

		if (!isBipartite)
		{
			return false;
		}
	}

	return true;
}

template <std::size_t Size>
inline bool IsBipartiteGraph(const Graph<Size>& graph) noexcept
{
	std::array<int, Size> graphColouring;
	std::fill(std::begin(graphColouring), std::end(graphColouring), NullColour);

	return IsBipartiteGraphHelper(graph, graphColouring, 0, 1);
}

int main(int argc, char* argv[])
{
	const Graph<5> graph
	{
		std::array<unsigned int, 5>{ 0, 1, 0, 1, 0 },
		std::array<unsigned int, 5>{ 1, 0, 1, 0, 1 },
		std::array<unsigned int, 5>{ 0, 1, 0, 1, 0 },
		std::array<unsigned int, 5>{ 1, 0, 1, 0, 1 },
		std::array<unsigned int, 5>{ 0, 1, 0, 1, 0 }
	};

	std::cout << std::boolalpha;
	std::cout << IsBipartiteGraph(graph) << "\n";

	std::cin.get();

	return 0;
}