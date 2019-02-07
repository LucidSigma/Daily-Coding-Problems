#include <algorithm>
#include <array>
#include <iostream>
#include <limits>
#include <type_traits>
#include <utility>

struct TripleMax
{
	int a = std::numeric_limits<int>::min();
	int b = std::numeric_limits<int>::min();
	int c = std::numeric_limits<int>::min();

	unsigned int totalAdded = 0;

	void Add(int number) noexcept
	{
		if (number > a)
		{
			c = b;
			b = a;
			a = number;
		}
		else if (number > b)
		{
			c = b;
			b = number;
		}
		else if (number > c)
		{
			c = number;
		}

		totalAdded++;
	}
};

void AddToNegativePair(std::pair<int, int>& negativePair, int number) noexcept
{
	if (number < negativePair.first)
	{
		negativePair.second = negativePair.first;
		negativePair.first = number;
	}
	else if (number < negativePair.second)
	{
		negativePair.second = number;
	}
}

template <unsigned int Size, typename = std::enable_if_t<(Size >= 3)>>
int GetMaxProductFromThreeNumbers(const std::array<int, Size>& numbers) noexcept
{
	if (Size == 3)
	{
		return numbers[0] * numbers[1] * numbers[2];
	}

	TripleMax maxPositives;
	std::pair<int, int> minNegatives { std::numeric_limits<int>::max(), std::numeric_limits<int>::max() };
	unsigned int negativeCount = 0;

	for (int number : numbers)
	{
		if (number >= 0)
		{
			maxPositives.Add(number);
		}
		else
		{
			AddToNegativePair(minNegatives, number);
			negativeCount++;
		}
	}

	int productWithNegatives = std::numeric_limits<int>::min();

	if (negativeCount >= 2 && maxPositives.totalAdded >= 1)
	{
		productWithNegatives = minNegatives.first * minNegatives.second * maxPositives.a;
	}

	int productWithoutNegatives = maxPositives.a * maxPositives.b * maxPositives.c;

	return std::max(productWithoutNegatives, productWithNegatives);
}

int main(int argc, char* argv[])
{
	std::cout << GetMaxProductFromThreeNumbers<4>({ -10, -10, 5, 2 }) << "\n";
	std::cout << GetMaxProductFromThreeNumbers<4>({ -10, 10, 5, 2 }) << "\n";
	std::cout << GetMaxProductFromThreeNumbers<6>({ -10, -10, -5, 2, 7, 9 }) << "\n";
	std::cout << GetMaxProductFromThreeNumbers<6>({ -10, 10, -5, 2, 7, 9 }) << "\n";
	std::cout << GetMaxProductFromThreeNumbers<4>({ -10, 5, 0, -20 }) << "\n";
	std::cout << GetMaxProductFromThreeNumbers<4>({ -10, 5, 0, 20 }) << "\n";

	std::cin.get();

	return 0;
}
