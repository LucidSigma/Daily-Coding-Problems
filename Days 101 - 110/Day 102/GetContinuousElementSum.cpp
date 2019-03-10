#include <iostream>
#include <iterator>
#include <vector>

std::vector<int> GetContinuousElementSum(const std::vector<int>& numbers, const int k) noexcept
{
	int sum = 0;
	unsigned int startIndex = 0;
	unsigned int endIndex = 0;
	unsigned int counter = 0;

	while (counter < numbers.size())
	{
		if (sum == k)
		{
			return std::vector(std::cbegin(numbers) + startIndex, std::cbegin(numbers) + endIndex);
		}
		else if (sum > k)
		{
			sum -= numbers[startIndex];
			startIndex++;
		}
		else
		{
			sum += numbers[counter];
			counter++;
			endIndex = counter;
		}
	}

	return { };
}

template <typename T>
void PrintVector(const std::vector<T>& values) noexcept
{
	for (const auto& value : values)
	{
		std::cout << value << " ";
	}

	std::cout << "\n";
}

int main(int argc, char* argv[])
{
	PrintVector(GetContinuousElementSum({ 1, 2, 3, 4, 5 }, 9));

	std::cin.get();

	return 0;
}