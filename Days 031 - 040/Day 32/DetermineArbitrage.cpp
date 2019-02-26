#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <limits>

template <unsigned int Currencies>
bool HasArbitrage(const std::array<std::array<double, Currencies>, Currencies>& exchanges)
{
	auto transformedExchanges = exchanges;

	for (auto& row : transformedExchanges)
	{
		std::transform(row.begin(), row.end(), row.begin(),
			[](double exchange) -> double
			{
				return -std::log(exchange);
			}
		);
	}

	std::array<double, Currencies> minDistance;
	minDistance.fill(std::numeric_limits<double>::max());
	minDistance[0] = 0.0;

	for (unsigned int i = 0; i < Currencies - 1; i++)
	{
		for (unsigned int j = 0; j < Currencies; j++)
		{
			for (unsigned int k = 0; k < Currencies; k++)
			{
				if (minDistance[k] > (minDistance[j] + transformedExchanges[j][k]))
				{
					minDistance[k] = minDistance[j] + transformedExchanges[j][k];
				}
			}
		}
	}

	for (unsigned int i = 0; i < Currencies; i++)
	{
		for (unsigned int j = 0; j < Currencies; j++)
		{
			if (minDistance[j] > (minDistance[i] + transformedExchanges[i][j]))
			{
				return true;
			}
		}
	}

	return false;
}

int main(int argc, const char* argv[])
{
	// Currencies: AUD, USD, GBP, EUR, CAD
	constexpr unsigned int CURRENCY_COUNT = 5;

	const std::array<std::array<double, CURRENCY_COUNT>, CURRENCY_COUNT> EXCHANGE_RATES
	{
		std::array<double, CURRENCY_COUNT> { 1.00, 0.70, 0.55, 0.62, 0.96 },
		std::array<double, CURRENCY_COUNT> { 1.42, 1.00, 0.79, 0.87, 1.36 },
		std::array<double, CURRENCY_COUNT> { 1.80, 1.27, 1.00, 1.11, 1.73 },
		std::array<double, CURRENCY_COUNT> { 1.62, 1.14, 0.90, 1.00, 1.56 },
		std::array<double, CURRENCY_COUNT> { 1.04, 0.73, 0.58, 0.64, 1.00 }
	};

	std::cout << std::boolalpha;
	std::cout << HasArbitrage(EXCHANGE_RATES) << "\n";

	std::cin.get();

	return 0;
}