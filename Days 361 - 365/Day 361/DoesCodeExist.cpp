#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <string>
#include <unordered_map>

bool DoesCodeMatch(const std::string& code, const std::string& guess, const unsigned int correctDigitCount)
{
	unsigned int count = 0;

	for (size_t i = 0; i < 6; ++i)
	{
		if (code[i] == guess[i])
		{
			++count;
		}
	}

	return count == correctDigitCount;
}

bool DoesCodeExist(const std::unordered_map<unsigned int, unsigned int>& guesses)
{
	for (unsigned int i = 0; i < 1'000'000; ++i)
	{
		const std::string currentCodeString = std::to_string(i);
		const std::string currentFullCodeString = std::string(6 - currentCodeString.length(), '0') + currentCodeString;

		bool codeExists = true;

		for (const auto [codeGuess, correctDigitCount] : guesses)
		{
			codeExists = codeExists && DoesCodeMatch(currentFullCodeString, std::to_string(codeGuess), correctDigitCount);
		}

		if (codeExists)
		{
			return true;
		}
	}

	return false;
}

int main(const int argc, const char* const argv[])
{
	std::cout << std::boolalpha;
	std::cout << DoesCodeExist({ { 175286, 2 }, { 293416, 3 }, { 654321, 0 } }) << "\n";
	std::cout << DoesCodeExist({ { 123456, 4 }, { 345678, 4 }, { 567890, 4 } }) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}