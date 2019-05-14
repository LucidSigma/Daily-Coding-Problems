#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <utility>
#include <vector>

using IndexPair = std::pair<unsigned int, unsigned int>;

bool IsPalindrome(const std::string& word) noexcept
{
	std::string reversedWord{ word };
	std::reverse(std::begin(reversedWord), std::end(reversedWord));

	return word == reversedWord;
}

std::vector<IndexPair> GetPalindromicIndexPairs(const std::vector<std::string>& words) noexcept
{
	std::vector<IndexPair> palindromicIndexPairs;

	for (unsigned int i = 0; i < words.size(); ++i)
	{
		for (unsigned int j = 0; j < words.size(); ++j)
		{
			if (i != j && IsPalindrome(words[i] + words[j]))
			{
				palindromicIndexPairs.push_back({ i, j });
			}
		}
	}

	return palindromicIndexPairs;
}

inline std::ostream& operator <<(std::ostream& outputStream, const IndexPair& indexPair) noexcept
{
	outputStream << "(" << indexPair.first << ", " << indexPair.second << ")";

	return outputStream;
}

template <typename T>
std::ostream& operator <<(std::ostream& outputStream, const std::vector<T>& values) noexcept
{
	for (const auto& value : values)
	{
		outputStream << value << " ";
	}

	return outputStream;
}

int main(int argc, char* argv[])
{
	std::cout << GetPalindromicIndexPairs({ "code", "edoc", "da", "d" }) << "\n";

	std::cin.get();

	return 0;
}