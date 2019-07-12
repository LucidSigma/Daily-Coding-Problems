#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <optional>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

void GetLetterOrderHelper(const std::vector<std::string>& dictionary, std::unordered_map<char, std::unordered_set<char>>& letters) noexcept
{
	std::vector<char> order;
	std::unordered_map<char, std::vector<std::string>> newWords;
	char previousLetter = '\0';

	for (const auto& word : dictionary)
	{
		const char firstLetter = word[0];

		if (firstLetter != previousLetter)
		{
			order.push_back(firstLetter);
		}

		if (newWords.find(firstLetter) == std::cend(newWords))
		{
			newWords[firstLetter] = std::vector<std::string>();
		}

		newWords[firstLetter].push_back(word.substr(1));
		previousLetter = firstLetter;
	}

	for (size_t i = 0; i < order.size(); ++i)
	{
		std::vector<char> currentLetters(std::cbegin(order) + i + 1, std::cend(order));

		for (const auto letter : currentLetters)
		{
			if (letters[order[i]].find(letter) == std::cend(letters[order[i]]))
			{
				letters[order[i]].insert(letter);
			}
		}
	}

	for (const auto& [_, words] : newWords)
	{
		GetLetterOrderHelper(words, letters);
	}
}

std::optional<std::vector<char>> GetValidLetterOrder(const std::unordered_map<char, std::unordered_set<char>>& letters, const char first, std::vector<char> currentPath, const size_t currentLength) noexcept
{
	if (currentPath.size() == currentLength)
	{
		return currentPath;
	}

	if (letters.find(first) == std::cend(letters))
	{
		return std::nullopt;
	}

	for (const auto letter : letters.at(first))
	{
		currentPath.push_back(first);
		const auto nextPath = GetValidLetterOrder(letters, letter, currentPath, currentLength);

		if (nextPath != std::nullopt)
		{
			return nextPath;
		}
	}

	return std::nullopt;
}

std::vector<char> GetLetterOrder(const std::vector<std::string>& dictionary)
{
	std::unordered_map<char, std::unordered_set<char>> letters;

	for (const auto& word : dictionary)
	{
		for (const auto letter : word)
		{
			if (letters.find(letter) == std::cend(letters))
			{
				letters[letter] = std::unordered_set<char>();
			}
		}
	}

	GetLetterOrderHelper(dictionary, letters);

	size_t maxLength = 0;

	for (const auto& [_, letterSet] : letters)
	{
		maxLength = std::max(maxLength, letterSet.size());
	}

	std::vector<char> candidateLetters;

	for (const auto& [letter, letterSet] : letters)
	{
		if (letterSet.size() == maxLength)
		{
			candidateLetters.push_back(letter);
		}
	}

	for (const auto letter : candidateLetters)
	{
		const auto order = GetValidLetterOrder(letters, letter, { letter }, letters.size());

		if (order.has_value())
		{
			return order.value();
		}
	}

	throw std::invalid_argument("No order can be determined.");
}

template <typename T>
std::ostream& operator <<(std::ostream& outputStream, const std::vector<T>& values) noexcept
{
	for (const auto& value : values)
	{
		outputStream << value << " ";
	}

	return outputStream;
}

int main(int argc, char* argv[])
{
	std::cout << GetLetterOrder({ "xww", "wxyz", "wxyw", "ywx", "ywz" }) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}