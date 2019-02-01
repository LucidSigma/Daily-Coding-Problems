#include <array>
#include <iostream>

template <unsigned int M, unsigned int N>
void PrintMatrixClockwise(const std::array<std::array<int, N>, M>& matrix) noexcept
{
	int rowStartIndex = 0;
	int columnStartIndex = 0;
	int rowEndIndex = M;
	int columnEndIndex = N;

	while (rowStartIndex < rowEndIndex && columnStartIndex < columnEndIndex)
	{
		for (int i = columnStartIndex; i < columnEndIndex; i++)
		{
			std::cout << matrix[rowStartIndex][i] << "\n";
		}

		rowStartIndex++;

		for (int i = rowStartIndex; i < rowEndIndex; i++)
		{
			std::cout << matrix[i][columnEndIndex - 1] << "\n";
		}

		columnEndIndex--;

		if (rowStartIndex < rowEndIndex)
		{
			for (int i = columnEndIndex - 1; i >= columnStartIndex; i--)
			{
				std::cout << matrix[rowEndIndex - 1][i] << "\n";
			}

			rowEndIndex--;
		}

		if (columnStartIndex < columnEndIndex)
		{
			for (int i = rowEndIndex - 1; i >= rowStartIndex; i--)
			{
				std::cout << matrix[i][columnStartIndex] << "\n";
			}

			columnStartIndex++;
		}
	}
}

int main(int argc, char* argv[])
{
	const std::array<std::array<int, 5>, 4> matrix
	{
		std::array<int, 5> { 1, 2, 3, 4, 5 },
		std::array<int, 5> { 6, 7, 8, 9, 10 },
		std::array<int, 5> { 11, 12, 13, 14, 15 },
		std::array<int, 5> { 16, 17, 18, 19, 20 }
	};

	PrintMatrixClockwise(matrix);

	std::cin.get();

	return 0;
}
