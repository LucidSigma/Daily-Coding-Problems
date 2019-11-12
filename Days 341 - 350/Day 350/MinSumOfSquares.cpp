#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <vector>

unsigned int GetSumOfSquares(const unsigned int number, std::vector<unsigned int> currentSquares)
{
	if (number == 0)
	{
		return 0;
	}
	else if (currentSquares.empty())
	{
		return std::numeric_limits<unsigned int>::max();
	}

	unsigned int decreasingNumber = number;
	unsigned int counter = 0;

	const unsigned int largestSquare = currentSquares.back();
	currentSquares.pop_back();

	while (decreasingNumber >= largestSquare)
	{
		++counter;
		decreasingNumber -= largestSquare;
	}

	return counter > 0
		   ? std::min(counter + GetSumOfSquares(decreasingNumber, currentSquares), GetSumOfSquares(number, currentSquares))
		   : GetSumOfSquares(number, currentSquares);
}

unsigned int GetMinSumOfSquares(const unsigned int number)
{
	unsigned int currentSquare = 1;
	unsigned int magnitude = 1;
	std::vector<unsigned int> squares;

	while (currentSquare <= number)
	{
		squares.push_back(currentSquare);

		++magnitude;
		currentSquare = magnitude * magnitude;
	}

	return GetSumOfSquares(number, squares);
}

int main(const int argc, const char* const argv[])
{
	std::cout << GetMinSumOfSquares(4) << "\n";
	std::cout << GetMinSumOfSquares(17) << "\n";
	std::cout << GetMinSumOfSquares(18) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}