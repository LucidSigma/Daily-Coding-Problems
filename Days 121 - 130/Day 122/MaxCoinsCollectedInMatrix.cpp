#include <algorithm>
#include <array>
#include <iostream>
#include <type_traits>

template <unsigned int M, unsigned int N, typename = std::enable_if_t<(M > 0 && N > 0)>>
using Matrix = std::array<std::array<unsigned int, M>, N>;

template <unsigned int M, unsigned int N>
unsigned int GetMaxCoinsCollectedHelper(const Matrix<M, N>& matrix, const unsigned int currentRow, const unsigned int currentColumn) noexcept
{
	const unsigned int currentCoinValue = matrix[currentRow][currentColumn];

	if (currentRow == N - 1 && currentColumn == M - 1)
	{
		return currentCoinValue;
	}

	unsigned int downCoinValue = currentCoinValue;
	unsigned int rightCoinValue = currentCoinValue;

	if (currentRow < N - 1)
	{
		downCoinValue += GetMaxCoinsCollectedHelper(matrix, currentRow + 1, currentColumn);
	}

	if (currentColumn < M - 1)
	{
		rightCoinValue += GetMaxCoinsCollectedHelper(matrix, currentRow, currentColumn + 1);
	}

	return std::max(downCoinValue, rightCoinValue);
}

template <unsigned int M, unsigned int N>
inline unsigned int GetMaxCoinsCollected(const Matrix<M, N>& matrix) noexcept
{
	return GetMaxCoinsCollectedHelper(matrix, 0, 0);
}

int main(int argc, char* argv[])
{
	const Matrix<4, 3> coinMatrix
	{
		std::array<unsigned int, 4> { 0, 3, 1, 1 },
		std::array<unsigned int, 4> { 2, 0, 0, 4 },
		std::array<unsigned int, 4> { 1, 5, 3, 1 }
	};

	std::cout << GetMaxCoinsCollected(coinMatrix) << "\n";

	std::cin.get();

	return 0;
}