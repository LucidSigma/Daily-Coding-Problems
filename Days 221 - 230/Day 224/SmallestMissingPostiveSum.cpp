#include <cstdlib>
#include <iostream>
#include <vector>

unsigned int GetSmallestMissingPositiveSum(const std::vector<unsigned int>& numbers) noexcept
{
	unsigned int smallestMissingPositive = 1;

	for (const auto number : numbers)
	{
		if (number > smallestMissingPositive)
		{
			break;
		}

		smallestMissingPositive += number;
	}

	return smallestMissingPositive;
}

int main(int argc, char* argv[])
{
	std::cout << GetSmallestMissingPositiveSum({ 1, 2, 3, 10 }) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}