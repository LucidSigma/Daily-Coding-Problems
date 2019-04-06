#include <algorithm>
#include <iostream>
#include <vector>

int GetMaxProfitFromStockHelper(const std::vector<unsigned int>& stockPrices, const unsigned int currentIndex, const int currentProfit, const unsigned int remainingBuys, const unsigned int remainingSells) noexcept
{
	if (currentIndex == stockPrices.size() || remainingSells == 0)
	{
		return currentProfit;
	}

	return remainingBuys == remainingSells 
		? std::max(GetMaxProfitFromStockHelper(stockPrices, currentIndex + 1, currentProfit - stockPrices[currentIndex], remainingBuys - 1, remainingSells), 
				   GetMaxProfitFromStockHelper(stockPrices, currentIndex + 1, currentProfit, remainingBuys, remainingSells)) 
		: std::max(GetMaxProfitFromStockHelper(stockPrices, currentIndex + 1, currentProfit + stockPrices[currentIndex], remainingBuys, remainingSells - 1), 
				   GetMaxProfitFromStockHelper(stockPrices, currentIndex + 1, currentProfit, remainingBuys, remainingSells));
}

inline int GetMaxProfitFromStock(const std::vector<unsigned int>& stockPrices, const unsigned int k) noexcept
{
	return GetMaxProfitFromStockHelper(stockPrices, 0, 0, k, k);
}

int main(int argc, char* argv[])
{
	std::cout << GetMaxProfitFromStock({ 5, 2, 4, 0, 1 }, 3) << "\n";

	std::cin.get();

	return 0;
}