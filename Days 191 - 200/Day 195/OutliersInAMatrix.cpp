#include <array>
#include <cstddef>
#include <iostream>
#include <utility>

template <std::size_t M, std::size_t N>
using Matrix = std::array<std::array<int, N>, M>;

using Coordinate = std::pair<std::size_t, std::size_t>;

template <std::size_t M, std::size_t N>
unsigned int GetOutlierNumberCount(const Matrix<M, N>& matrix, const Coordinate& i, const Coordinate& j) noexcept
{
	const int iValue = matrix[i.first][i.second];
	const int jValue = matrix[j.first][j.second];

	unsigned int outlierCount = 0;

	for (std::size_t i = 0; i < M; ++i)
	{
		for (std::size_t j = 0; j < N; ++j)
		{
			if (matrix[i][j] < iValue || matrix[i][j] > jValue)
			{
				++outlierCount;
			}
		}
	}

	return outlierCount;
}

int main(int argc, char* argv[])
{
	const Matrix<5, 6> matrix
	{
		std::array<int, 6>{  1,  3,  7, 10, 15, 20 },
		std::array<int, 6>{  2,  6,  9, 14, 22, 25 },
		std::array<int, 6>{  3,  8, 10, 15, 25, 30 },
		std::array<int, 6>{ 10, 11, 12, 23, 30, 35 },
		std::array<int, 6>{ 20, 25, 30, 35, 40, 45 }
	};

	std::cout << GetOutlierNumberCount(matrix, { 1, 1 }, { 3, 3 }) << "\n";

	std::cin.get();

	return 0;
}