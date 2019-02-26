#include <algorithm>
#include <array>
#include <iostream>
#include <numeric>

template <unsigned int Size>
bool CanUniquelyColourAdjacentVertices(const std::array<std::array<unsigned int, Size>, Size>& adjacencyMatrix, unsigned int colours) noexcept
{
	unsigned int maxAdjacencies = 0;

	for (const auto& row : adjacencyMatrix)
	{
		unsigned int sum = std::accumulate(row.cbegin(), row.cend(), 0);
		maxAdjacencies = std::max(maxAdjacencies, sum);
	}

	return colours > maxAdjacencies;
}

int main(int argc, char* argv[])
{
	std::array<std::array<unsigned int, 5>, 5> adjacencyMatrix
	{
		std::array<unsigned int, 5> { 0, 0, 1, 1, 0 },
		std::array<unsigned int, 5> { 0, 0, 1, 1, 1 },
		std::array<unsigned int, 5> { 1, 1, 0, 1, 0 },
		std::array<unsigned int, 5> { 1, 1, 1, 0, 1 },
		std::array<unsigned int, 5> { 0, 1, 0, 1, 0 }
	};

	std::cout << std::boolalpha;
	std::cout << CanUniquelyColourAdjacentVertices(adjacencyMatrix, 5);

	std::cin.get();

	return 0;
}