#include <algorithm>
#include <array>
#include <iostream>

template <unsigned int Size>
int GetMaxSubarraySum(const std::array<int, Size>& numbers) noexcept
{
	int maxElement = *std::max_element(numbers.begin(), numbers.end());
	
	if (numbers.empty() || maxElement < 0)
	{
		return 0;
	}

	int currentMaxSum = numbers[0];
	int maxSum = numbers[0];

	for (unsigned int i = 1; i < Size; i++)
	{
		currentMaxSum = std::max(numbers[i], currentMaxSum + numbers[i]);
		maxSum = std::max(maxSum, currentMaxSum);
	}

	return maxSum;
}

int main(int argc, const char* argv[])
{
	const std::array<int, 6> numbers { 34, -50, 42, 14, -5, 86 };
	std::cout << GetMaxSubarraySum(numbers) << "\n";

	const std::array<int, 4> moreNumbers { -5, -1, -8, -9 };
	std::cout << GetMaxSubarraySum(moreNumbers) << "\n";

	std::cin.get();

	return 0;
}