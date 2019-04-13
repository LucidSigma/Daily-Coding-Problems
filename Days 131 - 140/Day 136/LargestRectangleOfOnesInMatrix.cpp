#include <algorithm>
#include <array>
#include <iostream>

template <unsigned int M, unsigned int N>
using Matrix = std::array<std::array<unsigned int, N>, M>;

template <unsigned int M, unsigned int N>
bool IsExtendableRow(const Matrix<M, N>& matrix, unsigned int currentRow, unsigned int startColumn, unsigned int currentColumn) noexcept
{
	for (unsigned int i = startColumn; i < currentColumn; i++)
	{
		if (matrix[currentRow][i] == 0)
		{
			return false;
		}
	}

	return true;
}

template <unsigned int M, unsigned int N>
bool IsExtendableColumn(const Matrix<M, N>& matrix, unsigned int currentColumn, unsigned int startRow, unsigned int currentRow) noexcept
{
	for (unsigned int i = startRow; i < currentRow; i++)
	{
		if (matrix[i][currentColumn] == 0)
		{
			return false;
		}
	}

	return true;
}

template <unsigned int M, unsigned int N>
unsigned int GetLargestOneRectangleAreaHelper(const Matrix<M, N>& matrix, unsigned int startRow, unsigned int currentRow, unsigned int startColumn, unsigned int currentColumn) noexcept
{
	unsigned int currentArea = (currentRow - startRow) * (currentColumn - startColumn);

	unsigned int extendedRowArea = currentRow < M && IsExtendableRow(matrix, currentRow, startColumn, currentColumn)
								   ? GetLargestOneRectangleAreaHelper(matrix, startRow, currentRow + 1, startColumn, currentColumn)
								   : 0;

	unsigned int extendedColumnArea = currentColumn < N && IsExtendableColumn(matrix, currentColumn, startRow, currentRow)
							    	  ? GetLargestOneRectangleAreaHelper(matrix, startRow, currentRow, startColumn, currentColumn + 1)
							    	  : 0;

	return std::max({ currentArea, extendedRowArea, extendedColumnArea });
}

template <unsigned int M, unsigned int N>
unsigned int GetLargestOneRectangleArea(const Matrix<M, N>& matrix) noexcept
{
	unsigned int maxArea = 0;

	for (unsigned int i = 0; i < M; i++)
	{
		for (unsigned int j = 0; j < N; j++)
		{
			if (unsigned int remainingArea = (M - i) * (N - j); matrix[i][j] == 1 && remainingArea > maxArea)
			{
				unsigned int area = GetLargestOneRectangleAreaHelper(matrix, i, i + 1, j, j + 1);
				maxArea = std::max(area, maxArea);
			}
		}
	}

	return maxArea;
}

int main(int argc, char* argv[])
{
	const Matrix<4, 4> matrix
	{
		std::array<unsigned int, 4> { 1, 0, 0, 0 },
		std::array<unsigned int, 4> { 1, 0, 1, 1 },
		std::array<unsigned int, 4> { 1, 0, 1, 1 },
		std::array<unsigned int, 4> { 0, 1, 0, 0 }
	};

	std::cout << GetLargestOneRectangleArea(matrix) << "\n";

	std::cin.get();

	return 0;
}