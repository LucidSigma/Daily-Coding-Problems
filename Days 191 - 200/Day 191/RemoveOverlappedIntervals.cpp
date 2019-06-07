#include <algorithm>
#include <iostream>
#include <iterator>
#include <unordered_set>
#include <utility>
#include <vector>

using Interval = std::pair<unsigned int, unsigned int>;

unsigned int GetFrivolousIntervalCountHelper(const std::vector<Interval>& intervals, std::vector<std::unordered_set<unsigned int>> intervalSpans, const unsigned int removedIntervalCount) noexcept
{
	if (intervals.empty())
	{
		return removedIntervalCount;
	}

	const Interval currentInterval = intervals.front();
	const unsigned int tailRemovalCount = GetFrivolousIntervalCountHelper(std::vector<Interval>(std::cbegin(intervals) + 1, std::cend(intervals)), intervalSpans, removedIntervalCount + 1);

	for (const auto& reservedInterval : intervalSpans)
	{
		if (reservedInterval.find(currentInterval.first) != std::cend(reservedInterval) || reservedInterval.find(currentInterval.second) != std::cend(reservedInterval))
		{
			return tailRemovalCount;
		}
	}

	std::unordered_set<unsigned int> newIntervalSpan;
	
	for (unsigned int i = currentInterval.first; i < currentInterval.second; ++i)
	{
		newIntervalSpan.insert(i);
	}

	intervalSpans.push_back(newIntervalSpan);

	return std::min(tailRemovalCount, GetFrivolousIntervalCountHelper(std::vector<Interval>(std::cbegin(intervals) + 1, std::cend(intervals)), intervalSpans, removedIntervalCount));
}

inline unsigned int GetFrivolousIntervalCount(const std::vector<Interval>& intervals) noexcept
{
	return GetFrivolousIntervalCountHelper(intervals, { }, 0);
}

int main(int argc, char* argv[])
{
	std::cout << GetFrivolousIntervalCount({ { 0, 1 }, { 1, 2 } }) << "\n";
	std::cout << GetFrivolousIntervalCount({ { 7, 9 }, { 2, 4 }, { 5, 8 } }) << "\n";

	std::cin.get();

	return 0;
}