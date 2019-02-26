#include <algorithm>
#include <iostream>
#include <vector>

int FindMaxNonAdjacentSum(const std::vector<int>& numbers)
{
	int sumWithPrevious = numbers[0];
	int sumWithoutPrevious = 0;

	for (unsigned int i = 1; i < numbers.size(); i++)
	{
		T sumWithoutPreviousNew = std::max(sumWithPrevious, sumWithoutPrevious);

		sumWithPrevious = sumWithoutPrevious + numbers[i];
		sumWithoutPrevious = sumWithoutPreviousNew;
	}

	return std::max(sumWithPrevious, sumWithoutPrevious);
}

int main(int argc, char* argv[])
{
	std::vector<int> numbers { 2, 4, 6, 2, 5 };
	std::cout << FindMaxNonAdjacentSum(numbers) << "\n";

	std::vector<int> moreNumbers { 5, 1, 1, 5 };
	std::cout << FindMaxNonAdjacentSum(moreNumbers) << "\n";

	std::cin.get();

	return 0;
}
