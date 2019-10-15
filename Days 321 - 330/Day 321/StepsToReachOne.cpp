#include <cstdlib>
#include <iostream>
#include <utility>

std::pair<unsigned int, unsigned int> GetClosestFactors(const unsigned int number)
{
	unsigned int potentialFactor = 1;
	unsigned int factorLimit = number;

	std::pair<unsigned int, unsigned int> closestFactors{ 1, 1 };

	while (factorLimit > potentialFactor)
	{
		if (number % potentialFactor == 0)
		{
			closestFactors = { potentialFactor, number / potentialFactor };
		}

		factorLimit = number / potentialFactor;
		++potentialFactor;
	}

	return closestFactors;
}

unsigned int StepsToReachOne(const unsigned int number)
{
	if (number == 1)
	{
		return 0;
	}

	unsigned int successiveStepCount = StepsToReachOne(number - 1);

	if (const unsigned int largestFactor = GetClosestFactors(number).second; 
		largestFactor < number)
	{
		const unsigned int alternateSuccessiveStepCount = StepsToReachOne(largestFactor);

		if (successiveStepCount > alternateSuccessiveStepCount)
		{
			successiveStepCount = alternateSuccessiveStepCount;
		}
	}

	return successiveStepCount + 1;
}

int main(const int argc, const char* const argv[])
{
	std::cout << StepsToReachOne(100) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}