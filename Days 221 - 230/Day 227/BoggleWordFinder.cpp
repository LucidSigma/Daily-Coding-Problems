#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <string>
#include <type_traits>
#include <vector>

static constexpr size_t GridSize = 4u;

using Dictionary = std::vector<std::string>;
using BoggleGrid = std::array<std::array<char, GridSize>, GridSize>;
using VisitedGrid = std::array<std::array<bool, GridSize>, GridSize>;

inline bool IsValidWord(const std::string& word, const Dictionary& dictionary) noexcept
{
	return std::find(std::cbegin(dictionary), std::cend(dictionary), word) != std::cend(dictionary);
}

void FindAllWordsHelper(const BoggleGrid& boggleGrid, VisitedGrid& visited, const Dictionary& dictionary, std::vector<std::string>& validWords, const size_t i, const size_t j, std::string& currentWord) noexcept
{
	visited[i][j] = true;
	currentWord += boggleGrid[i][j];

	if (IsValidWord(currentWord, dictionary))
	{
		validWords.push_back(currentWord);
	}

	for (int row = i - 1; row <= static_cast<int>(i + 1); ++row)
	{
		for (int column = j - 1; column <= static_cast<int>(j + 1); ++column)
		{
			if (row < GridSize && column < GridSize && row >= 0 && column >= 0 && !visited[row][column])
			{
				FindAllWordsHelper(boggleGrid, visited, dictionary, validWords, row, column, currentWord);
			}
		}
	}

	currentWord.pop_back();
	visited[i][j] = false;
}

std::vector<std::string> FindAllWords(const BoggleGrid& boggleGrid, const Dictionary& dictionary) noexcept
{
	std::string currentWord;
	std::vector<std::string> validWords;

	for (size_t i = 0; i < GridSize; ++i)
	{
		for (size_t j = 0; j < GridSize; ++j)
		{
			VisitedGrid visitedCells{ std::array<bool, GridSize>{ false } };

			FindAllWordsHelper(boggleGrid, visitedCells, dictionary, validWords, i, j, currentWord);
		}
	}

	return validWords;
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
	const Dictionary dictionary
	{
		"AUTO", "SHORT", "RETURN", "EXPLICIT", "CATCH", "ALIGNAS", "FOR", "WHILE", "NOEXCEPT", "INLINE"
	};

	const BoggleGrid boggleGrid
	{
		std::array<char, GridSize>{ 'A', 'C', 'X', 'E' },
		std::array<char, GridSize>{ 'T', 'C', 'P', 'N' },
		std::array<char, GridSize>{ 'F', 'H', 'L', 'I' },
		std::array<char, GridSize>{ 'Q', 'T', 'I', 'C' },
	};

	std::cout << FindAllWords(boggleGrid, dictionary) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}