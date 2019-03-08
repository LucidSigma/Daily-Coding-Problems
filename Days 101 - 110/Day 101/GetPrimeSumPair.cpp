#include <iostream>
#include <iterator>
#include <stdexcept>
#include <unordered_set>
#include <utility>
#include <vector>

using UIntPair = std::pair<unsigned int, unsigned int>;

bool IsPrime(const unsigned int number, const std::unordered_set<unsigned int>& primeNumbers) noexcept
{
	for (const auto primeNumber : primeNumbers)
	{
		if (number == primeNumber)
		{
			return true;
		}

		if (number % primeNumber == 0)
		{
			return false;
		}
	}

	return true;
}

UIntPair GetPrimeNumberSumPair(const unsigned int number)
{
	if (number <= 2 || number % 2 != 0)
	{
		throw std::invalid_argument("Only even numbers more than two can be expressed as a sum of two primes.");
	}

	const unsigned int sumOperandLimit { number / 2 + 1 };

	std::vector<UIntPair> candidateNumbers;
	std::unordered_set<unsigned int> primeNumbers;

	for (unsigned int i = 2; i < sumOperandLimit; i++)
	{
		if (IsPrime(i, primeNumbers))
		{
			primeNumbers.insert(i);
			candidateNumbers.push_back({ i, number - i });
		}
	}

	std::vector<UIntPair> validCandidateNumbers;

	for (auto iterator = std::crbegin(candidateNumbers); iterator != std::crend(candidateNumbers); iterator++)
	{
		if (IsPrime(iterator->second, primeNumbers))
		{
			primeNumbers.insert(iterator->second);
			validCandidateNumbers.push_back(*iterator);
		}
	}

	return validCandidateNumbers.back();
}

inline void PrintPrimePair(const UIntPair& primePair) noexcept
{
	std::cout << primePair.first << " + " << primePair.second << " = " << (primePair.first + primePair.second) << "\n";
}

int main(int argc, char* argv[])
{
	PrintPrimePair(GetPrimeNumberSumPair(4));
	PrintPrimePair(GetPrimeNumberSumPair(28));
	PrintPrimePair(GetPrimeNumberSumPair(194));

	std::cin.get();

	return 0;
}