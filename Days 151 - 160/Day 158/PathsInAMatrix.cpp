#include <array>
#include <iostream>
#include <iterator>
#include <unordered_set>
#include <utility>
#include <vector>

template <unsigned int M, unsigned int N>
using Matrix = std::array<std::array<bool, M>, N>;

using Coordinate = std::pair<unsigned int, unsigned int>;

template <>
struct std::hash<Coordinate>
{
	inline std::size_t operator ()(const Coordinate& coordinate) const noexcept
	{
		return std::hash<unsigned int>()(coordinate.first) ^ std::hash<unsigned int>()(coordinate.second);
	}
};

std::vector<Coordinate> GetNeighbourCells(const Coordinate& currentCoordinate, const unsigned int rows, const unsigned int columns) noexcept
{
	std::vector<Coordinate> neighbourCells;
	const auto[x, y] = currentCoordinate;

	if (x > 0)
	{
		neighbourCells.emplace_back(x - 1, y);
	}

	if (x < rows - 1)
	{
		neighbourCells.emplace_back(x + 1, y);
	}

	if (y > 0)
	{
		neighbourCells.emplace_back(x, y - 1);
	}

	if (y < columns - 1)
	{
		neighbourCells.emplace_back(x, y + 1);
	}

	return neighbourCells;
}

template <unsigned int M, unsigned int N>
unsigned int GetAllPathsHelper(const Matrix<M, N>& matrix, const Coordinate& currentCoordinate, std::unordered_set<Coordinate> currentPath) noexcept
{
	if (currentCoordinate == std::make_pair(N - 1, M - 1))
	{
		return 1;
	}

	const auto neighbourCells = GetNeighbourCells(currentCoordinate, N, M);
	std::vector<Coordinate> validNeighbourCells;

	for (const auto& neighbourCell : neighbourCells)
	{
		if (currentPath.find(neighbourCell) == std::cend(currentPath) && matrix[currentCoordinate.first][currentCoordinate.second] == 0)
		{
			validNeighbourCells.push_back(neighbourCell);
		}
	}

	currentPath.insert(currentCoordinate);
	unsigned int pathCount = 0;

	for (const auto& nextCoordinate : validNeighbourCells)
	{
		pathCount += GetAllPathsHelper(matrix, nextCoordinate, currentPath);
	}

	return pathCount;
}

template <unsigned int M, unsigned int N>
inline unsigned int GetAllPaths(const Matrix<M, N>& matrix) noexcept
{
	return GetAllPathsHelper(matrix, { 0, 0 }, std::unordered_set<Coordinate>{ });
}

int main(int argc, char* argv[])
{
	const Matrix<3, 3> matrix
	{
		std::array<bool, 3> { 0, 0, 1 },
		std::array<bool, 3> { 0, 0, 1 },
		std::array<bool, 3> { 1, 0, 0 }
	};

	std::cout << GetAllPaths(matrix) << "\n";

	std::cin.get();

	return 0;
}