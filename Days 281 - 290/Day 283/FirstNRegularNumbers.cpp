#include <cstdlib>
#include <iostream>
#include <iterator>
#include <queue>
#include <set>
#include <unordered_map>
#include <utility>

using NumberCounter = std::unordered_map<unsigned int, unsigned int>;

template <>
struct std::less<std::pair<unsigned int, NumberCounter>>
{
	inline bool operator ()(const std::pair<unsigned int, NumberCounter>& lhs, const std::pair<unsigned int, NumberCounter>& rhs) noexcept
	{
		return lhs.first < rhs.first;
	}
};

unsigned int GetFactorCountProduct(const NumberCounter& factorCounts)
{
	unsigned int product = 1;

	for (const auto [factor, count] : factorCounts)
	{
		product *= factor * count;
	}

	return product;
}

void GetFirstNRegularNumbersHelper(const unsigned int n, std::priority_queue<std::pair<unsigned int, NumberCounter>>& numberOrder, std::set<unsigned int>& regularNumbers)
{
	if (regularNumbers.size() >= n)
	{
		return;
	}

	const auto [lowestValue, lowestFactorCounts] = numberOrder.top();
	numberOrder.pop();

	regularNumbers.insert(lowestValue);

	for (const auto [factor, _] : lowestFactorCounts)
	{
		auto currentFactorCount = lowestFactorCounts;
		++currentFactorCount[factor];

		numberOrder.emplace(lowestValue * factor, currentFactorCount);
	}

	GetFirstNRegularNumbersHelper(n, numberOrder, regularNumbers);
}

std::set<unsigned int> GetFirstNRegularNumbers(const unsigned int n)
{
	const NumberCounter factorCounts
	{	
		{ 2, 2 },
		{ 3, 1 },
		{ 5, 1 }
	};

	std::set<unsigned int> regularNumbers;

	std::priority_queue<std::pair<unsigned int, NumberCounter>> numberOrder;
	numberOrder.emplace(GetFactorCountProduct(factorCounts), factorCounts);
	GetFirstNRegularNumbersHelper(n, numberOrder, regularNumbers);

	return regularNumbers;
}

template <typename T>
std::ostream& operator <<(std::ostream& outputStream, const std::set<T>& values)
{
	for (const auto& value : values)
	{
		outputStream << value << " ";
	}

	return outputStream;
}

int main(int argc, char* argv[])
{
	std::cout << GetFirstNRegularNumbers(10) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}