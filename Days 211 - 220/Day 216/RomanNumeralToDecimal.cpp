#include <cstddef>
#include <iostream>
#include <iterator>
#include <string>
#include <unordered_map>

const std::unordered_map<char, unsigned int> valueMappings
{
	{ 'M', 1000 },
	{ 'D', 500 },
	{ 'C', 100 },
	{ 'L', 50 },
	{ 'X', 10 },
	{ 'V', 5 },
	{ 'I', 1 }
};

unsigned int RomanNumeralToDecimal(const std::string& romanNumeral) noexcept
{
	char previousNumeral = romanNumeral.back();
	unsigned int decimalValue = valueMappings.at(previousNumeral);

	for (auto it = std::crbegin(romanNumeral) + 1; it != std::crend(romanNumeral); ++it)
	{
		const char numeral = *it;

		const short sign = valueMappings.at(numeral) > valueMappings.at(previousNumeral) ? 1 : -1;
		decimalValue += valueMappings.at(numeral) * sign;

		previousNumeral = numeral;
	}

	return decimalValue;
}

inline unsigned int operator "" _roman(const char* romanNumeral, const std::size_t) noexcept
{
	return RomanNumeralToDecimal(romanNumeral);
}

int main(int argc, char* argv[])
{
	std::cout << "XIV"_roman << "\n";

	std::cin.get();

	return 0;
}