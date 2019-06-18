#include <cmath>
#include <iostream>

bool IsNumberPalindrome(const int number) noexcept
{
	const unsigned int magnitude = static_cast<unsigned int>(std::log10(number));
	unsigned int powerOfTen = static_cast<unsigned int>(std::pow(10, magnitude));

	for (unsigned int i = 0; i < magnitude / 2; ++i)
	{
		const int leftDigit = number / powerOfTen;
		const int rightDigit = number % static_cast<unsigned int>(std::pow(10, i + 1));

		if (leftDigit != rightDigit)
		{
			return false;
		}

		powerOfTen /= 10;
	}

	return true;
}

int main(int argc, char* argv[])
{
	std::cout << std::boolalpha;
	std::cout << IsNumberPalindrome(121) << "\n";
	std::cout << IsNumberPalindrome(888) << "\n";
	std::cout << IsNumberPalindrome(678) << "\n";

	std::cin.get();

	return 0;
}