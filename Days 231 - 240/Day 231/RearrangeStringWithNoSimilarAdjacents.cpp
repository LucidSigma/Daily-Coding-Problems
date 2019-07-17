#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <map>
#include <optional>
#include <queue>
#include <string>
#include <vector>

std::optional<std::string> RearrageAdjacentCharacters(const std::string& string) noexcept
{
	std::map<char, unsigned int> letterCounter;

	for (const auto letter : string)
	{
		if (letterCounter.find(letter) == std::cend(letterCounter))
		{
			letterCounter[letter] = 0;
		}

		++letterCounter[letter];
	}

	std::vector<std::pair<char, unsigned int>> sortedCounts;

	for (const auto& letterCount : letterCounter)
	{
		sortedCounts.push_back(letterCount);
	}

	std::sort(std::begin(sortedCounts), std::end(sortedCounts), [](const std::pair<char, unsigned int>& lhs, const std::pair<char, unsigned int>& rhs) noexcept
		{
			return lhs.second > rhs.second;
		}
	);

	if (string.length() % 2 != 0)
	{
		if (sortedCounts[0].second > (string.length() / 2) + 1)
		{
			return std::nullopt;
		}
	}
	else
	{
		if (sortedCounts[0].second > (string.length() / 2))
		{
			return std::nullopt;
		}
	}

	std::queue<std::pair<char, unsigned int>> letterQueue;

	for (const auto& letterCount : sortedCounts)
	{
		letterQueue.push(letterCount);
	}

	std::string rearrangedString;

	while (!letterQueue.empty())
	{
		auto& [letter, letterCount] = letterQueue.front();
		rearrangedString += letter;

		--letterCount;

		if (letterCount == 0)
		{
			letterQueue.pop();
		}
	}

	return rearrangedString;
}

int main(int argc, char* argv[])
{
	std::cout << RearrageAdjacentCharacters("aaabbc").value_or("None") << "\n";
	std::cout << RearrageAdjacentCharacters("aaab").value_or("None") << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}