#include <algorithm>
#include <array>
#include <iostream>
#include <limits>

template <unsigned int Size>
int GetMaxProfitFromStock(const std::array<int, Size>& stocks) noexcept
{
	int minStock = stocks[0];
	int maxProfit = std::numeric_limits<int>::min();

	for (unsigned int i = 1; i < Size; i++)
	{
		maxProfit = std::max(stocks[i] - minStock, maxProfit);
		minStock = std::min(stocks[i], minStock);
	}

	return maxProfit;
}

int main(int argc, const char* argv[])
{
	std::cout << GetMaxProfitFromStock<6>({ 9, 11, 8, 5, 7, 10 }) << "\n";

	std::cin.get();

	return 0;
}