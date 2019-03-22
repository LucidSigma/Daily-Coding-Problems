#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

std::pair<std::vector<std::string>, std::vector<char>> SplitStringFromDelimiters(const std::string& words, const std::unordered_set<char>& delimiters) noexcept
{
	std::vector<std::string> wordList;
	std::vector<char> delimiterList;

	std::string currentWord;

	for (const char letter : words)
	{
		if (delimiters.find(letter) != std::cend(delimiters))
		{
			wordList.push_back(currentWord);
			delimiterList.push_back(letter);

			currentWord = "";
		}
		else
		{
			currentWord += letter;
		}
	}

	wordList.push_back(currentWord);

	return { wordList, delimiterList };
}

std::string ReverseWordsWithDelimiters(const std::string& words, const std::unordered_set<char>& delimiters) noexcept
{
	auto[wordList, delimiterList] = SplitStringFromDelimiters(words, delimiters);
	std::reverse(std::begin(wordList), std::end(wordList));

	std::string reversedString;

	for (unsigned int i = 0; i < wordList.size(); i++)
	{
		reversedString += wordList[i];

		if (i < delimiterList.size())
		{
			reversedString += delimiterList[i];
		}
	}

	return reversedString;
}

int main(int argc, char* argv[])
{
	std::cout << ReverseWordsWithDelimiters("hello/world:here", { '/', ':' }) << "\n";
	std::cout << ReverseWordsWithDelimiters("hello/world:here/", { '/', ':' }) << "\n";
	std::cout << ReverseWordsWithDelimiters("hello//world:here", { '/', ':' }) << "\n";

	std::cin.get();

	return 0;
}