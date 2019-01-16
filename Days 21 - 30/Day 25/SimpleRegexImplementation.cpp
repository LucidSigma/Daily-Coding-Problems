#include <iostream>
#include <string>
#include <vector>

bool MatchSimpleRegex(const std::string& regex, const std::string& text)
{
	std::vector<std::vector<bool>> matches(text.length() + 1, std::vector<bool>(regex.length() + 1));
	matches[0][0] = true;

	static constexpr char SINGLE_CHARACTER = '.';
	static constexpr char MULTIPLE_CHARACTERS = '*';

	for (unsigned int i = 1; i < matches[0].size(); i++)
	{
		if (regex[i - 1] == MULTIPLE_CHARACTERS)
		{
			matches[0][i] = matches[0][i - 2];
		}
	}

	for (unsigned int i = 1; i < matches.size(); i++)
	{
		for (unsigned int j = 1; j < matches[i].size(); j++)
		{
			if ((regex[j - 1] == SINGLE_CHARACTER) || (regex[j - 1] == text[i - 1]))
			{
				matches[i][j] = matches[i - 1][j - 1];
			}
			else if (regex[j - 1] == MULTIPLE_CHARACTERS)
			{
				matches[i][j] = matches[i][j - 2];

				if ((regex[j - 2] == SINGLE_CHARACTER) || (regex[j - 2] == text[i - 1]))
				{
					matches[i][j] = matches[i][j] || matches[i - 1][j];
				}
			}
			else
			{
				matches[i][j] = false;
			}
		}
	}

	return matches[text.length()][regex.length()];
}

int main(int argc, const char* argv[])
{
	std::cout << std::boolalpha;

	std::cout << MatchSimpleRegex(".*at", "chat") << "\n";
	std::cout << MatchSimpleRegex(".*at", "chats") << "\n";

	std::cout << MatchSimpleRegex("ra.", "ray") << "\n";
	std::cout << MatchSimpleRegex("ra.", "raymond") << "\n";

	std::cout << MatchSimpleRegex(".*", "aaaaaaaaaaaaaa") << "\n";
	std::cout << MatchSimpleRegex(".", "aaaaaaaaaaaaaa") << "\n";
	
	std::cin.get();

	return 0;
}
