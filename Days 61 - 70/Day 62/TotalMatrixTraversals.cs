using System;

namespace DailyCodingProblem
{
	internal class Day62
	{
		private static int Main(string[] args)
		{
			Console.WriteLine(TotalMatrixTraversals(2, 2));
			Console.WriteLine(TotalMatrixTraversals(5, 5));

			Console.ReadLine();

			return 0;
		}

		private static int TotalMatrixTraversals(int rows, int columns)
		{
			if (rows == 0 || columns == 0)
			{
				return 0;
			}

			return TotalMatrixTraversalsHelper(rows, columns, 0, 0);
		}

		private static int TotalMatrixTraversalsHelper(int rows, int columns, int currentRow, int currentColumn)
		{
			if (currentRow == rows - 1 && currentColumn == columns - 1)
			{
				return 1;
			}

			int traversals = 0;

			if (currentRow < rows - 1)
			{
				traversals += TotalMatrixTraversalsHelper(rows, columns, currentRow + 1, currentColumn);
			}

			if (currentColumn < columns - 1)
			{
				traversals += TotalMatrixTraversalsHelper(rows, columns, currentRow, currentColumn + 1);
			}

			return traversals;
		}
	}
}