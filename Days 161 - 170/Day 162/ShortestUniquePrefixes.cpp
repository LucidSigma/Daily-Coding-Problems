#include <iostream>
#include <initializer_list>
#include <iterator>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

class WordTrie
{
private:
	unsigned int size = 0;
	std::unordered_map<char, std::shared_ptr<WordTrie>> letterMap;

public:
	explicit WordTrie() noexcept
	{ }

	explicit WordTrie(const std::initializer_list<std::string>& words) noexcept
	{
		AddWords(words);
	}

	void AddWord(const std::string& word) noexcept
	{
		if (word.empty())
		{
			return;
		}

		const char firstLetter = word[0];
		std::shared_ptr<WordTrie> subWordTrie;

		if (letterMap.find(firstLetter) != std::cend(letterMap))
		{
			subWordTrie = letterMap[firstLetter];
		}
		else
		{
			subWordTrie = std::make_shared<WordTrie>();
			letterMap[firstLetter] = subWordTrie;
		}

		++size;
		subWordTrie->AddWord(word.substr(1));
	}

	void AddWords(const std::initializer_list<std::string>& words) noexcept
	{
		for (const auto& word : words)
		{
			AddWord(word);
		}
	}

	std::string GetShortestUniquePrefix(const std::string& word, const std::string& aggregateWord = "") noexcept
	{
		if (size < 2)
		{
			return aggregateWord;
		}

		const char firstLetter = word[0];
		const auto subWordTrie = letterMap[firstLetter];

		return subWordTrie->GetShortestUniquePrefix(word.substr(1), aggregateWord + firstLetter);
	}
};

std::vector<std::string> GetShortestUniquePrefixes(const std::initializer_list<std::string>& words) noexcept
{
	WordTrie wordTrie{ words };
	std::vector<std::string> shortestUniquePrefixes;

	for (const auto& word : words)
	{
		shortestUniquePrefixes.push_back(wordTrie.GetShortestUniquePrefix(word));
	}

	return shortestUniquePrefixes;
}

template <typename T>
void PrintVector(const std::vector<T>& values) noexcept
{

	for (const auto& value : values)
	{
		std::cout << value << " ";
	}

	std::cout << "\n";
}

int main(int argc, char* argv[])
{
	PrintVector(GetShortestUniquePrefixes({ "dog", "cat", "apple", "apricot", "fish" }));

	std::cin.get();

	return 0;
}