#include <iostream>
#include <iterator>
#include <vector>

unsigned int GetTotalSquareSum(unsigned int number) noexcept
{
	std::vector<unsigned int> validSquares;
	unsigned int squareCounter = 1;

	while (squareCounter * squareCounter < number)
	{
		validSquares.push_back(squareCounter * squareCounter);
		++squareCounter;
	}

	unsigned int currentSquareIndex = validSquares.size() - 1;
	unsigned int squareSumCount = 0;

	while (number > 0)
	{
		if (validSquares[currentSquareIndex] > number)
		{
			--currentSquareIndex;
		}
		else
		{
			number -= validSquares[currentSquareIndex];
			++squareSumCount;
		}
	}

	return squareSumCount;
}

int main(int argc, char* argv[])
{
	std::cout << GetTotalSquareSum(13) << "\n";
	std::cout << GetTotalSquareSum(27) << "\n";

	std::cin.get();

	return 0;
}