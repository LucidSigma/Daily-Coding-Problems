#include <iostream>
#include <sstream>
#include <string>

std::string RunLengthEncode(const std::string& string) noexcept
{
	unsigned int counter = 1;
	char previousCharacter = string[0];

	std::string encodedString;

	for (unsigned int i = 1; i < string.length(); i++)
	{
		if (string[i] == previousCharacter)
		{
			counter++;
		}
		else
		{
			encodedString += std::to_string(counter) + previousCharacter;

			counter = 1;
			previousCharacter = string[i];
		}

		if ((i == string.length() - 1))
		{
			encodedString += std::to_string(counter) + previousCharacter;
		}
	}

	return encodedString;
}

std::string RunLengthDecode(const std::string& string)
{
	std::istringstream stringReader(string);
	std::string decodedString;

	unsigned int currentCount;
	char currentLetter;
	
	while (stringReader >> currentCount >> currentLetter)
	{
		decodedString += std::string(currentCount, currentLetter);
	}

	return decodedString;
}

int main(int argc, const char* argv[])
{
	std::cout << RunLengthEncode("AAAABBBCCDAA") << "\n";
	std::cout << RunLengthDecode("4A3B2C1D2A") << "\n";
	
	std::cin.get();

	return 0;
}