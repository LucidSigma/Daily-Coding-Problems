#include <cmath>
#include <iostream>
#include <vector>

bool IsValidQueenSetup(const std::vector<unsigned int>& board)
{
	unsigned int lastRow = board.size() - 1;
	unsigned int lastColumn = board[board.size() - 1];

	for (unsigned int i = 0; i < lastRow; i++)
	{
		unsigned int difference = std::abs(static_cast<int>(lastColumn - board[i]));

		if ((difference == 0) || (difference == lastRow - i))
		{
			return false;
		}
	}

	return true;
}

unsigned int GetValidQueenSetupsHelper(std::vector<unsigned int>& board, const unsigned int N)
{
	if (board.size() == N)
	{
		return 1;
	}

	unsigned int count = 0;

	for (unsigned int i = 0; i < N; i++)
	{
		board.push_back(i);

		if (IsValidQueenSetup(board))
		{
			count += GetValidQueenSetupsHelper(board, N);
		}

		board.pop_back();
	}

	return count;
}

unsigned int GetValidQueenSetups(const unsigned int N)
{
	std::vector<unsigned int> board;

	return GetValidQueenSetupsHelper(board, N);
}

int main(int argc, const char* argv[])
{
	std::cout << "Total solutions for N = 2: " << GetValidQueenSetups(2) << "\n";
	std::cout << "Total solutions for N = 4: " << GetValidQueenSetups(4) << "\n";
	std::cout << "Total solutions for N = 8: " << GetValidQueenSetups(8) << "\n";

	std::cin.get();

	return 0;
}