using System;

namespace DailyCodingProblem
{
	internal class Day54
	{
		private const int BoxSize = 9;
		private const int SubBoxSize = 3;
		private const int EmptyCell = 0;

		private static int Main(string[] args)
		{
			int[,] sudoku = new int[BoxSize, BoxSize]
			{
				{ 0, 4, 3, 2, 6, 0, 0, 0, 0 },
				{ 0, 0, 6, 0, 0, 0, 0, 0, 3 },
				{ 0, 8, 9, 1, 0, 5, 0, 0, 0 },
				{ 0, 3, 0, 6, 0, 0, 0, 0, 4 },
				{ 4, 7, 0, 0, 1, 0, 0, 3, 8 },
				{ 8, 0, 0, 0, 0, 4, 0, 7, 0 },
				{ 0, 0, 0, 7, 0, 6, 1, 8, 0 },
				{ 1, 0, 0, 0, 0, 0, 9, 0, 0 },
				{ 0, 0, 0, 0, 9, 1, 3, 2, 0 }
			};

			SolveSudoku(sudoku);
			PrintSudoku(sudoku);

			Console.ReadLine();

			return 0;
		}

		private static bool SolveSudoku(int[,] grid)
		{
			int row = 0;
			int column = 0;

			if (!FindEmptyCell(grid, ref row, ref column))
			{
				return true;
			}

			for (int number = 1; number <= BoxSize; number++)
			{
				if (IsValidNumber(grid, row, column, number))
				{
					grid[row, column] = number;

					if (SolveSudoku(grid))
					{
						return true;
					}
					else
					{
						grid[row, column] = EmptyCell;
					}
				}
			}

			return false;
		}

		private static bool IsValidNumber(int[,] grid, int row, int column, int number)
		{
			for (int i = 0; i < BoxSize; i++)
			{
				if (grid[row, i] == number || grid[i, column] == number)
				{
					return false;
				}
			}

			for (int r = 0; r < SubBoxSize; r++)
			{
				for (int c = 0; c < SubBoxSize; c++)
				{
					if (grid[r + row - (row % SubBoxSize), c + column - (column % SubBoxSize)] == number)
					{
						return false;
					}
				}
			}

			return grid[row, column] == EmptyCell;
		}

		private static bool FindEmptyCell(int[,] grid, ref int row, ref int column)
		{
			for (row = 0; row < BoxSize; row++)
			{
				for (column = 0; column < BoxSize; column++)
				{
					if (grid[row, column] == EmptyCell)
					{
						return true;
					}
				}
			}

			return false;
		}

		private static void PrintSudoku(int[,] grid)
		{
			for (int i = 0; i < grid.GetLength(0); i++)
			{
				for (int j = 0; j < grid.GetLength(1); j++)
				{
					Console.Write($"{grid[i, j]} ");
				}

				Console.WriteLine();
			}
		}
	}
}