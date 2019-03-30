#include <iostream>
#include <locale>
#include <string>

bool IsNumberString(const std::string& numberString) noexcept
{
	enum NonNumericSymbols
		: char
	{
		PositiveSign = '+',
		NegativeSign = '-',
		ScientificExponent = 'e',
		ScientificExponentCapital = 'E',
		DecimalPoint = '.',
		HexadecimalIndicator = 'x',
		BinaryIndicator = 'b',
		DigitSeparator = '\'',
		CSharpDigitSeparator = '_'
	};

	bool hasDigit = false;

	for (unsigned int i = 0; i < numberString.length(); i++)
	{
		if (unsigned int endIndex = numberString.length() - 1;
			!std::isdigit(numberString[i], std::locale("")))
		{
			switch (numberString[i])
			{
			case NonNumericSymbols::PositiveSign:
			case NonNumericSymbols::NegativeSign:
				if (i != 0)
				{
					if (numberString[i - 1] == NonNumericSymbols::PositiveSign || numberString[i - 1] == NonNumericSymbols::NegativeSign ||
						numberString[i - 1] == NonNumericSymbols::BinaryIndicator || numberString[i - 1] == NonNumericSymbols::HexadecimalIndicator ||
						numberString[i - 1] == NonNumericSymbols::DigitSeparator || numberString[i - 1] == NonNumericSymbols::CSharpDigitSeparator ||
						numberString[i - 1] == NonNumericSymbols::DecimalPoint)
					{
						return false;
					}
				}

				if (!(i == 0 || 
					(numberString[i - 1] == NonNumericSymbols::ScientificExponent || numberString[i - 1] == NonNumericSymbols::ScientificExponentCapital) 
					 && i != endIndex))
				{
					return false;
				}

				break;

			case NonNumericSymbols::ScientificExponent:
			case NonNumericSymbols::ScientificExponentCapital:
				if(i != 0)
				{
					if (numberString[i - 1] == NonNumericSymbols::ScientificExponent || numberString[i - 1] == NonNumericSymbols::ScientificExponentCapital || 
						numberString[i - 1] == NonNumericSymbols::PositiveSign || numberString[i - 1] == NonNumericSymbols::NegativeSign ||
						numberString[i - 1] == NonNumericSymbols::DigitSeparator || numberString[i - 1] == NonNumericSymbols::CSharpDigitSeparator ||
						numberString[i - 1] == NonNumericSymbols::DecimalPoint)
					{
						return false;
					}
				}

				if (i == 0 || i == endIndex)
				{
					return false;
				}

				[[fallthrough]];

			case NonNumericSymbols::DecimalPoint:
				if (i != 0)
				{
					if (numberString[i - 1] == NonNumericSymbols::ScientificExponent || numberString[i - 1] == NonNumericSymbols::ScientificExponentCapital ||
						numberString[i - 1] == NonNumericSymbols::BinaryIndicator || numberString[i - 1] == NonNumericSymbols::HexadecimalIndicator ||
						numberString[i - 1] == NonNumericSymbols::DigitSeparator || numberString[i - 1] == NonNumericSymbols::CSharpDigitSeparator ||
						numberString[i - 1] == NonNumericSymbols::DecimalPoint)
					{
						return false;
					}
				}

				break;

			case NonNumericSymbols::HexadecimalIndicator:
			case NonNumericSymbols::BinaryIndicator:
				if (!(i == 1 && numberString[0] == '0'))
				{
					return false;
				}

				hasDigit = false;

				break;

			case NonNumericSymbols::DigitSeparator:
			case NonNumericSymbols::CSharpDigitSeparator:
				if (i != 0)
				{
					if (numberString[i - 1] == NonNumericSymbols::ScientificExponent || numberString[i - 1] == NonNumericSymbols::ScientificExponentCapital ||
						numberString[i - 1] == NonNumericSymbols::PositiveSign || numberString[i - 1] == NonNumericSymbols::NegativeSign ||
						numberString[i - 1] == NonNumericSymbols::BinaryIndicator || numberString[i - 1] == NonNumericSymbols::HexadecimalIndicator ||
						numberString[i - 1] == NonNumericSymbols::DigitSeparator || numberString[i - 1] == NonNumericSymbols::CSharpDigitSeparator ||
						numberString[i - 1] == NonNumericSymbols::DecimalPoint)
					{
						return false;
					}
				}

				if (i == 0 || i == endIndex)
				{
					return false;
				}

				break;

			default:
				return false;
			}
		}
		else
		{
			hasDigit = true;
		}
	}

	return hasDigit;
}

int main(int argc, char* argv[])
{
	std::cout << std::boolalpha;

	std::cout << IsNumberString("10") << "\n";
	std::cout << IsNumberString("-10") << "\n";
	std::cout << IsNumberString("+10") << "\n";
	std::cout << IsNumberString("10.1") << "\n";
	std::cout << IsNumberString("-10.1") << "\n";
	std::cout << IsNumberString("1e5") << "\n";
	std::cout << IsNumberString("1e-5") << "\n";

	std::cout << IsNumberString("") << "\n";
	std::cout << IsNumberString("a") << "\n";
	std::cout << IsNumberString("x 1") << "\n";
	std::cout << IsNumberString("a -2") << "\n";
	std::cout << IsNumberString("-") << "\n";
	std::cout << IsNumberString("1e-") << "\n";
	std::cout << IsNumberString("2e") << "\n";

	std::cin.get();

	return 0;
}