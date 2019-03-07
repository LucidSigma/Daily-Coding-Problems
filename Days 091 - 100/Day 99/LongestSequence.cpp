#include <algorithm>
#include <cstddef>
#include <functional>
#include <iostream>
#include <iterator>
#include <unordered_map>
#include <vector>

struct Range
{
	int start;
	int end;

	Range() noexcept = default;

	Range(int start, int end) noexcept
		: start(start), end(end)
	{ }
};

template <>
struct std::hash<Range>
{
	inline std::size_t operator ()(const Range& range) const noexcept
	{
		return std::hash<int>()(range.start) + std::hash<int>()(range.end);
	}
};

void AddNumberToRanges(int number, std::unordered_map<int, Range>& rangeStarts, std::unordered_map<int, Range>& rangeEnds) noexcept
{
	if (rangeStarts.find(number + 1) != std::cend(rangeStarts) && rangeEnds.find(number - 1) != std::cend(rangeEnds))
	{
		Range newStart = rangeEnds[number - 1];
		Range newEnd = rangeStarts[number + 1];
		Range newRange(newStart.start, newStart.end);

		rangeStarts[newRange.start] = newRange;
		rangeEnds[newRange.end] = newRange;

		rangeStarts.erase(newEnd.start);
		rangeEnds.erase(newStart.end);

		return;
	}
	else if (rangeStarts.find(number + 1) != std::cend(rangeStarts))
	{
		Range newRange = rangeStarts[number + 1];
		newRange.start = number;

		rangeStarts[number] = newRange;
		rangeEnds.erase(number + 1);

		return;
	}
	else if (rangeEnds.find(number - 1) != std::cend(rangeEnds))
	{
		Range newRange = rangeEnds[number - 1];
		newRange.end = number;

		rangeEnds[number] = newRange;
		rangeEnds.erase(number - 1);

		return;
	}

	Range newRange(number, number);
	rangeStarts[number] = newRange;
	rangeEnds[number] = newRange;
}

unsigned int GetLongestSequenceLength(const std::vector<int>& numbers) noexcept
{
	std::unordered_map<int, Range> rangeStarts;
	std::unordered_map<int, Range> rangeEnds;

	for (const int number : numbers)
	{
		AddNumberToRanges(number, rangeStarts, rangeEnds);
	}

	unsigned int maxLength = 0;

	for (const auto&[number, range] : rangeStarts)
	{
		unsigned int length = range.end - range.start + 1;
		maxLength = std::max(length, maxLength);
	}

	return maxLength;
}

int main(int argc, char* argv[])
{
	std::cout << GetLongestSequenceLength({ 100, 4, 200, 1, 3, 2 }) << "\n";

	std::cin.get();

	return 0;
}