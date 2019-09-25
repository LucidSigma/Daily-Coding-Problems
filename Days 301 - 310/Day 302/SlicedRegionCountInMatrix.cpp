#include <cstddef>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <iterator>
#include <unordered_set>
#include <utility>
#include <vector>

using Coordinate = std::pair<size_t, size_t>;
using Matrix = std::vector<std::vector<char>>;

template <>
struct std::hash<Coordinate>
{
	inline size_t operator ()(const Coordinate& coordinate) const noexcept
	{
		return coordinate.first ^ coordinate.second;
	}
};

void GetSlicedRegionCountHelper(const Coordinate startCoordinate, std::unordered_set<Coordinate>& emptySpaces, const unsigned int rowCount, const unsigned int columnCount)
{
	if (emptySpaces.find(startCoordinate) == std::cend(emptySpaces))
	{
		return;
	}

	emptySpaces.erase(startCoordinate);

	if (startCoordinate.first > 0)
	{
		GetSlicedRegionCountHelper({ startCoordinate.first - 1, startCoordinate.second }, emptySpaces, rowCount, columnCount);
	}
	
	if (startCoordinate.first < rowCount - 1)
	{
		GetSlicedRegionCountHelper({ startCoordinate.first + 1, startCoordinate.second }, emptySpaces, rowCount, columnCount);
	}

	if (startCoordinate.second > 0)
	{
		GetSlicedRegionCountHelper({ startCoordinate.first, startCoordinate.second - 1}, emptySpaces, rowCount, columnCount);
	}

	if (startCoordinate.second < columnCount - 1)
	{
		GetSlicedRegionCountHelper({ startCoordinate.first, startCoordinate.second + 1}, emptySpaces, rowCount, columnCount);
	}
}

unsigned int GetSlicedRegionCount(const Matrix& matrix)
{
	std::unordered_set<Coordinate> emptySpaces;

	for (size_t i = 0; i < matrix.size(); ++i)
	{
		for (size_t j = 0; j < matrix[i].size(); ++j)
		{
			if (matrix[i][j] == ' ')
			{
				emptySpaces.emplace(i, j);
			}
		}
	}

	unsigned int regionCount = 0;

	while (!emptySpaces.empty())
	{
		GetSlicedRegionCountHelper(*std::cbegin(emptySpaces), emptySpaces, matrix.size(), matrix.front().size());
		++regionCount;
	}

	return regionCount;
}

int main(int argc, char* argv[])
{
	const Matrix matrix
	{
		{ '\\', ' ', ' ', ' ', ' ', '/' },
		{ ' ', '\\', ' ', ' ', '/', ' ' },
		{ ' ', ' ', '\\', '/', ' ', ' ' }
	};

	std::cout << GetSlicedRegionCount(matrix) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}