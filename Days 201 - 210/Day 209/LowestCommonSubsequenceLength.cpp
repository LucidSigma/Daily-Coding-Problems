#include <algorithm>
#include <array>
#include <cstddef>
#include <iostream>
#include <vector>

static constexpr std::size_t StringCount = 3;

std::size_t GetLowestCommonSubsequenceLengthHelper(const std::array<std::string, StringCount>& strings, const std::string& currentString, const std::vector<std::size_t>& indices) noexcept
{
	std::size_t currentLength = currentString.size();

	for (char c = 'a'; c <= 'z'; ++c)
	{
		std::vector<std::size_t> newIndices;

		for (std::size_t i = 0; i < strings.size(); ++i)
		{
			const std::size_t index = strings[i].find(c, indices[i] + 1);

			if (index == std::string::npos)
			{
				break;
			}

			newIndices.push_back(index);
		}

		if (newIndices.size() == strings.size())
		{
			const std::size_t subsequentLength = GetLowestCommonSubsequenceLengthHelper(strings, currentString + c, newIndices);
			currentLength = std::max(currentLength, subsequentLength);
		}
	}

	return currentLength;
}

inline std::size_t GetLowestCommonSubsequenceLength(const std::array<std::string, StringCount>& strings) noexcept
{
	return GetLowestCommonSubsequenceLengthHelper(strings, "", std::vector<std::size_t>(strings.size(), std::string::npos));
}

int main(int argc, char* argv[])
{
	std::cout << GetLowestCommonSubsequenceLength({ "epidermiologist", "refrigeration", "supercalifragilisticexpialodocious" }) << "\n";

	std::cin.get();

	return 0;
}