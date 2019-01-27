#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

bool CanSplitEquallyHelper(const std::vector<int>& numbers, unsigned int startIndex, unsigned int endIndex, int firstSum, int secondSum) noexcept
{
	if (startIndex >= endIndex)
	{
		return false;
	}
	else if (firstSum == secondSum)
	{
		return true;
	}
	else
	{
		return CanSplitEquallyHelper(numbers, startIndex + 1, endIndex, firstSum + numbers[startIndex], secondSum - numbers[startIndex]) ||
			   CanSplitEquallyHelper(numbers, startIndex, endIndex - 1, firstSum + numbers[endIndex], secondSum - numbers[endIndex]);
	}
}

bool CanSplitEqually(const std::vector<int>& numbers)
{
	int sum = std::accumulate(numbers.begin(), numbers.end(), 0);

	if (numbers.empty() || sum % 2 == 1)
	{
		return false;
	}

	std::vector<int> sortedNumbers = numbers;
	std::sort(sortedNumbers.begin(), sortedNumbers.end());

	return CanSplitEquallyHelper(sortedNumbers, 0, numbers.size() - 1, 0, sum);
}

int main(int argc, char* argv[])
{
	std::cout << std::boolalpha;
	std::cout << CanSplitEqually({ 15, 5, 20, 10, 35, 15, 10 }) << "\n";
	std::cout << CanSplitEqually({ 15, 5, 20, 10, 35 }) << "\n";

	std::cin.get();

	return 0;
}
