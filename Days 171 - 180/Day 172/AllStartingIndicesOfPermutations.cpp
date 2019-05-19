#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

std::vector<std::vector<std::string>> GetPermutationsHelper(std::vector<std::string> strings, const unsigned int currentIndex, const unsigned int maxIndex) noexcept
{
	if (currentIndex == maxIndex - 1)
	{
		return { strings };
	}

	std::vector<std::vector<std::string>> permutations;

	for (unsigned int i = currentIndex; i < maxIndex; ++i)
	{
		std::swap(strings[currentIndex], strings[i]);

		const auto lesserPermutations = GetPermutationsHelper(strings, currentIndex + 1, maxIndex);
		permutations.insert(std::cend(permutations), std::cbegin(lesserPermutations), std::cend(lesserPermutations));

		std::swap(strings[i], strings[currentIndex]);
	}

	return permutations;
}

inline std::vector<std::vector<std::string>> GetPermutations(const std::vector<std::string>& strings) noexcept
{
	return GetPermutationsHelper(strings, 0, strings.size());
}

std::string JoinVectorOfStrings(const std::vector<std::string>& words) noexcept
{
	std::string joinedString;

	for (const auto& word : words)
	{
		joinedString += word;
	}

	return joinedString;
}

std::vector<unsigned int> GetStartingIndicesOfAllWordPermutations(const std::string& s, std::vector<std::string> words) noexcept
{
	std::vector<unsigned int> startingIndices;
	const auto permutations = GetPermutations(words);

	for (const auto& permuation : permutations)
	{
		const std::string joinedString = JoinVectorOfStrings(permuation);
		
		if (const std::size_t index = s.find(joinedString); index != std::string::npos)
		{
			startingIndices.push_back(index);
		}
	}

	return startingIndices;
}

template <typename T>
std::ostream& operator <<(std::ostream& outputStream, const std::vector<T>& values) noexcept
{
	outputStream << "( ";

	for (const auto& value : values)
	{
		outputStream << value << " ";
	}

	outputStream << ")";

	return outputStream;
}

int main(int argc, char* argv[])
{
	std::cout << GetStartingIndicesOfAllWordPermutations("dogcatcatcodecatdog", { "dog", "cat" }) << "\n";
	std::cout << GetStartingIndicesOfAllWordPermutations("barfoobazbitbyte", { "dog", "cat" }) << "\n";

	std::cin.get();

	return 0;
}