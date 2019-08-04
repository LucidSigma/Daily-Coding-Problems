#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <vector>

int MaxXOR(const std::vector<int>& numbers)
{
	int maxXOR = std::numeric_limits<int>::min();

	for (size_t i = 0; i < numbers.size() - 1; ++i)
	{
		for (size_t j = i + 1; j < numbers.size(); ++j)
		{
			maxXOR = std::max(maxXOR, numbers[i] ^ numbers[j]);
		}
	}

	return maxXOR;
}

int main(int argc, char* argv[])
{
	std::cout << MaxXOR({ 6, 3, 9, 2, -8, 7 }) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}