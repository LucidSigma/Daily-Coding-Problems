#include <algorithm>
#include <iostream>
#include <iterator>
#include <unordered_set>
#include <vector>

unsigned int GetLengthOfLongestUniqueSubarrayHelper(const std::vector<int>& numbers, std::unordered_set<int> currentSubarray) noexcept
{
	if (numbers.empty())
	{
		return currentSubarray.size();
	}

	const int firstNumber = numbers.front();

	if (currentSubarray.find(firstNumber) != std::cend(currentSubarray))
	{
		return currentSubarray.size();
	}

	currentSubarray.insert(firstNumber);
	const std::vector<int> numbersTail = std::vector(std::cbegin(numbers) + 1, std::cend(numbers));

	return std::max(GetLengthOfLongestUniqueSubarrayHelper(numbersTail, currentSubarray), GetLengthOfLongestUniqueSubarrayHelper(numbersTail, { }));
}

inline unsigned int GetLengthOfLongestUniqueSubarray(const std::vector<int>& numbers) noexcept
{
	return GetLengthOfLongestUniqueSubarrayHelper(numbers, { });
}

int main(int argc, char* argv[])
{
	std::cout << GetLengthOfLongestUniqueSubarray({ 5, 1, 3, 5, 2, 3, 4, 1 }) << "\n";

	std::cin.get();

	return 0;
}