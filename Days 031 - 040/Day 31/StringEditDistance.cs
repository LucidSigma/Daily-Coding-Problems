using System;
using System.Collections.Generic;

namespace DailyCodingProblem
{
	internal class Day31
	{
		private static int Main(string[] args)
		{
			Console.WriteLine(EditDistance("kitten", "sitting"));

			Console.ReadLine();

			return 0;
		}

		private static int EditDistance(string source, string destination)
		{
			List<List<int>> solutions = new List<List<int>>(source.Length + 1);

			for (int i = 0; i < source.Length + 1; i++)
			{
				solutions.Add(new List<int>(destination.Length + 1));

				for (int j = 0; j < destination.Length + 1; j++)
				{
					solutions[i].Add(0);

					if (i == 0)
					{
						solutions[i][j] = j;
					}
					else if (j == 0)
					{
						solutions[i][j] = i;
					}
					else if (source[i - 1] == destination[j - 1])
					{
						solutions[i][j] = solutions[i - 1][j - 1];
					}
					else
					{
						solutions[i][j] = MinOfThree(solutions[i][j - 1], solutions[i - 1][j], solutions[i - 1][j - 1]) + 1;
					}
				}
			}

			return solutions[source.Length][destination.Length];
		}

		private static int MinOfThree(int a, int b, int c)
		{
			return Math.Min(Math.Min(a, b), c);
		}
	}
}