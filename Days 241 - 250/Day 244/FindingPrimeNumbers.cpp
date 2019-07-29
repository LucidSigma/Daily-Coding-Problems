#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <limits>
#include <numeric>
#include <vector>

static constexpr unsigned int FirstPrimeNumber = 2u;

[[nodiscard]] std::vector<unsigned int> SieveOfEratosthenes(const unsigned int n)
{
	std::vector<unsigned int> candidateNumbers(n - 1);
	std::iota(std::begin(candidateNumbers), std::end(candidateNumbers), FirstPrimeNumber);

	static constexpr unsigned int CompositeNumber = 0u;

	for (unsigned int i = FirstPrimeNumber; i < candidateNumbers.size(); ++i)
	{
		for (size_t j = i; j < candidateNumbers.size(); ++j)
		{
			if (candidateNumbers[j] == CompositeNumber)
			{
				continue;
			}

			if (candidateNumbers[j] % i == 0 && candidateNumbers[j] != i)
			{
				candidateNumbers[j] = CompositeNumber;
			}
		}
	}

	std::vector<unsigned int> primeNumbers;

	for (const auto number : candidateNumbers)
	{
		if (number != CompositeNumber)
		{
			primeNumbers.push_back(number);
		}
	}

	return primeNumbers;
}

[[nodiscard]] std::vector<unsigned int> GetAllPrimes(const unsigned int limit = std::numeric_limits<unsigned int>::max())
{
	std::vector<unsigned int> primeNumbers{ FirstPrimeNumber };

	for (unsigned int i = FirstPrimeNumber + 1; i < limit; ++i)
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

template <typename T>
std::ostream& operator <<(std::ostream& outputStream, const std::vector<T>& values)
{
	for (const auto& value : values)
	{
		outputStream << value << " ";
	}

	return outputStream;
}

int main(int argc, char* argv[])
{
	std::cout << SieveOfEratosthenes(100) << "\n";
	std::cout << GetAllPrimes(100) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}