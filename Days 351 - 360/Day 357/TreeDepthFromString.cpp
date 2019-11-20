#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <string>

unsigned int GetSuccessiveBracketCount(const std::string& treeString, const char bracket)
{
	unsigned int currentCount = 1;
	unsigned int maxCount = 1;

	for (size_t i = 1; i < treeString.length(); ++i)
	{
		if (treeString[i] == treeString[i - 1])
		{
			++currentCount;
		}
		else
		{
			currentCount = 0;
		}

		maxCount = std::max(maxCount, currentCount);
	}

	return maxCount - 1;
}

unsigned int GetTreeDepth(const std::string& treeString)
{
	const unsigned int openCount = GetSuccessiveBracketCount(treeString, '(');
	const unsigned int closeCount = GetSuccessiveBracketCount(treeString, ')');

	return std::max(openCount, closeCount);
}

int main(const int argc, const char* const argv[])
{
	std::cout << GetTreeDepth("(00)") << "\n";
	std::cout << GetTreeDepth("((00)(00))") << "\n";
	std::cout << GetTreeDepth("((((00)0)0)0)") << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}