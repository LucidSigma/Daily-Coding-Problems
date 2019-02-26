#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
#include <vector>

bool HasNoExcessUniqueCharacters(const std::vector<unsigned int>& characterCount, unsigned int k)
{
	unsigned int uniqueCharacters = 0;

	for (unsigned int count : characterCount)
	{
		if (count > 0)
		{
			uniqueCharacters++;
		}
	}

	return k >= uniqueCharacters;
}

unsigned int GetMaxLengthOfDistinctSubstring(const std::string& string, unsigned int k)
{
	std::string lowerCase = string;
	std::transform(lowerCase.begin(), lowerCase.end(), lowerCase.begin(), std::tolower);

	unsigned int uniqueCharacters = 0;
	unsigned int length = lowerCase.length();

	constexpr unsigned int CHARS_IN_ALPHABET = 26;
	std::vector<unsigned int> characterCounts(CHARS_IN_ALPHABET, 0);

	unsigned int (* charToInt)(char) = [](char character) -> unsigned int
	{
		return character - 'a';
	};

	for (unsigned int i = 0; i < length; i++)
	{
		if (characterCounts[charToInt(lowerCase[i])] == 0)
		{
			uniqueCharacters++;
		}

		characterCounts[charToInt(lowerCase[i])]++;
	}

	if (uniqueCharacters < k)
	{
		std::cout << string << "\n";

		return length;
	}

	int start = 0;
	int end = 0;
	int startEndDifference = 1;
	int maxStart = 0;

	std::fill(characterCounts.begin(), characterCounts.end(), 0);
	characterCounts[charToInt(lowerCase[0])]++;

	for (unsigned int i = 1; i < length; i++)
	{
		characterCounts[charToInt(lowerCase[i])]++;
		end++;

		while (!HasNoExcessUniqueCharacters(characterCounts, k))
		{
			characterCounts[charToInt(lowerCase[start])]--;
			start++;
		}

		if ((end - start + 1) > startEndDifference)
		{
			startEndDifference = end - start + 1;
			maxStart = start;
		}
	}

	std::cout << string.substr(maxStart, startEndDifference) << "\n";

	return startEndDifference;
}

int main(int argc, char* argv[])
{
	std::cout << GetMaxLengthOfDistinctSubstring("ifjhfunjfjsfhkshjsnjc", 5) << "\n";

	std::cin.get();

	return 0;
}
