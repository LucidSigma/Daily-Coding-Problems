#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <vector>

using Listener = unsigned int;
using Tower = unsigned int;

unsigned int GetMinBroadcastRangeHelper(const unsigned int westLocation, const unsigned int eastLocation, const std::vector<Tower>& towers, const unsigned int currentDistance)
{
	if (std::find(towers.cbegin(), towers.cend(), westLocation) != std::cend(towers) ||
		std::find(towers.cbegin(), towers.cend(), eastLocation) != std::cend(towers))
	{
		return currentDistance;
	}

	return GetMinBroadcastRangeHelper(westLocation - 1, eastLocation + 1, towers, currentDistance + 1);
}

unsigned int GetMinBroadcastRange(const std::vector<Listener>& listeners, const std::vector<Tower>& towers)
{
	unsigned int minBroadcastRange = 0;

	for (const auto listener : listeners)
	{
		minBroadcastRange = std::max(minBroadcastRange, GetMinBroadcastRangeHelper(listener, listener, towers, 0));
	}

	return minBroadcastRange;
}

int main(const int argc, const char* const argv[])
{
	std::cout << GetMinBroadcastRange({ 1, 5, 11, 20 }, { 4, 8, 15 }) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}