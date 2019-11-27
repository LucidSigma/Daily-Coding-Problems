#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <vector>

std::vector<int> GetLongestIncreasingSubsequence(const std::vector<int>& numbers)
{
	std::vector<int> longestIncreasingSubsequence;
	size_t startIndex = 0;

	for (size_t i = 0; i < numbers.size(); ++i)
	{
		if (i != 0 && numbers[i] < numbers[i - 1])
		{
			startIndex = i;
		}

		if (const size_t endIndex = i + 1;
			endIndex - startIndex > longestIncreasingSubsequence.size())
		{
			longestIncreasingSubsequence = std::vector<int>(std::cbegin(numbers) + startIndex, std::cbegin(numbers) + endIndex);
		}
	}

	return longestIncreasingSubsequence;
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
	std::cout << GetLongestIncreasingSubsequence({ 3, 7, 2, 5, 6, 8, 1, 0 }) << "\n";
	std::cout << GetLongestIncreasingSubsequence({ 1, 2, 3, 4, 5, 6, 7, 8 }) << "\n";
	std::cout << GetLongestIncreasingSubsequence({ 9, 8, 7, 6, 4, 3, 1, 0 }) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}