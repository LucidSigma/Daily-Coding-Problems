#include <cstdlib>
#include <iostream>
#include <iterator>
#include <string>
#include <unordered_map>
#include <utility>

std::unordered_map<char, unsigned int> GetCharacterCounts(const std::string& word)
{
	std::unordered_map<char, unsigned int> characterCounts;

	for (const auto letter : word)
	{
		if (characterCounts.find(letter) == std::cend(characterCounts))
		{
			characterCounts[letter] = 0;
		}

		++characterCounts[letter];
	}

	return characterCounts;
}

std::pair<std::unordered_map<char, unsigned int>, unsigned int> UseNumber(std::unordered_map<char, unsigned int> characterCounts, const std::unordered_map<char, unsigned int>& numberWordCounts, const unsigned int number)
{
	for (const auto [letter, count] : numberWordCounts)
	{
		if (characterCounts.find(letter) == std::cend(characterCounts) || count > characterCounts[letter])
		{
			return { characterCounts, 0 };
		}
	}

	for (const auto [letter, count] : numberWordCounts)
	{
		characterCounts[letter] -= count;
	}

	const auto [successiveCharacterCounts, successiveNumberUses] = UseNumber(characterCounts, numberWordCounts, number);

	return { successiveCharacterCounts, successiveNumberUses + 1 };
}

unsigned int RearrangeIntoNumber(const std::string& jumbledNumber)
{
	auto characterCounts = GetCharacterCounts(jumbledNumber);
	unsigned int number = 0;

	for (unsigned int i = 0; i < 9; ++i)
	{
		static const std::unordered_map<unsigned int, std::string> numberWordMap
		{
			{ 0, "zero" },
			{ 1, "one" },
			{ 2, "two" },
			{ 3, "three" },
			{ 4, "four" },
			{ 5, "five" },
			{ 6, "six" },
			{ 7, "seven" },
			{ 8, "eight" },
			{ 9, "nine" }
		};

		const std::string& currentNumberWord = numberWordMap.at(i);
		const auto numberWordCharacterCounts = GetCharacterCounts(currentNumberWord);
		auto [newCharacterCounts, numberUses] = UseNumber(characterCounts, numberWordCharacterCounts, i);
		characterCounts = newCharacterCounts;

		while (numberUses > 0)
		{
			number *= 10;
			number += i;

			--numberUses;
		}
	}

	return number;
}

int main(const int argc, const char* const argv[])
{
	std::cout << RearrangeIntoNumber("niesevehrtfeev") << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}