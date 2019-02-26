#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
#include <vector>

class WordList
{
private:
	static std::vector<std::string> s_Words;

public:
	template<typename... Args>
	static void Add(Args... words)
	{
		([](std::string word)
		{
			ConvertToLower(word);
			
			if (!Contains(word))
			{
				s_Words.push_back(word);
			}
		}(words), ...);
	}

	inline static const std::vector<std::string>& GetList() { return s_Words; }

private:
	static bool Contains(const std::string& word)
	{
		for (const std::string& currentWord : s_Words)
		{
			if (word == currentWord)
			{
				return true;
			}
		}

		return false;
	}

	static void ConvertToLower(std::string& word)
	{
		std::transform(word.begin(), word.end(), word.begin(), std::tolower);
	}
};

std::vector<std::string> WordList::s_Words;

std::vector<std::string> GetAutoCompletedWords(const std::string& query, const std::vector<std::string>& wordList)
{
	std::vector<std::string> validWords;

	for (const std::string& word : wordList)
	{
		if (word.find(query) == 0)
		{
			validWords.push_back(word);
		}
	}

	return validWords;
}

template<typename T>
void PrintVector(const std::vector<T>& values)
{
	for (const T& value : values)
	{
		std::cout << value << " ";
	}

	std::cout << "\n";
}

int main(int argc, char* argv[])
{
	WordList::Add("dog", "deer", "deal");

	PrintVector(GetAutoCompletedWords("de", WordList::GetList()));

	std::cin.get();

	return 0;
}
