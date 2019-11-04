#include <cstddef>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <iterator>
#include <optional>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

template <typename T>
using Matrix = std::vector<std::vector<T>>;

using Coordinate = std::pair<size_t, size_t>;
using WordChain = std::unordered_set<Coordinate>;

namespace std
{
	template <>
	struct hash<Coordinate>
	{
		inline size_t operator ()(const Coordinate& coordinate) const noexcept
		{
			return (coordinate.first << 15) ^ coordinate.second;
		}
	};
}

std::vector<Coordinate> GetAdjacentCoordinates(const Matrix<char>& matrix, const size_t row, const size_t column, const std::unordered_set<Coordinate>& usedCoordinates)
{
	std::vector<Coordinate> adjacentCoordinates;

	if (row > 0)
	{
		if (const Coordinate coordinate{ row - 1, column };
			usedCoordinates.find(coordinate) == std::cend(usedCoordinates))
		{
			adjacentCoordinates.emplace_back(coordinate);
		}
	}

	if (row < matrix.size() - 1)
	{
		if (const Coordinate coordinate{ row + 1, column };
			usedCoordinates.find(coordinate) == std::cend(usedCoordinates))
		{
			adjacentCoordinates.emplace_back(coordinate);
		}
	}

	if (column > 0)
	{
		if (const Coordinate coordinate{ row, column - 1 };
			usedCoordinates.find(coordinate) == std::cend(usedCoordinates))
		{
			adjacentCoordinates.emplace_back(coordinate);
		}
	}

	if (column < matrix.front().size() - 1)
	{
		if (const Coordinate coordinate{ row, column + 1 };
			usedCoordinates.find(coordinate) == std::cend(usedCoordinates))
		{
			adjacentCoordinates.emplace_back(coordinate);
		}
	}

	return adjacentCoordinates;
}

std::vector<std::pair<bool, WordChain>> GetWordCreationChains(const Coordinate& start, const std::string& word, const Matrix<char>& matrix, WordChain currentChain)
{
	if (word.empty())
	{
		return { { true, currentChain } };
	}

	if (matrix[start.first][start.second] != word.front())
	{
		return { { false, { } } };
	}

	currentChain.insert(start);
	const auto adjacentCoordinates = GetAdjacentCoordinates(matrix, start.first, start.second, currentChain);

	std::vector<std::pair<bool, WordChain>> results;

	for (const auto& adjacentCoordinate : adjacentCoordinates)
	{
		const auto currentResult = GetWordCreationChains(adjacentCoordinate, word.substr(1), matrix, currentChain);
		results.insert(std::cend(results), std::cbegin(currentResult), std::cend(currentResult));
	}

	return results;
}

std::vector<std::vector<std::string>> GetWordCombinations(const std::unordered_set<std::string>& words, const size_t combinationSize)
{
	if (words.size() == 1)
	{
		return { { *std::cbegin(words) } };
	}
	else if (combinationSize == 0)
	{
		return { };
	}

	std::vector<std::vector<std::string>> wordCombinations;

	for (const auto& word : words)
	{
		std::unordered_set<std::string> remainingWords = words;
		remainingWords.erase(word);
		std::vector<std::vector<std::string>> subsequentCombinations = GetWordCombinations(remainingWords, combinationSize - 1);

		for (const auto& subsequentCombination : subsequentCombinations)
		{
			std::vector<std::string> currentCombination = { word };
			currentCombination.insert(std::cend(currentCombination), std::cbegin(subsequentCombination), std::cend(subsequentCombination));

			wordCombinations.push_back(currentCombination);
		}
	}

	return wordCombinations;
}

unsigned int GetMostWordsOnMatrix(const Matrix<char>& matrix, const std::unordered_set<std::string>& dictionary)
{
	std::unordered_map<std::string, std::vector<WordChain>> wordChains;

	for (const auto& word : dictionary)
	{
		wordChains[word] = { };

		for (size_t i = 0; i < matrix.size(); ++i)
		{
			for (size_t j = 0; j < matrix.front().size(); ++j)
			{
				const auto currentWordChains = GetWordCreationChains({ i, j }, word, matrix, { });
				
				for (const auto& [canCreateWord, wordChain] : currentWordChains)
				{
					if (canCreateWord)
					{
						wordChains[word].push_back(wordChain);
					}
				}
			}
		}
	}

	unsigned int maxWordCount = dictionary.size();

	while (maxWordCount > 0)
	{
		std::unordered_set<Coordinate> usedWords;
		const auto wordCombinations = GetWordCombinations(dictionary, maxWordCount);

		for (const auto& combination : wordCombinations)
		{
			unsigned int wordCount = 0;

			for (const auto& word : combination)
			{
				bool isNewWord = false;
				std::optional<WordChain> selectedWordChain = std::nullopt;

				for (const auto& wordChain : wordChains[word])
				{
					if (!usedWords.empty())
					{
						continue;
					}

					isNewWord = true;
					selectedWordChain = wordChain;
				}

				if (isNewWord)
				{
					for (const auto& coordinate : selectedWordChain.value())
					{
						if (usedWords.find(coordinate) == std::cend(usedWords))
						{
							usedWords.insert(coordinate);
						}
					}

					++wordCount;
				}
			}

			if (wordCount == maxWordCount)
			{
				return maxWordCount;
			}
		}

		--maxWordCount;
	}

	return 1;
}

int main(const int argc, const char* const argv[])
{
	const Matrix<char> matrix
	{
		{ 'e', 'a', 'n' },
		{ 't', 't', 'i' },
		{ 'a', 'r', 'a' }
	};

	const std::unordered_set<std::string> dictionary
	{
		"eat", "rain", "in", "rat"
	};

	std::cout << GetMostWordsOnMatrix(matrix, dictionary) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}