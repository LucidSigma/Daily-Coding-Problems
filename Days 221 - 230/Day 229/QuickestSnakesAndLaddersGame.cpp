#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <limits>
#include <unordered_map>
#include <utility>
#include <vector>

using Snake = std::pair<unsigned int, unsigned int>;
using Ladder = std::pair<unsigned int, unsigned int>;

unsigned int GetQuickestSnakesAndLaddersGameHelper(const std::unordered_map<unsigned int, unsigned int>& snakes, const std::unordered_map<unsigned int, unsigned int>& ladders, const unsigned int currentTile, const unsigned int turnCount, std::unordered_map<unsigned int, unsigned int>& tileCache) noexcept
{
	static constexpr unsigned int BoardSize = 100u;

	if (turnCount > BoardSize || currentTile > BoardSize)
	{
		return std::numeric_limits<unsigned int>::max();
	}

	if (currentTile == BoardSize)
	{
		return turnCount;
	}

	if (tileCache.find(currentTile) != std::cend(tileCache))
	{
		return tileCache.at(currentTile);
	}

	bool isOnSnake = false;

	std::for_each(std::cbegin(snakes), std::cend(snakes), [&isOnSnake, currentTile](const Snake& snake) noexcept
		{
			if (currentTile == snake.first)
			{
				isOnSnake = true;
			}
		}
	);

	if (isOnSnake)
	{
		const unsigned int currentTurnCount = GetQuickestSnakesAndLaddersGameHelper(snakes, ladders, snakes.at(currentTile), turnCount, tileCache);
		tileCache[currentTile] = currentTurnCount;

		return tileCache[currentTile];
	}

	bool isOnLadder = false;

	std::for_each(std::cbegin(ladders), std::cend(ladders), [&isOnLadder, currentTile](const Ladder& ladder) noexcept
		{
			if (currentTile == ladder.first)
			{
				isOnLadder = true;
			}
		}
	);

	if (isOnLadder)
	{
		const unsigned int currentTurnCount = GetQuickestSnakesAndLaddersGameHelper(snakes, ladders, ladders.at(currentTile), turnCount, tileCache);
		tileCache[currentTile] = currentTurnCount;

		return tileCache[currentTile];
	}

	static constexpr unsigned int DiceSideCount = 6u;
	std::vector<unsigned int> candidateTurnCounts;

	for (unsigned int i = 1; i <= DiceSideCount; ++i)
	{
		const unsigned int currentTurnCount = GetQuickestSnakesAndLaddersGameHelper(snakes, ladders, currentTile + i, turnCount + 1, tileCache);
		tileCache[currentTile + i] = currentTurnCount;

		candidateTurnCounts.push_back(currentTurnCount);
	}

	return *std::min_element(std::cbegin(candidateTurnCounts), std::cend(candidateTurnCounts));
}

inline unsigned int GetQuickestSnakesAndLaddersGame(const std::unordered_map<unsigned int, unsigned int>& snakes, const std::unordered_map<unsigned int, unsigned int>& ladders) noexcept
{
	std::unordered_map<unsigned int, unsigned int> tileCache;

	return GetQuickestSnakesAndLaddersGameHelper(snakes, ladders, 1, 0, tileCache);
}

int main(int argc, char* argv[])
{
	const std::unordered_map<unsigned int, unsigned int> snakes
	{
		{ 16, 6 },
		{ 48, 26 },
		{ 49, 11 },
		{ 56, 53 },
		{ 62, 19 },
		{ 64, 60 },
		{ 87, 24 },
		{ 93, 73 },
		{ 95, 75 },
		{ 98, 78 }
	};

	const std::unordered_map<unsigned int, unsigned int> ladders
	{
		{ 1, 38 },
		{ 4, 14 },
		{ 9, 31 },
		{ 21, 42 },
		{ 28, 84 },
		{ 36, 44 },
		{ 51, 67 },
		{ 71, 91 },
		{ 80, 100 }
	};

	std::cout << GetQuickestSnakesAndLaddersGame(snakes, ladders) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}