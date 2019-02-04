using System;

namespace DailyCodingProblem
{
	internal class Day63
	{
		private static int Main(string[] args)
		{
			char[,] matrix = new char[,]
			{
				{ 'F', 'A', 'C', 'I' },
				{ 'O', 'B', 'Q', 'P' },
				{ 'A', 'N', 'O', 'B' },
				{ 'M', 'A', 'S', 'S' },
			};

			Console.WriteLine(ContainsWord(matrix, "FOAM"));
			Console.WriteLine(ContainsWord(matrix, "TEST"));
			Console.WriteLine(ContainsWord(matrix, "MASS"));

			Console.ReadLine();

			return 0;
		}

		private static bool ContainsWord(char[,] letterMatrix, string word)
		{
			int width = letterMatrix.GetLength(1);
			int height = letterMatrix.GetLength(0);

			for (int i = 0; i < Math.Max(width, height); i++)
			{
				string horizonal = "";

				if (i < height)
				{
					for (int j = 0; j < width; j++)
					{
						horizonal += letterMatrix[i, j];
					}
				}

				string vertical = "";

				if (i < width)
				{
					for (int j = 0; j < height; j++)
					{
						vertical += letterMatrix[j, i];
					}
				}

				if (horizonal == word || vertical == word)
				{
					return true;
				}
			}

			return false;
		}
	}
}