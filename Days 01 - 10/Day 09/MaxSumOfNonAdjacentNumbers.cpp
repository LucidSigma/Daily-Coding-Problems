#include <algorithm>
#include <iostream>
#include <type_traits>
#include <vector>

template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
T FindMaxNonAdjacentSum(const std::vector<T>& numbers)
{
	T sumWithPrevious = numbers[0];
	T sumWithoutPrevious = 0;

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
