#include <algorithm>
#include <array>
#include <iostream>

template <unsigned int N>
using Matrix = std::array<std::array<int, N>, N>;

template <unsigned int N>
void RotateMatrixClockwise(Matrix<N>& matrix) noexcept
{
	for (unsigned int i{ 0u }; i < N / 2u; ++i)
	{
		static constexpr unsigned int MaxIndex{ N - 1u };

		for (unsigned int j{ i }; j < MaxIndex - i; ++j)
		{
			std::swap(matrix[i][j], matrix[MaxIndex - j][i]);
			std::swap(matrix[MaxIndex - j][i], matrix[MaxIndex - i][MaxIndex - j]);
			std::swap(matrix[MaxIndex - i][MaxIndex - j], matrix[j][MaxIndex - i]);
		}
	}
}

template <unsigned int N>
std::ostream& operator <<(std::ostream& outputStream, const Matrix<N>& matrix) noexcept
{
	for (const auto& row : matrix)
	{
		for (const auto& number : row)
		{
			outputStream << number << " ";
		}

		outputStream << "\n";
	}

	return outputStream;
}

int main(int argc, char* argv[])
{
	Matrix<3u> matrix
	{
		std::array<int, 3u>{ 1, 2, 3 },
		std::array<int, 3u>{ 4, 5, 6 },
		std::array<int, 3u>{ 7, 8, 9 }
	};

	RotateMatrixClockwise(matrix);

	std::cout << matrix << "\n";

	std::cin.get();

	return 0;
}
