using System;

namespace DailyCodingProblem
{
	internal class Day76
	{
		private static int Main(string[] args)
		{
			char[,] matrix = new char[,] { { 'c', 'b', 'a' }, { 'd', 'a', 'f' }, { 'g', 'h', 'i' } };
			Console.WriteLine(GetColumnRemovalCount(matrix));

			matrix = new char[,] { { 'a', 'b', 'c', 'd', 'e', 'f' } };
			Console.WriteLine(GetColumnRemovalCount(matrix));

			matrix = new char[,] { { 'z', 'y', 'x' }, { 'w', 'v', 'u' }, { 't', 's', 'r' } };
			Console.WriteLine(GetColumnRemovalCount(matrix));

			Console.ReadLine();

			return 0;
		}

		private static int GetColumnRemovalCount(char[,] matrix)
		{
			if (matrix.Length == 0)
			{
				return 0;
			}

			int rows = matrix.GetLength(0);

			if (rows == 1)
			{
				return 0;
			}

			int columns = matrix.GetLength(1);
			int columnRemovalCount = 0;

			for (int i = 0; i < columns; i++)
			{
				for (int j = 1; j < rows; j++)
				{
					if (matrix[j - 1, i] > matrix[j, i])
					{
						columnRemovalCount++;
						break;
					}
				}
			}

			return columnRemovalCount;
		}
	}
}