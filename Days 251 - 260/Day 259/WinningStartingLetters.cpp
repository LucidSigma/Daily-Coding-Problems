#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <string>
#include <unordered_map>
#include <unordered_set>

std::unordered_set<char> GetWinningStartingLetters(const std::unordered_set<std::string>& dictionary)
{
	std::unordered_map<char, std::unordered_set<size_t>> startingLetterLengths;

	for (const auto& word : dictionary)
	{
		const char firstLetter = word.front();

		if (startingLetterLengths.find(firstLetter) == std::cend(startingLetterLengths))
		{
			startingLetterLengths[firstLetter] = { };
		}

		startingLetterLengths[firstLetter].insert(word.size());
	}

	std::unordered_set<char> winningStartingLetters;

	for (const auto& [letter, lengths] : startingLetterLengths)
	{
		bool isWinningStartingLetter = true;

		for (const auto length : lengths)
		{
			if (length % 2 != 0)
			{
				isWinningStartingLetter = false;

				break;
			}
		}

		if (isWinningStartingLetter)
		{
			winningStartingLetters.insert(letter);
		}
	}

	return winningStartingLetters;
}

template <typename T>
std::ostream& operator <<(std::ostream& outputStream, const std::unordered_set<T>& values)
{
	for (const auto& value : values)
	{
		outputStream << value << " ";
	}

	return outputStream;
}

int main(int argc, char* argv[])
{
	std::cout << GetWinningStartingLetters({ "cat", "calf", "dog", "bear" }) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}