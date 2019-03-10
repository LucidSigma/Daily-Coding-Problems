#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

std::string GetShortestLimitedString(const std::string& string, const std::vector<char>& letters) noexcept
{
	std::string validString;

	std::vector<char> currentValidLetters;
	std::vector<unsigned int> currentValidIndices;
	std::vector<char> seenLetters;

	for (unsigned int i = 0; i < string.length(); i++)
	{
		if (std::find(std::cbegin(letters), std::cend(letters), string[i]) != std::cend(letters))
		{
			currentValidLetters.push_back(string[i]);
			currentValidIndices.push_back(i);
			seenLetters.push_back(string[i]);
		}

		unsigned int shift = 0;

		for (unsigned int j = 0; j < currentValidLetters.size() / 2; j++)
		{
			if (currentValidLetters[j] == currentValidLetters[currentValidLetters.size() - j - 1])
			{
				shift++;
			}
		}

		currentValidLetters = std::vector<char>(std::cbegin(currentValidLetters) + shift, std::cend(currentValidLetters));
		currentValidIndices = std::vector<unsigned int>(std::cbegin(currentValidIndices) + shift, std::cend(currentValidIndices));

		if (!currentValidIndices.empty() && (seenLetters.size() == letters.size() && validString.empty() ||
			(validString.length() > (currentValidIndices.back() - currentValidIndices[0] + 1))))
		{
			validString = std::string(std::cbegin(string) + currentValidIndices[0], std::cbegin(string) + currentValidIndices.back() + 1);
		}
	}

	return validString;
}

int main(int argc, char* argv[])
{
	std::cout << GetShortestLimitedString("figehaeci", { 'a', 'e', 'i' }) << "\n";

	std::cin.get();

	return 0;
}