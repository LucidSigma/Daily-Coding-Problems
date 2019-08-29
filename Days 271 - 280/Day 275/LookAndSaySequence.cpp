#include <cstdlib>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

std::string CreateLookAndSaySequenceHelper(const unsigned int n, const std::string& currentTerm)
{
	if (n == 1)
	{
		return currentTerm;
	}

	std::vector<std::pair<unsigned int, char>> numberCounts{ { 0, currentTerm.front() } };

	for (const char digit : currentTerm)
	{
		const auto [previousCount, previousDigit] = numberCounts.back();
		numberCounts.pop_back();

		if (digit == previousDigit)
		{
			numberCounts.emplace_back(previousCount + 1, digit);
		}
		else
		{
			numberCounts.emplace_back(previousCount, previousDigit);
			numberCounts.emplace_back(1, digit);
		}
	}

	std::string lookAndSaySequence;

	for (const auto [count, digit] : numberCounts)
	{
		lookAndSaySequence += std::to_string(count) + digit;
	}

	return CreateLookAndSaySequenceHelper(n - 1, lookAndSaySequence);
}

inline std::string CreateLookAndSaySequence(const unsigned int n)
{
	return CreateLookAndSaySequenceHelper(n, "1");
}

int main(int argc, char* argv[])
{
	std::cout << CreateLookAndSaySequence(5) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}