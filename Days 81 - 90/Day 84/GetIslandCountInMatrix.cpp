#include <array>
#include <cstddef>
#include <iostream>
#include <unordered_set>
#include <utility>

template <unsigned int N>
using MatrixRow = std::array<unsigned int, N>;

template <unsigned int M, unsigned int N>
using Matrix = std::array<MatrixRow<M>, N>;

using Coordinate = std::pair<unsigned int, unsigned int>;
using CoordinateSet = std::unordered_set<Coordinate>;

template <>
struct std::hash<Coordinate>
{
	inline std::size_t operator ()(const Coordinate& pair) const noexcept
	{
		return std::hash<unsigned int>()(pair.first) + std::hash<unsigned int>()(pair.second);
	}
};

template <unsigned int M, unsigned int N>
bool AddIsland(unsigned int x, unsigned int y, const Matrix<M, N>& islandMap, CoordinateSet& visited) noexcept
{
	const Coordinate currentCoordinate = std::make_pair(x, y);

	if (visited.find(currentCoordinate) != visited.end())
	{
		return false;
	}

	visited.insert(currentCoordinate);

	if (x > 0 && islandMap[x - 1][y] == 1)
	{
		AddIsland(x - 1, y, islandMap, visited);
	}

	if (x < islandMap.size() - 1 && islandMap[x + 1][y] == 1)
	{
		AddIsland(x + 1, y, islandMap, visited);
	}

	if (y > 0 && islandMap[x][y - 1] == 1)
	{
		AddIsland(x, y - 1, islandMap, visited);
	}

	if (y < islandMap[0].size() - 1 && islandMap[x][y + 1] == 1)
	{
		AddIsland(x, y + 1, islandMap, visited);
	}

	return true;
}

template <unsigned int M, unsigned int N>
unsigned int IslandCount(const Matrix<M, N>& islandMap) noexcept
{
	unsigned int count = 0;
	CoordinateSet visited;

	for (unsigned int i = 0; i < islandMap.size(); i++)
	{
		for (unsigned int j = 0; j < islandMap[i].size(); j++)
		{
			if (islandMap[i][j] == 1)
			{
				count += AddIsland(i, j, islandMap, visited);
			}
		}
	}

	return count;
}

int main(int argc, char* argv[])
{
	const Matrix<5, 6> islandMap
	{
		MatrixRow<5> { 1, 0, 0, 0, 0 },
		MatrixRow<5> { 0, 0, 1, 1, 0 },
		MatrixRow<5> { 0, 1, 1, 0, 0 },
		MatrixRow<5> { 0, 0, 0, 0, 0 },
		MatrixRow<5> { 1, 1, 0, 0, 1 },
		MatrixRow<5> { 1, 1, 0, 0, 1 }
	};

	std::cout << IslandCount(islandMap) << "\n";

	std::cin.get();

	return 0;
}