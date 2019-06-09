#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

int GetMaxProfitFromStockHelper(const std::vector<int>& stockPrices, const int fee, const int previousProfit, const bool canBuy) noexcept
{
	if (stockPrices.empty())
	{
		return previousProfit;
	}

	int currentPrice = canBuy ? -stockPrices.front() - fee : stockPrices.front();

	return std::max(
		GetMaxProfitFromStockHelper(std::vector<int>(std::cbegin(stockPrices) + 1, std::cend(stockPrices)), fee, previousProfit, canBuy),
		GetMaxProfitFromStockHelper(std::vector<int>(std::cbegin(stockPrices) + 1, std::cend(stockPrices)), fee, previousProfit + currentPrice, !canBuy)
	);
}

inline int GetMaxProfitFromStock(const std::vector<int>& stockPrices, const int fee) noexcept
{
	return GetMaxProfitFromStockHelper(stockPrices, fee, 0, true);
}

int main(int argc, char* argv[])
{
	std::cout << GetMaxProfitFromStock({ 1, 3, 2, 8, 4, 10 }, 2) << "\n";

	std::cin.get();

	return 0;
}