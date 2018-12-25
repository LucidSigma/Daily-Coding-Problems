#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::vector<std::string> JustifyText(const std::vector<std::string>& words, int lineLength)
{
	std::vector<std::vector<std::string>> wordsEachLine;
	std::string currentLine;
	std::vector<std::string> currentWordsInLine;

	for (const auto& word : words)
	{
		if ((currentLine + word).length() + 1 <= lineLength)
		{
			currentLine += word + ' ';

			currentWordsInLine.push_back(word);
		}
		else
		{
			wordsEachLine.push_back(currentWordsInLine);
			currentWordsInLine.clear();

			currentLine = word;
			currentWordsInLine.push_back(word);
		}

		if (word == words[words.size() - 1])
		{
			wordsEachLine.push_back(currentWordsInLine);
		}
	}

	std::vector<std::string> justifiedLines;

	for (const auto& line : wordsEachLine)
	{
		if (line.size() > 1)
		{
			unsigned int length = 0;

			for (const auto& word : line)
			{
				length += word.length();
			}

			unsigned int difference = lineLength - length;
			unsigned int spaceSize = difference / (line.size() - 1);
			unsigned int extraSpace = lineLength - length - ((line.size() - 1) * spaceSize);

			std::string justifiedLine;

			for (const auto& word : line)
			{
				justifiedLine += word;
				justifiedLine += (extraSpace > 0) ? std::string(spaceSize + 1, ' ') : std::string(spaceSize, ' ');

				if (extraSpace > 0)
				{
					extraSpace--;
				}
			}

			justifiedLines.push_back(justifiedLine);
		}
		else
		{
			justifiedLines.push_back(line[0] + std::string(lineLength - line[0].length(), ' '));
		}
	}

	return justifiedLines;
}


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

template <typename T>
void PrintVector(const std::vector<T>& values, char delimiter = ' ') noexcept
{
	for (const auto& value : values)
	{
		std::cout << value << delimiter;
	}
}

int main(int argc, const char* argv[])
{
	std::vector<std::string> words = SplitString("The quick brown fox jumps over the lazy dog");
	std::vector<std::string> lines = JustifyText(words, 16);

	PrintVector(lines, '\n');
	
	std::cin.get();

	return 0;
}