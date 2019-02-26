#include <array>
#include <iostream>

static constexpr unsigned int BOX_SIZE = 9;
static constexpr unsigned int SUB_BOX_SIZE = 3;
static constexpr unsigned int EMPTY_CELL = 0;

bool FindEmptyCell(const std::array<std::array<unsigned int, BOX_SIZE>, BOX_SIZE>& grid, unsigned int& row, unsigned int& column) noexcept
{
	for (row = 0; row < BOX_SIZE; row++)
	{
		for (column = 0; column < BOX_SIZE; column++)
		{
			if (grid[row][column] == EMPTY_CELL)
			{
				return true;
			}
		}
	}

	return false;
}

bool IsValidNumber(const std::array<std::array<unsigned int, BOX_SIZE>, BOX_SIZE>& grid, unsigned int row, unsigned int column, unsigned int number) noexcept
{
	for (unsigned int i = 0; i < BOX_SIZE; c++)
	{
		if (grid[row][i] == number || grid[i][column] == number)
		{
			return false;
		}
	}

	for (unsigned int r = 0; r < SUB_BOX_SIZE; r++)
	{
		for (unsigned int c = 0; c < SUB_BOX_SIZE; c++)
		{
			if (grid[r + row - (row % SUB_BOX_SIZE)][c + column - (column % SUB_BOX_SIZE)] == number)
			{
				return false;
			}
		}
	}

	return grid[row][column] == EMPTY_CELL;
}

bool SolveSudoku(std::array<std::array<unsigned int, BOX_SIZE>, BOX_SIZE>& grid) noexcept
{
	unsigned int row;
	unsigned int column;

	if (!FindEmptyCell(grid, row, column))
	{
		return true;
	}

	for (unsigned int number = 1; number <= BOX_SIZE; number++)
	{
		if (IsValidNumber(grid, row, column, number))
		{
			grid[row][column] = number;

			if (SolveSudoku(grid))
			{
				return true;
			}
			else
			{
				grid[row][column] = EMPTY_CELL;
			}
		}
	}

	return false;
}

void PrintSudoku(std::array<std::array<unsigned int, BOX_SIZE>, BOX_SIZE>& grid)
{
	for (const auto& row : grid)
	{
		for (const int cell : row)
		{
			std::cout << cell << " ";
		}

		std::cout << "\n";
	}
}

int main(int argc, const char* argv[])
{
	std::array<std::array<unsigned int, BOX_SIZE>, BOX_SIZE> sudoku
	{
		std::array<unsigned int, BOX_SIZE> { 0, 4, 3, 2, 6, 0, 0, 0, 0 },
		std::array<unsigned int, BOX_SIZE> { 0, 0, 6, 0, 0, 0, 0, 0, 3 },
		std::array<unsigned int, BOX_SIZE> { 0, 8, 9, 1, 0, 5, 0, 0, 0 },
		std::array<unsigned int, BOX_SIZE> { 0, 3, 0, 6, 0, 0, 0, 0, 4 },
		std::array<unsigned int, BOX_SIZE> { 4, 7, 0, 0, 1, 0, 0, 3, 8 },
		std::array<unsigned int, BOX_SIZE> { 8, 0, 0, 0, 0, 4, 0, 7, 0 },
		std::array<unsigned int, BOX_SIZE> { 0, 0, 0, 7, 0, 6, 1, 8, 0 },
		std::array<unsigned int, BOX_SIZE> { 1, 0, 0, 0, 0, 0, 9, 0, 0 },
		std::array<unsigned int, BOX_SIZE> { 0, 0, 0, 0, 9, 1, 3, 2, 0 }
	};
	
	SolveSudoku(sudoku);
	PrintSudoku(sudoku);

	std::cin.get();

	return 0;
}