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
	std::vector<int> numbers { 3, 4, -1, 1 };
	std::cout << GetSmallestMissingPositive(numbers) << "\n";

	std::vector<int> moreNumbers { 1, 2, 0 };
	std::cout << GetSmallestMissingPositive(moreNumbers) << "\n";

	std::cin.get();
	
	return 0;
}
