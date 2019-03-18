#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

bool IsAnagram(std::string stringA, std::string stringB) noexcept
{
	std::sort(std::begin(stringA), std::end(stringA));
	std::sort(std::begin(stringB), std::end(stringB));

	return stringA == stringB;
}

std::vector<unsigned int> GetAnagramIndices(const std::string& word, const std::string& string) noexcept
{
	std::vector<unsigned int> anagramIndices;

	for (unsigned int i = 0; i < string.size() - word.size() + 1; i++)
	{
		std::string currentSubstring = string.substr(i, word.size());

		if (IsAnagram(word, currentSubstring))
		{
			anagramIndices.push_back(i);
		}
	}

	return anagramIndices;
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
	PrintVector(GetAnagramIndices("ab", "abxaba"));

	std::cin.get();

	return 0;
}