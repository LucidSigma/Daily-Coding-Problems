#include <array>
#include <cstddef>
#include <cstdlib>
#include <iostream>

template <size_t M, size_t N>
using Matrix = std::array<std::array<int, N>, M>;

template <size_t M, size_t N>
bool IsMatrixToeplitzHelper(const size_t rowIndex, const size_t columnIndex, const Matrix<M, N> matrix, const int currentElement)
{
	if (rowIndex == M || columnIndex == N)
	{
		return true;
	}

	if (matrix[rowIndex][columnIndex] == currentElement)
	{
		return IsMatrixToeplitzHelper(rowIndex + 1, columnIndex + 1, matrix, currentElement);
	}

	return false;
}

template <size_t M, size_t N>
bool IsMatrixToeplitz(const Matrix<M, N>& matrix)
{
	for (size_t i = 0; i < M; ++i)
	{
		if (!IsMatrixToeplitzHelper(i + 1, 1, matrix, matrix[i][0]))
		{
			return false;
		}
	}

	for (size_t i = 1; i < N; ++i)
	{
		if (!IsMatrixToeplitzHelper(1, i + 1, matrix, matrix[0][i]))
		{
			return false;
		}
	}

	return true;
}

int main(const int argc, const char* const argv[])
{
	const Matrix<4, 5>& matrix
	{
		std::array<int, 5>{ 1, 2, 3, 4, 8 },
		std::array<int, 5>{ 5, 1, 2, 3, 4 },
		std::array<int, 5>{ 4, 5, 1, 2, 3 },
		std::array<int, 5>{ 7, 4, 5, 1, 2 }
	};

	std::cout << std::boolalpha;
	std::cout << IsMatrixToeplitz(matrix) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}