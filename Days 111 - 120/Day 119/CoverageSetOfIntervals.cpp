#include <iostream>
#include <iterator>
#include <limits>
#include <set>
#include <unordered_map>
#include <utility>
#include <vector>

using Interval = std::pair<unsigned int, unsigned int>;

std::set<unsigned int> GetCoverageSetHelper(const std::set<Interval>& leftoverIntervals, const std::set<unsigned int>& usedPoints, const std::set<unsigned int>& leftoverEndPoints, const std::unordered_map<unsigned int, std::set<Interval>>& indexToIntervalMap) noexcept
{
	if (leftoverIntervals.empty())
	{
		return usedPoints;
	}

	unsigned int minLength = std::numeric_limits<unsigned int>::max();
	std::set<unsigned int> smallestCoverageSet;

	for (const auto& currentPoint : leftoverEndPoints)
	{
		if (indexToIntervalMap.find(currentPoint) == std::cend(indexToIntervalMap))
		{
			continue;
		}

		std::set<Interval> currentPointIntervals = indexToIntervalMap.at(currentPoint);
		std::set<Interval> remainingIntervals;

		for (const auto& interval : leftoverIntervals)
		{
			if (currentPointIntervals.find(interval) == std::cend(currentPointIntervals))
			{
				remainingIntervals.insert(interval);
			}
		}

		std::set<unsigned int> currentUsedPoints = usedPoints;
		currentUsedPoints.insert(currentPoint);

		std::set<unsigned int> currentRemainingPoints = leftoverEndPoints;
		currentRemainingPoints.erase(currentPoint);

		std::set<unsigned int> coverageSet = GetCoverageSetHelper(remainingIntervals, currentUsedPoints, currentRemainingPoints, indexToIntervalMap);

		if (coverageSet.size() < minLength)
		{
			smallestCoverageSet = coverageSet;
			minLength = coverageSet.size();
		}
	}

	return smallestCoverageSet;
}

std::set<unsigned int> GetCoverageSet(const std::vector<Interval>& initialIntervals) noexcept
{
	std::set<Interval> intervals;
	std::unordered_map<unsigned int, std::set<Interval>> indexToIntervalMap;

	std::set<unsigned int> endPoints;

	for (const auto&[start, end] : initialIntervals)
	{
		endPoints.insert(end);
		intervals.emplace(start, end);

		for (unsigned int i = start; i <= end; i++)
		{
			indexToIntervalMap[i].emplace(start, end);
		}
	}

	return GetCoverageSetHelper(intervals, std::set<unsigned int>(), endPoints, indexToIntervalMap);
}

template <typename T>
void PrintSet(const std::set<T>& values) noexcept
{
	for (const auto& value : values)
	{
		std::cout << value << " ";
	}

	std::cout << "\n";
}

int main(int argc, char* argv[])
{
	PrintSet(GetCoverageSet({ { 0, 3 }, { 2, 6 }, { 3, 4 }, { 6, 9 } }));

	std::cin.get();

	return 0;
}

