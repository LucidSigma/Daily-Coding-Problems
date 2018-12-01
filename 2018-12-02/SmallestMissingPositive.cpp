#include <iostream>
#include <utility>
#include <vector>

unsigned int SplitPositives(std::vector<int>& numbers)
{
	unsigned int nonPositiveCount = 0;

	for (unsigned int i = 0; i < numbers.size(); i++)
	{
		if (numbers[i] <= 0)
		{
			std::swap(numbers[i], numbers[nonPositiveCount]);

			nonPositiveCount++;
		}
	}

	return nonPositiveCount;
}

unsigned int GetSmallestMissingPositive(std::vector<int>& numbers)
{
	unsigned int nonPositiveCount = SplitPositives(numbers);

	if (nonPositiveCount == numbers.size())
	{
		return 1;
	}

	unsigned int positiveCount = numbers.size() - nonPositiveCount;

	for (unsigned int i = nonPositiveCount; i < numbers.size(); i++)
	{
		if (numbers[i] - 1 < positiveCount)
		{
			numbers[numbers[i] - 1] *= -1;
		}
	}

	for (unsigned int i = nonPositiveCount; i < numbers.size(); i++)
	{
		if (numbers[i] > 0)
		{
			return i + 1;
		}
	}

	return positiveCount + 1;
}

int main(int argc, char* argv[])
{
	std::vector<int> numbers { 6, 3, 9, 1, -7, -3, 2, -4, 2, 1, 0, -9, 4, 5 };
	std::cout << GetSmallestMissingPositive(numbers) << std::endl;

	std::vector<int> moreNumbers { 3, 4, 1, -1 };
	std::cout << GetSmallestMissingPositive(moreNumbers) << std::endl;

	std::vector<int> evenMoreNumbers { 1, 2, 0 };
	std::cout << GetSmallestMissingPositive(evenMoreNumbers) << std::endl;

	std::vector<int> evenEvenMoreNumbers { -1, -2, 0, -6, -4 };
	std::cout << GetSmallestMissingPositive(evenEvenMoreNumbers) << std::endl;

	std::cin.get();
	
	return 0;
}
