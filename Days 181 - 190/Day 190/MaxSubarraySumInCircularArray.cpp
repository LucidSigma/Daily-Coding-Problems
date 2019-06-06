#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

int GetMaxCircularSubarraySum(const std::vector<int>& circularArray) noexcept
{
	std::vector<int> conjoinedArray = circularArray;
	conjoinedArray.insert(std::cend(conjoinedArray), std::cbegin(circularArray), std::cend(circularArray));

	std::vector<int> currentSubarray;

	int currentSum = 0;
	int maxSum = 0;

	for (const auto number : conjoinedArray)
	{
		while (currentSubarray.size() >= circularArray.size() || (!currentSubarray.empty() && currentSubarray.front() < 1))
		{
			currentSum -= currentSubarray.front();
			currentSubarray = std::vector<int>(std::cbegin(currentSubarray) + 1, std::cend(currentSubarray));
		}

		currentSubarray.push_back(number);
		currentSum += number;

		maxSum = std::max(maxSum, currentSum);
	}

	return maxSum;
}

int main(int argc, char* argv[])
{
	std::cout << GetMaxCircularSubarraySum({ 8, -1, 3, 4 }) << "\n";
	std::cout << GetMaxCircularSubarraySum({ -4, 5, 1, 0 }) << "\n";

	std::cin.get();

	return 0;
}