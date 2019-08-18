#include <cstdlib>
#include <iostream>
#include <iterator>
#include <locale>
#include <string>
#include <unordered_set>

bool IsSentenceValidHelper(const std::u32string& currentSentence, const char32_t currentCharacter, const std::u32string& remainingSentence)
{
	static const std::unordered_set<char32_t> separators{ U',', U';', U':' };
	static const std::unordered_set<char32_t> terminators{ U'.', U'?', U'!', U'\x203D' };

	bool isValid = true;

	if (currentSentence.empty() && !std::isupper(currentCharacter, std::locale("en_US.UTF-8")))
	{
		return false;
	}

	if (currentSentence.length() == 1 && !(currentCharacter == U' ' || !std::isupper(currentCharacter, std::locale("en_US.UTF-8"))))
	{
		return false;
	}

	if (terminators.find(currentCharacter) != std::cend(terminators))
	{
		return terminators.find(currentSentence.back()) == std::cend(terminators) && separators.find(currentSentence.back()) == std::cend(separators);
	}

	if (remainingSentence.empty())
	{
		return isValid && terminators.find(currentCharacter) != std::cend(terminators);
	}

	return isValid ? IsSentenceValidHelper(currentSentence + currentCharacter, remainingSentence.front(), remainingSentence.substr(1)) : false;
}

inline bool IsSentenceValid(const std::u32string& sentence)
{
	return IsSentenceValidHelper(U"", sentence.front(), sentence.substr(1));
}

int main(int argc, char* argv[])
{
	std::wcout << std::boolalpha;
	std::wcout << IsSentenceValid(U"This sentence is valid.") << "\n";
	std::wcout << IsSentenceValid(U"This sentence is Invalid") << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}