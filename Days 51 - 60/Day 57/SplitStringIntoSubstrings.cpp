#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::vector<std::string> SplitString(const std::string& text, char delimiter = ' ')
{
	std::string currentToken;
	std::stringstream reader(text);

	std::vector<std::string> tokens;

	while (std::getline(reader, currentToken, delimiter))
	{
		tokens.push_back(currentToken);
	}

	return tokens;
}

std::vector<std::string> BreakStringIntoTexts(const std::string& text, unsigned int k)
{
	std::vector<std::string> texts;
	std::vector<std::string> words = SplitString(text);
	std::string currentText;

	for (const std::string& word : words)
	{
		if ((currentText + word).length() - 1 < k)
		{
			currentText += word;
		}
		else if (word.length() > k)
		{
			return { };
		}
		else
		{
			currentText.pop_back();
			texts.push_back(currentText);
			currentText = word;
		}

		currentText += ' ';
	}

	currentText.pop_back();
	texts.push_back(currentText);

	return texts;
}

template <typename T>
void PrintVector(const std::vector<T>& values)
{
	if (values.empty())
	{
		std::cout << "Vector is empty...\n";

		return;
	}

	for (unsigned int i = 0; i < values.size(); i++)
	{
		std::cout << values[i];

		if (i < values.size() - 1)
		{
			std::cout << ", ";
		}
	}

	std::cout << "\n";
}

int main(int argc, char* argv[])
{
	std::string sentence = "The quick brown fox jumps over the lazy dog.";
	PrintVector(BreakStringIntoTexts(sentence, 10));

	sentence = "12345678910";
	PrintVector(BreakStringIntoTexts(sentence, 10));

	std::cin.get();

	return 0;
}