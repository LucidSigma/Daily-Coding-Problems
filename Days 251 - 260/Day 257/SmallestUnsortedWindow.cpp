#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <set>
#include <utility>
#include <vector>

inline bool operator <(const std::pair<size_t, size_t>& lhs, const std::pair<size_t, size_t>& rhs)
{
	return lhs.first == rhs.first ? lhs.second < rhs.second : lhs.first < rhs.first;
}

std::pair<size_t, size_t> GetSmallestUnsortedWindow(const std::vector<int>& numbers)
{
	auto sortedNumbers = numbers;
	std::sort(std::begin(sortedNumbers), std::end(sortedNumbers));

	if (numbers == sortedNumbers)
	{
		return { 0, numbers.size() - 1 };
	}

	std::set<std::pair<size_t, size_t>> validWindows;

	for (size_t windowStart = 0; windowStart < numbers.size() - 1; ++windowStart)
	{
		for (size_t windowEnd = windowStart + 1; windowEnd <= numbers.size(); ++windowEnd)
		{
			const auto prefix = std::vector<int>(std::cbegin(numbers), std::cbegin(numbers) + windowStart);
			auto window = std::vector<int>(std::cbegin(numbers) + windowStart, std::cbegin(numbers) + windowEnd);
			const auto suffix = std::vector<int>(std::cbegin(numbers) + windowEnd, std::cend(numbers));

			std::sort(std::begin(window), std::end(window));

			auto currentNumbers = prefix;
			currentNumbers.insert(std::cend(currentNumbers), std::cbegin(window), std::cend(window));
			currentNumbers.insert(std::cend(currentNumbers), std::cbegin(suffix), std::cend(suffix));

			if (currentNumbers == sortedNumbers)
			{
				validWindows.emplace(windowStart, windowEnd);
			}
		}
	}

	return *std::cbegin(validWindows);
}

template <typename T, typename U>
inline std::ostream& operator <<(std::ostream& outputStream, const std::pair<T, U>& pair)
{
	outputStream << "( " << pair.first << ", " << pair.second << " )";

	return outputStream;
}

int main(int argc, char* argv[])
{
	std::cout << GetSmallestUnsortedWindow({ 3, 7, 5, 6, 9 }) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}