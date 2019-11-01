#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <vector>

bool ContainsTwoNumberSum(const std::vector<int>& numbers, const int sum)
{
	size_t i = 0;
	size_t j = numbers.size() - 1;

	while (i < j)
	{
		const int firstNumber = numbers[i];
		const int secondNumber = numbers[j];

		if (const int currentSum = firstNumber + secondNumber;
			currentSum == sum)
		{
			return true;
		}
		else if (currentSum < sum)
		{
			++i;
		}
		else
		{
			--j;
		}
	}

	return false;
}

bool ContainsThreeNumberSum(std::vector<int> numbers, const int sum)
{
	std::sort(std::begin(numbers), std::end(numbers));

	for (size_t i = 0; i < numbers.size(); ++i)
	{
		const int currentNumber = numbers[i];

		if (currentNumber > sum)
		{
			continue;
		}

		std::vector<int> currentNumberVector = numbers;
		numbers.erase(std::cbegin(numbers) + i);

		if (ContainsThreeNumberSum(currentNumberVector, sum - currentNumber))
		{
			return true;
		}
	}

	return false;
}

int main(const int argc, const char* const argv[])
{
	std::cout << std::boolalpha;
	std::cout << ContainsThreeNumberSum({ 20, 303, 3, 4, 25 }, 49) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}