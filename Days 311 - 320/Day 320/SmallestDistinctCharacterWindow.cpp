#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <limits>
#include <unordered_set>
#include <string>

std::unordered_set<char> StringToUnorderedSet(const std::string& string)
{
	std::unordered_set<char> distinctLetters;

	for (const auto letter : string)
	{
		if (distinctLetters.find(letter) == std::cend(distinctLetters))
		{
			distinctLetters.insert(letter);
		}
	}

	return distinctLetters;
}

unsigned int SmallestDistinctCharacterWindowLengthHelper(const std::string& string, const std::unordered_set<char>& distinctLetters, const size_t startIndex, const size_t endIndex)
{
	const std::string currentString = string.substr(startIndex, endIndex);

	if (startIndex == endIndex || StringToUnorderedSet(currentString).size() < distinctLetters.size())
	{
		return std::numeric_limits<unsigned int>::max();
	}

	const unsigned int leftWindow = SmallestDistinctCharacterWindowLengthHelper(string, distinctLetters, startIndex, endIndex - 1);
	const unsigned int rightWindow = SmallestDistinctCharacterWindowLengthHelper(string, distinctLetters, startIndex + 1, endIndex);

	return std::min(currentString.length(), std::min(leftWindow, rightWindow));
}

inline unsigned int SmallestDistinctCharacterWindowLength(const std::string& string)
{
	if (string.empty())
	{
		return 0;
	}

	return SmallestDistinctCharacterWindowLengthHelper(string, StringToUnorderedSet(string), 0, string.length());
}

int main(const int argc, const char* const argv[])
{
	std::cout << SmallestDistinctCharacterWindowLength("jiujitsu") << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}