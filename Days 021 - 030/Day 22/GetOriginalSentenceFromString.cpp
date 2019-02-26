#include <iostream>
#include <set>
#include <string>
#include <vector>

std::vector<std::string> GetOriginalSentence(const std::string& sentence, const std::set<std::string>& dictionary)
{
	std::string searchString = sentence;
	std::vector<std::string> words;

	while (searchString != "")
	{
		bool wordFound = false;

		for (const auto& word : dictionary)
		{
			if (searchString.find(word) == 0)
			{
				words.push_back(word);

				searchString = searchString.substr(word.length());
				wordFound = true;
			}
		}

		if (!wordFound)
		{
			return std::vector<std::string> { };
		}
	}

	return words;
}

template <typename T>
void PrintVector(const std::vector<T>& values) noexcept
{
	if (values.empty())
	{
		std::cout << "Empty vector...";
	}

	for (const auto& value : values)
	{
		std::cout << value << " ";
	}

	std::cout << "\n";
}

int main(int argc, const char* argv[])
{
	std::set<std::string> dictionary { "quick", "brown", "the", "fox" };
	std::string sentence = "thequickbrownfox";

	PrintVector(GetOriginalSentence(sentence, dictionary));

	std::set<std::string> secondDictionary { "bed", "bath", "bedbath", "and", "beyond" };
	std::string secondSentence = "bedbathandbeyond";

	PrintVector(GetOriginalSentence(secondSentence, secondDictionary));

	std::set<std::string> thirdDictionary { "this", "will", "return", "an", "empty", "vector" };
	std::string thirdSentence = "nodictionarywordsinhere";

	PrintVector(GetOriginalSentence(thirdSentence, thirdDictionary));

	std::cin.get();

	return 0;
}