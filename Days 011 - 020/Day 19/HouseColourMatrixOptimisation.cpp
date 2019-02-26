#include <array>
#include <iostream>
#include <limits>
#include <type_traits>

template <unsigned int N, unsigned int K, typename = std::enable_if_t<(N > 0) && (K > 0)>>
int GetOptimisedCost(const std::array<std::array<int, K>, N>& costs) noexcept
{
	int previousMin = 0;
	int previousSecondMin = 0;
	int previousColour = -1;

	std::array<std::array<int, K>, N> totalCosts = costs;

	for (unsigned int i = 0; i < N; i++)
	{
		int currentMin = std::numeric_limits<int>::max();
		int currentSecondMin = std::numeric_limits<int>::max();
		int currentColour = -1;

		for (unsigned int j = 0; j < K; j++)
		{
			totalCosts[i][j] = totalCosts[i][j] + ((previousColour == j) ? previousSecondMin : previousMin);

			if (totalCosts[i][j] < currentMin)
			{
				currentSecondMin = currentMin;
				currentMin = totalCosts[i][j];
				currentColour = j;
			}
			else if (totalCosts[i][j] < currentSecondMin)
			{
				currentSecondMin = totalCosts[i][j];
			}
		}

		previousMin = currentMin;
		previousSecondMin = currentSecondMin;
		previousColour = currentColour;
	}

	return previousMin;
}

int main(int argc, char* argv[])
{
	const std::array<int, 3> row1 { 3, 5, 6 };
	const std::array<int, 3> row2 { 4, 7, 2 };
	const std::array<int, 3> row3 { 7, 1, 3 };
	const std::array<int, 3> row4 { 6, 2, 4 };
	const std::array<int, 3> row5 { 9, 8, 1 };

	const std::array<std::array<int, 3>, 5> matrix { row1, row2, row3, row4, row5 };

	std::cout << GetOptimisedCost(matrix) << "\n";

	std::cin.get();

	return 0;
}
