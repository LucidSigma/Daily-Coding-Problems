using System;

namespace DailyCodingProblem
{
	internal class Day19
	{
		private static int Main(string[] args)
		{
			int[] row1 = new int[] { 3, 5, 6 };
			int[] row2 = new int[] { 4, 7, 2 };
			int[] row3 = new int[] { 7, 1, 3 };
			int[] row4 = new int[] { 6, 2, 4 };
			int[] row5 = new int[] { 9, 8, 1 };

			int[][] matrix = new int[][] { row1, row2, row3, row4, row5 };

			Console.WriteLine(GetOptimisedCost(matrix));

			Console.ReadLine();

			return 0;
		}

		private static int GetOptimisedCost(int[][] costs)
		{
			int previousMin = 0;
			int previousSecondMin = 0;
			int previousColour = -1;

			int[][] totalCosts = costs;

			for (int i = 0; i < costs.Length; i++)
			{
				int currentMin = int.MaxValue;
				int currentSecondMin = int.MaxValue;
				int currentColour = -1;

				for (int j = 0; j < costs[i].Length; j++)
				{
					totalCosts[i][j] = totalCosts[i][j] + (previousColour == j ? previousSecondMin : previousMin);

					if (totalCosts[i][j] < currentMin)
					{
						currentSecondMin = currentMin;
						currentMin = totalCosts[i][j];
						currentColour = j;
					}
					else if (totalCosts[i][j] < currentSecondMin)
					{
						currentSecondMin = totalCosts[i][j];
					}
				}

				previousMin = currentMin;
				previousSecondMin = currentSecondMin;
				previousColour = currentColour;
			}

			return previousMin;
		}
	}
}