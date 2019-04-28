#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>
#include <unordered_set>
#include <utility>
#include <vector>

using Coordinate = std::pair<unsigned int, unsigned int>;

template <unsigned int M, unsigned int N>
using PixelMatrix = std::array<std::array<char, M>, N>;

template <>
struct std::hash<Coordinate>
{
	inline std::size_t operator ()(const Coordinate& coordinate) const noexcept
	{
		return std::hash<unsigned int>()(coordinate.first) ^ std::hash<unsigned int>()(coordinate.second);
	}
};

template <unsigned int M, unsigned int N>
void FillMatrixAtCoordinateHelper(PixelMatrix<M, N>& pixels, const char colour, const char oldColour, std::unordered_set<Coordinate>& visitedCoordinates, const std::vector<Coordinate>& pendingCoordinates) noexcept
{
	std::vector<Coordinate> nextCoordinates;

	for (const Coordinate& coordinate : pendingCoordinates)
	{
		if (pixels[coordinate.second][coordinate.first] == oldColour)
		{
			pixels[coordinate.second][coordinate.first] = colour;

			for (int i = -1; i <= 1; i++)
			{
				for (int j = -1; j <= 1; j++)
				{
					if (i == 0 && j == 0)
					{
						continue;
					}

					if (Coordinate offsetCoordinate{ std::clamp(coordinate.first + i, 0u, M - 1), std::clamp(coordinate.second + j, 0u, N - 1) };
						pixels[offsetCoordinate.second][offsetCoordinate.first] == oldColour && visitedCoordinates.find(offsetCoordinate) == std::cend(visitedCoordinates))
					{
						nextCoordinates.push_back(offsetCoordinate);
						visitedCoordinates.insert(offsetCoordinate);
					}
				}
			}
		}
	}

	if (!nextCoordinates.empty())
	{
		FillMatrixAtCoordinateHelper(pixels, colour, oldColour, visitedCoordinates, nextCoordinates);
	}
}

template <unsigned int M, unsigned int N>
inline void FillMatrixAtCoordinate(PixelMatrix<M, N>& pixels, const Coordinate& coordinate, const char colour) noexcept
{
	std::unordered_set<Coordinate> visitedCoordinates;

	FillMatrixAtCoordinateHelper(pixels, colour, pixels[coordinate.second][coordinate.first], visitedCoordinates, { coordinate });
}

template <unsigned int M, unsigned int N>
void PrintPixelMatrix(const PixelMatrix<M, N>& pixelMatrix) noexcept
{
	for (const auto& row : pixelMatrix)
	{
		for (const auto pixel : row)
		{
			std::cout << pixel << " ";
		}

		std::cout << "\n";
	}
}

int main(int argc, char* argv[])
{
	PixelMatrix<3, 4> pixels
	{
		std::array<char, 3> { 'B', 'B', 'W' },
		std::array<char, 3> { 'W', 'W', 'W' },
		std::array<char, 3> { 'W', 'W', 'W' },
		std::array<char, 3> { 'B', 'B', 'B' }
	};

	std::cout << "Before fill:\n";
	PrintPixelMatrix(pixels);

	FillMatrixAtCoordinate(pixels, { 2, 2 }, 'G');

	std::cout << "\nAfter fill:\n";
	PrintPixelMatrix(pixels);

	std::cin.get();

	return 0;
}