#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

std::vector<std::string> SplitString(const std::string& text, char delimiter = ' ') noexcept
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

inline std::vector<std::string> ReverseVector(std::vector<std::string>&& strings) noexcept
{
	return std::reverse(std::begin(strings), std::end(strings)), strings;
}

std::string JoinVectorOfStrings(const std::vector<std::string>& strings, char delimiter = ' ') noexcept
{
	std::string joinedString;

	for (unsigned int i = 0; i < strings.size(); i++)
	{
		joinedString += strings[i];

		if (i < strings.size() - 1)
		{
			joinedString += delimiter;
		}
	}

	return joinedString;
}

inline std::string ReverseWordsOfString(const std::string& string) noexcept
{
	return JoinVectorOfStrings(ReverseVector(SplitString(string)));
}

int main(int argc, char* argv[])
{
	std::cout << ReverseWordsOfString("hello world here") << "\n";

	std::cin.get();

	return 0;
}
