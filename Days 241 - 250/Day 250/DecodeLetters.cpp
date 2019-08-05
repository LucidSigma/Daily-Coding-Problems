#include <cmath>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <iterator>
#include <optional>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

unsigned int StringToNumber(const std::unordered_map<char, unsigned int>& letterValues, const std::string& string)
{
	unsigned int result = 0;
	unsigned int magnitude = 0;

	for (auto it = std::crbegin(string); it != std::crend(string); ++it)
	{
		result += letterValues.at(*it) * static_cast<unsigned int>(std::pow(10, magnitude));
		++magnitude;
	}

	return result;
}

std::optional<std::unordered_map<char, unsigned int>> GetValidLetterValues(const std::pair<std::string, std::string>& operands, const std::string& result, const std::function<unsigned int(unsigned int, unsigned int)>& operation, const std::vector<std::unordered_map<char, unsigned int>>& candidateLetterValues)
{
	const auto isValid = [&operands, &result, &operation](const std::unordered_map<char, unsigned int>& letterValues)
	{
		const auto firstOperandValue = StringToNumber(letterValues, operands.first);
		const auto secondOperandValue = StringToNumber(letterValues, operands.second);
		const auto resultValue = StringToNumber(letterValues, result);

		return operation(firstOperandValue, secondOperandValue) == resultValue;
	};

	for (const auto& letterValues : candidateLetterValues)
	{
		if (isValid(letterValues))
		{
			return letterValues;
		}
	}

	return { };
}

std::vector<std::unordered_map<char, unsigned int>> DetermineLetterValues(std::unordered_set<char> remainingLetters, std::set<unsigned int> remainingNumbers, const std::unordered_map<char, std::unordered_set<unsigned int>>& restrictions, std::unordered_map<char, unsigned int> letterValues)
{
	if (remainingLetters.empty())
	{
		return { letterValues };
	}

	const char currentCharacter = *std::cbegin(remainingLetters);
	std::vector<std::unordered_map<char, unsigned int>> letterMappings;

	for (const auto number : remainingNumbers)
	{
		if (restrictions.at(currentCharacter).find(number) == std::cend(restrictions.at(currentCharacter)))
		{
			continue;
		}

		letterValues[currentCharacter] = number;
		remainingLetters.erase(currentCharacter);
		remainingNumbers.erase(number);

		const auto successiveLetterValues = DetermineLetterValues(remainingLetters, remainingNumbers, restrictions, letterValues);

		letterMappings.insert(std::cend(letterMappings), std::cbegin(successiveLetterValues), std::cend(successiveLetterValues));
	}

	return letterMappings;
}

std::optional<std::unordered_map<char, unsigned int>> DecodeLetters(const std::pair<std::string, std::string>& operands, const std::string& result, const std::function<unsigned int(unsigned int, unsigned int)>& operation = std::plus<unsigned int>())
{
	const std::vector<std::string> strings{ operands.first, operands.second, result };

	const std::unordered_set<char> letters = [&strings]()
	{
		std::unordered_set<char> letters;

		for (const auto& string : strings)
		{
			for (const auto letter : string)
			{
				if (letters.find(letter) == std::cend(letters))
				{
					letters.insert(letter);
				}
			}
		}

		return letters;
	}();

	if (letters.size() > 10)
	{
		return { };
	}

	std::set<unsigned int> numbers;
	
	for (unsigned int i = 0; i < 10; ++i)
	{
		numbers.insert(i);
	}

	std::unordered_map<char, std::unordered_set<unsigned int>> restrictions;

	for (const auto letter : letters)
	{
		restrictions[letter] = std::unordered_set<unsigned int>{ };
	}

	for (const auto& string : strings)
	{
		restrictions[string.front()].insert(0);
	}

	const auto possibleLetterValues = DetermineLetterValues(letters, numbers, restrictions, std::unordered_map<char, unsigned int>());

	return GetValidLetterValues(operands, result, operation, possibleLetterValues);
}

template <typename Key, typename Value>
std::ostream& operator <<(std::ostream& outputStream, const std::unordered_map<Key, Value>& map)
{
	for (const auto& [key, value] : map)
	{
		outputStream << key << " : " << value << "\n";
	}

	return outputStream;
}

int main(int argc, char* argv[])
{
	std::cout << DecodeLetters({ "SEND", "MORE" }, "MONEY").value_or(std::unordered_map<char, unsigned int>{ }) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}