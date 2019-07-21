#include <array>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <type_traits>
#include <utility>

template <size_t N, typename = std::enable_if_t<(N > 0)>>
std::pair<int, int> FindMinAndMax(const std::array<int, N>& numbers) noexcept
{
	int minNumber = numbers[0];
	int maxNumber = numbers[0];

	for (size_t i = 1; i < numbers.size(); ++i)
	{
		if (numbers[i] < minNumber)
		{
			minNumber = numbers[i];
		}
		else if (numbers[i] > maxNumber)
		{
			maxNumber = numbers[i];
		}
	}

	return { minNumber, maxNumber };
}

int main(int argc, char* argv[])
{
	const auto [min, max] = FindMinAndMax<7>({ 5, 9, 2, 4, 1, 8, 3 });

	std::cout << "Min: " << min << "\nMax: " << max << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}