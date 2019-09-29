#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <vector>

std::vector<int> SortDisplacedNumbers(const std::vector<int>& numbers, const unsigned int maxDisplacement)
{
	std::vector<int> sortedNumbers = numbers;
	std::sort(std::begin(sortedNumbers), std::begin(sortedNumbers) + maxDisplacement + 1);

	for (size_t i = maxDisplacement; i < numbers.size(); ++i)
	{
		const size_t startOffset = i - maxDisplacement + 1;
		const size_t endOffset = i + 1;

		std::sort(std::begin(sortedNumbers) + startOffset, std::begin(sortedNumbers) + endOffset);
	}

	return sortedNumbers;
}

template <typename T>
std::ostream& operator <<(std::ostream& outputStream, const std::vector<T>& values)
{
	for (const auto& value : values)
	{
		outputStream << value << " ";
	}

	return outputStream;
}

int main(const int argc, const char* const argv[])
{
	std::cout << SortDisplacedNumbers({ 2, 1, 0, 4, 3, 5, 8, 6, 7 }, 2) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}