#include <array>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <iterator>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using Coordinate = std::pair<int, int>;

template <>
struct std::hash<Coordinate>
{
	inline size_t operator ()(const Coordinate& coordinate) const noexcept
	{
		return std::hash<int>()(coordinate.first) ^ std::hash<int>()(coordinate.second);
	}
};

inline bool IsOnBoard(const Coordinate& coordinate)
{
	return coordinate.first >= 0 && coordinate.first < 8 && coordinate.second >= 0 && coordinate.second < 8;
}

std::unordered_set<Coordinate> GetValidMoves(const Coordinate& coordinate, std::unordered_map<Coordinate, std::unordered_set<Coordinate>>& cache)
{
	if (cache.find(coordinate) != std::cend(cache))
	{
		return cache[coordinate];
	}

	std::unordered_set<Coordinate> validMoves;
	static constexpr std::array<int, 4> KnightMoves{ -2, -1, 1, 2 };

	for (const auto horizontal : KnightMoves)
	{
		for (const auto vertical : KnightMoves)
		{
			if (std::abs(horizontal) + std::abs(vertical) == 3)
			{
				const Coordinate currentCoordinate(coordinate.first + horizontal, coordinate.second + vertical);

				if (IsOnBoard(currentCoordinate))
				{
					validMoves.insert(currentCoordinate);
				}
			}
		}
	}

	cache[coordinate] = validMoves;

	return validMoves;
}

void SimulateMoves(const Coordinate& coordinate, const unsigned int moveCount, std::pair<unsigned int, unsigned int>& counts, std::unordered_map<Coordinate, std::unordered_set<Coordinate>>& cache)
{
	if (moveCount == 0)
	{
		return;
	}

	const auto validMoves = GetValidMoves(coordinate, cache);
	counts.first += 8;
	counts.second += validMoves.size();

	for (const auto& nextMove : validMoves)
	{
		SimulateMoves(nextMove, moveCount - 1, counts, cache);
	}
}

float GetOnBoardProbability(const Coordinate& start, const unsigned int moveCount)
{
	std::unordered_map<Coordinate, std::unordered_set<Coordinate>> cache;
	std::pair<unsigned int, unsigned int> counts{ 0, 0 };

	SimulateMoves(start, moveCount, counts, cache);

	return static_cast<float>(counts.second) / static_cast<float>(counts.first);
}

int main(const int argc, const char* const argv[])
{
	std::cout << GetOnBoardProbability({ 3, 5 }, 4) << "%\n";

	std::cin.get();

	return EXIT_SUCCESS;
}