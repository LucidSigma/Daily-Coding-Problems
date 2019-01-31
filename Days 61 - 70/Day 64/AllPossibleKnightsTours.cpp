#include <array>
#include <iostream>
#include <utility>
#include <vector>

static constexpr int UnvisitedSquare = -1;
static constexpr int PossibleKnightMoves = 8;

template <unsigned int Size>
bool IsValidMove(const std::array<std::array<int, Size>, Size>& board, int x, int y) noexcept
{
	return x >= 0 && x < Size && y >= 0 && y < Size && board[x][y] == UnvisitedSquare;
}

template <unsigned int Size>
std::vector<std::pair<int, int>> GetValidMoves(const std::array<std::array<int, Size>, Size>& board, int x, int y)
{
	static constexpr std::pair<int, int> MoveDeltas[PossibleKnightMoves]
	{
		std::make_pair(2, 1),
		std::make_pair(1, 2),
		std::make_pair(1, -2),
		std::make_pair(-2, 1),
		std::make_pair(-1, 2),
		std::make_pair(2, -1),
		std::make_pair(-1, -2),
		std::make_pair(-2, -1)
	};

	std::vector<std::pair<int, int>> possibleMoves;

	for (unsigned int i = 0; i < PossibleKnightMoves; i++)
	{
		std::pair<int, int> move = std::make_pair(x + MoveDeltas[i].first, y + MoveDeltas[i].second);

		if (IsValidMove(board, move.first, move.second))
		{
			possibleMoves.push_back(move);
		}
	}

	return possibleMoves;
}

template <unsigned int Size>
unsigned int KnightsTourHelper(std::array<std::array<int, Size>, Size>& board, std::vector<std::pair<int, int>>& tour)
{
	if (tour.size() == Size * Size)
	{
		return 1;
	}
	else
	{
		unsigned int count = 0;
		auto[lastX, lastY] = tour.back();

		for (const auto& move : GetValidMoves(board, lastX, lastY))
		{
			auto[x, y] = move;

			tour.push_back(std::make_pair(x, y));
			board[x][y] = tour.size();

			count += KnightsTourHelper(board, tour);

			tour.pop_back();
			board[x][y] = UnvisitedSquare;
		}

		return count;
	}
}

template <unsigned int Size>
unsigned int KnightsTour()
{
	unsigned int count = 0;

	for (int i = 0; i < Size; i++)
	{
		for (int j = 0; j < Size; j++)
		{
			std::array<std::array<int, Size>, Size> board;

			for (unsigned int row = 0; row < Size; row++)
			{
				for (unsigned int column = 0; column < Size; column++)
				{
					board[row][column] = UnvisitedSquare;
				}
			}

			board[i][j] = 0;
			std::vector<std::pair<int, int>> tour { std::make_pair(i, j) };

			count += KnightsTourHelper(board, tour);
		}
	}

	return count;
}

int main(int argc, char* argv[])
{
	std::cout << KnightsTour<5>() << "\n";

	std::cin.get();

	return 0;
}
