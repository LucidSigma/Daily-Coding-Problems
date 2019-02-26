#include <iostream>
#include <map>
#include <string>
#include <vector>

static std::map<char, std::vector<std::string>> digitLetterMappings
{
	{ '2', { "a", "b", "c" } },
	{ '3', { "d", "e", "f" } },
	{ '4', { "g", "h", "i" } },
	{ '5', { "j", "k", "l" } },
	{ '6', { "m", "n", "o" } },
	{ '7', { "p", "q", "r", "s" } },
	{ '8', { "t", "u", "v" } },
	{ '9', { "w", "x", "y", "z" } }
};

std::vector<std::string> GetAllPossibleStrings(const std::string& digits) noexcept
{
	if (digits.empty())
	{
		return { };
	}
	else if (digits.length() == 1)
	{
		return digitLetterMappings[digits[0]];
	}

	std::vector<std::string> letterStrings;
	auto currentLetters = digitLetterMappings[digits[0]];
	auto succeedingLetterStrings = GetAllPossibleStrings(digits.substr(1));

	for (const std::string& letter : currentLetters)
	{
		for (const std::string& letterString : succeedingLetterStrings)
		{
			letterStrings.push_back(letter + letterString);
		}
	}

	return letterStrings;
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
	PrintVector(GetAllPossibleStrings("23"));
	PrintVector(GetAllPossibleStrings("8746"));

	std::cin.get();

	return 0;
}