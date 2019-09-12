#include <algorithm>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <string>
#include <unordered_set>

inline bool IsValidKaprekarNumber(const std::string& number)
{
	std::unordered_set<char> numberSet(std::cbegin(number), std::cend(number));

	return numberSet.size() >= 2 && numberSet.size() <= 4;
}

unsigned int GetKaprekarStepCount(unsigned int number)
{
	static constexpr unsigned int KaprekarConstant = 6174u;
	unsigned int stepCount = 0;

	while (number != KaprekarConstant)
	{
		const std::string numberString = std::to_string(number);

		if (!IsValidKaprekarNumber(numberString))
		{
			throw std::invalid_argument("Invalid number to get Kaprekar step count.");
		}

		std::string ascendingNumber = numberString;
		std::sort(std::begin(ascendingNumber), std::end(ascendingNumber));

		std::string descendingNumber = numberString;
		std::sort(std::begin(descendingNumber), std::end(descendingNumber), std::greater<char>());

		number = std::stoi(descendingNumber) - std::stoi(ascendingNumber);
		++stepCount;
	}

	return stepCount;
}

int main(int argc, char* argv[])
{
	std::cout << GetKaprekarStepCount(1234) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}