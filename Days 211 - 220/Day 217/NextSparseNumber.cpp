#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <string>

std::string DecimalToBinary(unsigned int number) noexcept
{
	std::string binaryNumber;

	while (number > 0)
	{
		binaryNumber += std::to_string(number % 2);
		number /= 2;
	}

	std::reverse(std::begin(binaryNumber), std::end(binaryNumber));

	return binaryNumber;
}

unsigned int BinaryToDecimal(const std::string& binary) noexcept
{
	unsigned int decimalNumber = 0;

	for (int i = binary.length() - 1; i >= 0; --i)
	{
		const unsigned int digit = binary[i] - '0';
		const unsigned int magnitude = binary.length() - 1 - i;

		decimalNumber += digit * (1 << magnitude);
	}

	return decimalNumber;
}

unsigned int GetNextSparseNumber(const unsigned int n) noexcept
{
	const std::string binary = DecimalToBinary(n);
	std::string nextSparseBinary;

	char previousDigit = '0';
	bool isNotSparse = false;

	for (std::size_t i = 0; i < binary.length(); ++i)
	{
		if (binary[i] == '1' && previousDigit == '1')
		{
			isNotSparse = true;
		}

		if (isNotSparse)
		{
			nextSparseBinary += std::string(binary.length() - i, '0');

			break;
		}
		else
		{
			nextSparseBinary += binary[i];
		}

		previousDigit = binary[i];
	}

	if (isNotSparse)
	{
		if (nextSparseBinary[0] == '1')
		{
			using namespace std::literals::string_literals;

			nextSparseBinary = "10"s + nextSparseBinary.substr(1);
		}
		else
		{
			nextSparseBinary = '1' + nextSparseBinary;
		}
	}

	return BinaryToDecimal(nextSparseBinary);
}

int main(int argc, char* argv[])
{
	std::cout << GetNextSparseNumber(21) << "\n";
	std::cout << GetNextSparseNumber(22) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}