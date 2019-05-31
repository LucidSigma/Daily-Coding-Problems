#include <algorithm>
#include <cmath>
#include <iostream>
#include <iterator>
#include <unordered_map>
#include <vector>

std::vector<unsigned int> GetPrimeNumbers(const unsigned int max) noexcept
{
	static constexpr unsigned int SmallestPrime = 2u;
	std::vector<unsigned int> primeNumbers{ SmallestPrime };

	for (unsigned int i = SmallestPrime + 1; i < max / 2 + 1; ++i)
	{
		bool isPrime = true;

		for (const auto primeNumber : primeNumbers)
		{
			if (i % primeNumber == 0)
			{
				isPrime = false;

				break;
			}
		}

		if (isPrime)
		{
			primeNumbers.push_back(i);
		}
	}

	return primeNumbers;
}

std::unordered_map<unsigned int, unsigned int> GetFactors(unsigned int number, const std::vector<unsigned int>& primeNumbers) noexcept
{
	std::unordered_map<unsigned int, unsigned int> factors;
	unsigned int primeNumberIndex = 0;

	while (number > 1)
	{
		if (primeNumberIndex >= primeNumbers.size())
		{
			break;
		}

		if (number % primeNumbers[primeNumberIndex] == 0)
		{
			if (factors.find(primeNumbers[primeNumberIndex]) == std::cend(factors))
			{
				factors[primeNumbers[primeNumberIndex]] = 0;
			}

			++factors[primeNumbers[primeNumberIndex]];
			number /= primeNumbers[primeNumberIndex];
		}
		else
		{
			++primeNumberIndex;
		}
	}

	return factors;
}

unsigned int GetGCD(const std::vector<unsigned int>& numbers) noexcept
{
	const unsigned int minNumber = *std::min_element(std::cbegin(numbers), std::cend(numbers));
	const auto primeNumbers = GetPrimeNumbers(minNumber);
	const auto minFactors = GetFactors(minNumber, primeNumbers);

	const auto allNumberFactors = [&numbers, &primeNumbers]()
	{
		std::unordered_map<unsigned int, std::unordered_map<unsigned int, unsigned int>> allFactors;

		for (const auto number : numbers)
		{
			allFactors[number] = GetFactors(number, primeNumbers);
		}

		return allFactors;
	}();

	std::unordered_map<unsigned int, unsigned int> commonFactors;

	for (const auto [minFactor, _] : minFactors)
	{
		commonFactors[minFactor] = 0;
		std::vector<unsigned int> numberFactors;

		for (const auto number : numbers)
		{
			const auto currentFactors = allNumberFactors.at(number);
			numberFactors.push_back(currentFactors.at(minFactor));
		}

		commonFactors[minFactor] = *std::min_element(std::cbegin(numberFactors), std::cend(numberFactors));
	}

	unsigned int gcd = 1;

	for (const auto [factor, commonFactor] : commonFactors)
	{
		gcd *= static_cast<unsigned int>(std::pow(factor, commonFactor));
	}

	return gcd;
}

int main(int argc, char* argv[])
{
	std::cout << GetGCD({ 42, 56, 14 }) << "\n";

	std::cin.get();

	return 0;
}