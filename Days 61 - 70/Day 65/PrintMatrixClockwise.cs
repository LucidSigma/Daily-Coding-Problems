using System;

namespace DailyCodingProblem
{
	internal class Day65
	{
		private static int Main(string[] args)
		{
			int[,] matrix = new int[,]
			{
				{ 1, 2, 3, 4, 5 },
				{ 6, 7, 8, 9, 10 },
				{ 11, 12, 13, 14, 15 },
				{ 16, 17, 18, 19, 20 }
			};

			PrintMatrixClockwise(matrix);

			Console.ReadLine();

			return 0;
		}

		private static void PrintMatrixClockwise(int[,] matrix)
		{
			int rowStartIndex = 0;
			int columnStartIndex = 0;
			int rowEndIndex = matrix.GetLength(0);
			int columnEndIndex = matrix.GetLength(1);

			while (rowStartIndex < rowEndIndex && columnStartIndex < columnEndIndex)
			{
				for (int i = columnStartIndex; i < columnEndIndex; i++)
				{
					Console.WriteLine(matrix[rowStartIndex, i]);
				}

				rowStartIndex++;

				for (int i = rowStartIndex; i < rowEndIndex; i++)
				{
					Console.WriteLine(matrix[i, columnEndIndex - 1]);
				}

				columnEndIndex--;

				if (rowStartIndex < rowEndIndex)
				{
					for (int i = columnEndIndex - 1; i >= columnStartIndex; i--)
					{
						Console.WriteLine(matrix[rowEndIndex - 1, i]);
					}

					rowEndIndex--;
				}

				if (columnStartIndex < columnEndIndex)
				{
					for (int i = rowEndIndex - 1; i >= rowStartIndex; i--)
					{
						Console.WriteLine(matrix[i, columnStartIndex]);
					}

					columnStartIndex++;
				}
			}
		}
	}
}