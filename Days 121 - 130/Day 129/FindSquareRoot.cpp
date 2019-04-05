#include <cmath>
#include <iostream>
#include <stdexcept>

inline bool WithinEpsilon(const float a, const float b, const float epsilon) noexcept
{
	return std::abs(a - b) < epsilon;
}

float Sqrt(const float number) noexcept
{
	if (number < 0.0f)
	{
		throw std::invalid_argument("Square root of negative number is non-real.");
	}

	static constexpr float Epsilon = 0.000001f;

	float squareRoot = number;
	float lowerBound = 0.0f;
	float upperBound = number;

	while (!WithinEpsilon(squareRoot * squareRoot, number, Epsilon))
	{
		(squareRoot * squareRoot > number ? upperBound : lowerBound) = squareRoot;
		squareRoot = (upperBound + lowerBound) / 2.0f;
	}

	return squareRoot;
}

int main(int argc, char* argv[])
{
	std::cout << Sqrt(2) << "\n";
	std::cout << Sqrt(9) << "\n";
	std::cout << Sqrt(289) << "\n";

	std::cin.get();

	return 0;
}