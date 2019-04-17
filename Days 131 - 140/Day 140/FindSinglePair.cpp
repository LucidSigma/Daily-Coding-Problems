#include <iostream>
#include <utility>
#include <vector>

std::pair<int, int> GetSinglePair(const std::vector<int>& numbers) noexcept
{
	int xorChain = numbers[0];

	for (unsigned int i = 1; i < numbers.size(); i++)
	{
		xorChain ^= numbers[i];
	}

	std::pair<int, int> singleNumbers{ 0, 0 };
	int rightmostSetBit = xorChain & ~(xorChain - 1);

	for (const int number : numbers)
	{
		((number & rightmostSetBit) != 0 ? singleNumbers.first : singleNumbers.second) ^= number;
	}

	return singleNumbers;
}

template <typename T, typename U>
inline void PrintPair(const std::pair<T, U>& pair) noexcept
{
	std::cout << pair.first << ", " << pair.second << "\n";
}

int main(int argc, char* argv[])
{
	PrintPair(GetSinglePair({ 2, 4, 6, 8, 10, 2, 6, 10 }));

	std::cin.get();

	return 0;
}