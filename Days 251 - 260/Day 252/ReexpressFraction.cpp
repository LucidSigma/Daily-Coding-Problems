#include <cstdlib>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <utility>
#include <vector>

using Fraction = std::pair<unsigned int, unsigned int>;

std::vector<Fraction> ReexpressFraction(const Fraction& fraction)
{
	const auto [a, b] = fraction;

	if (a >= b)
	{
		throw std::invalid_argument("Fraction is improper or whole.");
	}

	std::vector<Fraction> subfractions;
	unsigned int currentDenominator = 2;
	long double currentValue = static_cast<long double>(a) / static_cast<long double>(b);

	while (currentValue > std::numeric_limits<long double>::epsilon())
	{
		const long double currentFraction = 1.0l / static_cast<long double>(currentDenominator);

		if (currentFraction <= currentValue)
		{
			subfractions.emplace_back(1, currentDenominator);
			currentValue -= currentFraction;
		}

		++currentDenominator;
	}

	return subfractions;
}

inline std::ostream& operator <<(std::ostream& outputStream, const Fraction& fraction)
{
	outputStream << fraction.first << " / " << fraction.second;

	return outputStream;
}

template <typename T>
std::ostream& operator <<(std::ostream& outputStream, const std::vector<T>& values)
{
	for (const auto& value : values)
	{
		outputStream << value << "\n";
	}

	return outputStream;
}

int main(int argc, char* argv[])
{
	std::cout << ReexpressFraction({ 4, 13 }) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}