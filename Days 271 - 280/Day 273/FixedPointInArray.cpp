#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <optional>
#include <vector>

std::optional<int> GetFixedPoint(const std::vector<int>& numbers)
{
	for (size_t i = 0; i < numbers.size(); ++i)
	{
		if (static_cast<int>(i) == numbers[i])
		{
			return numbers[i];
		}
	}

	return { };
}

int main(int argc, char* argv[])
{
	std::cout << GetFixedPoint({ -6, 0, 2, 40 }).value() << "\n";
	std::cout << GetFixedPoint({ 1, 5, 7, 8 }).value_or(std::numeric_limits<int>::min()) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}