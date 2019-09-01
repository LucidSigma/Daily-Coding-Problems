#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <vector>

bool IsValidUTF8Encoding(const std::vector<unsigned char>& bytes)
{
	static_assert(sizeof(unsigned char) == 1);

	if (bytes.empty() || bytes.size() > 4)
	{
		throw std::invalid_argument("Invalid number of bytes to validate.");
	}

	if (bytes.size() == 1)
	{
		return (bytes.front() & 0b10000000) == 0b00000000;
	}
	else
	{
		unsigned char oneMask = 0b00000000;
		unsigned char zeroMask = 0b10000000;
		
		for (size_t i = 0; i < bytes.size(); ++i)
		{
			oneMask >>= 1;
			oneMask |= 0b10000000;
		
			zeroMask >>= 1;
		}
		
		if ((bytes.front() & oneMask) != oneMask && (bytes.front() & zeroMask) == 0b00000000)
		{
			return false;
		}

		for (size_t i = 1; i < bytes.size(); ++i)
		{
			if ((bytes[i] & 0b11000000) != 0b10000000)
			{
				return false;
			}
		}

		return true;
	}
}

int main(int argc, char* argv[])
{
	std::cout << std::boolalpha;

	std::cout << IsValidUTF8Encoding({ 0b00101010 }) << "\n";
	std::cout << IsValidUTF8Encoding({ 0b10101010 }) << "\n";

	std::cout << IsValidUTF8Encoding({ 0b11001100, 0b10010101 }) << "\n";
	std::cout << IsValidUTF8Encoding({ 0b01001100, 0b10010101 }) << "\n";
	
	std::cout << IsValidUTF8Encoding({ 0b11100101, 0b10001100, 0b10010101 }) << "\n";
	std::cout << IsValidUTF8Encoding({ 0b10100101, 0b10001100, 0b10010101 }) << "\n";

	std::cout << IsValidUTF8Encoding({ 0b11110010, 0b10100101, 0b10001100, 0b10010101 }) << "\n";
	std::cout << IsValidUTF8Encoding({ 0b11110010, 0b11100101, 0b10001100, 0b10010101 }) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}