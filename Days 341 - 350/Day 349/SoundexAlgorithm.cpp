#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <iterator>
#include <locale>
#include <unordered_map>
#include <unordered_set>
#include <string>

namespace std
{
	template <>
	struct hash< std::unordered_set<char>>
	{
		inline size_t operator ()(const std::unordered_set<char>& set) const noexcept
		{
			return (std::hash<size_t>()(set.size()) << 8) ^ std::hash<char>()(*std::cbegin(set));
		}
	};
}

std::string GetSoundexCode(const std::string& name)
{
	std::string removedConsonants = name;

	std::transform(std::begin(removedConsonants), std::end(removedConsonants), std::begin(removedConsonants), [](const char letter)
	{
		return std::tolower(letter, std::locale());
	});

	static const std::unordered_map<std::string, std::string> similarConsonants
	{
		{ "ck", "c" },
		{ "ph", "f" },
		{ "ce", "s" },
		{ "ci", "s" },
		{ "cy", "s" },
		{ "cs", "x" },
		{ "ks", "x" },
		{ "cx", "x" }
	};

	for (const auto& [pattern, newLetter] : similarConsonants)
	{
		size_t index = removedConsonants.find(pattern);

		while (index != std::string::npos)
		{
			removedConsonants.replace(index, 2, newLetter);

			index = removedConsonants.find(pattern);
		}
	}

	for (char c = 'a'; c <= 'z'; ++c)
	{
		std::string doubleLetter(2, c);

		size_t index = removedConsonants.find(doubleLetter);

		while (index != std::string::npos)
		{
			removedConsonants.replace(index, 2, std::string(1, c));

			index = removedConsonants.find(doubleLetter);
		}
	}

	static const std::unordered_set<char> vowels
	{
		'a', 'e', 'h', 'i', 'o', 'u', 'w', 'y'
	};

	std::string removedVowels(1, removedConsonants.front());

	for (size_t i = 1; i < removedConsonants.size(); ++i)
	{
		if (vowels.find(removedConsonants[i]) == std::cend(vowels))	
		{
			removedVowels += removedConsonants[i];
		}
	}

	static const std::unordered_map<std::unordered_set<char>, unsigned int> letterDigits
	{
		{ { 'b', 'f', 'p', 'v' }, 1 },
		{ { 'c', 'g', 'j', 'k', 'q', 's', 'x', 'z' }, 2 },
		{ { 'd', 't' }, 3 },
		{ { 'l' }, 4 },
		{ { 'm', 'n' }, 5 },
		{ { 'r' }, 6 }
	};

	std::string soundex = std::string(1, removedVowels.front()) + "000";

	for (size_t i = 1; i < removedVowels.size() || i < 4; ++i)
	{
		for (const auto& [letters, digit] : letterDigits)
		{
			if (letters.find(removedVowels[i]) != std::cend(letters))
			{
				soundex[i] = digit + '0';

				break;
			}
		}
	}

	return soundex;
}

int main(const int argc, const char* const argv[])
{
	std::cout << GetSoundexCode("Jackson") << "\n";
	std::cout << GetSoundexCode("Jaxon") << "\n";
	
	std::cin.get();

	return EXIT_SUCCESS;
}