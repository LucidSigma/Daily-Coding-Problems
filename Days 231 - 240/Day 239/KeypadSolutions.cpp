#include <array>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <unordered_map>
#include <unordered_set>

static constexpr size_t KeyCount = 9u;

unsigned int GetTotalUnlockPatternsHelper(const std::array<unsigned int, KeyCount>& keys, const std::unordered_map<unsigned int, std::unordered_set<unsigned int>>& keyEdges, const unsigned int codeLength, const unsigned int currentKey, std::unordered_set<unsigned int> visitedKeys)
{
	if (codeLength == 0)
	{
		return 1;
	}

	visitedKeys.insert(currentKey);

	const auto edgeKeys = keyEdges.at(currentKey);
	unsigned int currentCount = 0;

	for (const auto edgeKey : edgeKeys)
	{
		if (visitedKeys.find(edgeKey) == std::cend(visitedKeys))
		{
			currentCount += GetTotalUnlockPatternsHelper(keys, keyEdges, codeLength - 1, edgeKey, visitedKeys);
		}
	}

	return currentCount;
}

unsigned int GetTotalUnlockPatterns(const unsigned int codeLength)
{
	if (codeLength == 1)
	{
		return KeyCount;
	}

	const std::array<unsigned int, KeyCount> keys
	{
		1, 2, 3, 4, 5, 6, 7, 8, 9
	};

	const std::unordered_map<unsigned int, std::unordered_set<unsigned int>> keyEdges
	{
		{ 1, { 2, 4, 5 } },
		{ 2, { 1, 3, 4, 5, 6 } },
		{ 3, { 2, 5, 6 } },
		{ 4, { 1, 2, 5, 7, 8 } },
		{ 5, { 1, 2, 3, 4, 5, 6, 7, 8 } },
		{ 6, { 2, 3, 5, 8, 9 } },
		{ 7, { 4, 5, 8 } },
		{ 8, { 4, 5, 6, 7, 9 } },
		{ 9, { 5, 6, 8 } }
	};

	unsigned int unlockPatternCount = 0;

	for (const auto key : keys)
	{
		unlockPatternCount += GetTotalUnlockPatternsHelper(keys, keyEdges, codeLength, key, std::unordered_set<unsigned int>());
	}

	return unlockPatternCount;
}

int main(int argc, char* argv[])
{
	std::cout << GetTotalUnlockPatterns(2) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}