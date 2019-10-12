#include <array>
#include <cstddef>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <optional>
#include <unordered_set>
#include <utility>

constexpr size_t BoardSize = 3u;

using Board = std::array<std::array<std::optional<unsigned int>, BoardSize>, BoardSize>;
using Coordinate = std::pair<size_t, size_t>;

namespace std
{
	template <>
	struct hash<Coordinate>
	{
		inline size_t operator ()(const Coordinate& coordinate) const noexcept
		{
			return coordinate.first ^ coordinate.second;
		}
	};
}

std::unordered_set<Coordinate> GetNextCoordinates(const Coordinate& emptySpace)
{
	std::unordered_set<Coordinate> nextCoordinates;

	if (emptySpace.first > 0)
	{
		if (emptySpace.second > 0)
		{
			nextCoordinates.emplace(emptySpace.first - 1, emptySpace.second - 1);
		}

		if (emptySpace.second < BoardSize - 1)
		{
			nextCoordinates.emplace(emptySpace.first - 1, emptySpace.second + 1);
		}
	}

	if (emptySpace.first < BoardSize - 1)
	{
		if (emptySpace.second > 0)
		{
			nextCoordinates.emplace(emptySpace.first + 1, emptySpace.second - 1);
		}

		if (emptySpace.second < BoardSize - 1)
		{
			nextCoordinates.emplace(emptySpace.first + 1, emptySpace.second + 1);
		}
	}

	return nextCoordinates;
}

unsigned int GetStepsToWinHelper(Board board, const Coordinate& emptySpace)
{
	static constexpr Board SolvedBoard
	{
		std::array<std::optional<unsigned int>, BoardSize>{ 1, 2, 3 },
		std::array<std::optional<unsigned int>, BoardSize>{ 4, 5, 6 },
		std::array<std::optional<unsigned int>, BoardSize>{ 7, 8, std::nullopt }
	};

	if (board == SolvedBoard)
	{
		return 0;
	}

	const auto nextCoordinates = GetNextCoordinates(emptySpace);
	unsigned int stepsToWin = 0;

	for (const auto& nextCoordinate : nextCoordinates)
	{
		board[emptySpace.first][emptySpace.second] = std::exchange(board[nextCoordinate.first][nextCoordinate.second], std::nullopt);
		stepsToWin += GetStepsToWinHelper(board, nextCoordinate);
	}

	return stepsToWin;
}

unsigned int GetStepsToWin(const Board& board)
{
	Coordinate emptySpace{ };

	for (size_t y = 0; y < board.size(); ++y)
	{
		for (size_t x = 0; x < board.front().size(); ++x)
		{
			emptySpace = { x, y };
		}
	}

	return GetStepsToWinHelper(board, emptySpace);
}

int main(const int argc, const char* const argv[])
{
	const Board board
	{
		std::array<std::optional<unsigned int>, BoardSize>{ 6, 4, std::nullopt },
		std::array<std::optional<unsigned int>, BoardSize>{ 5, 3, 2 },
		std::array<std::optional<unsigned int>, BoardSize>{ 1, 7, 8 }	
	};

	std::cout << GetStepsToWin(board) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}