using System;

namespace DailyCodingProblem
{
	internal class Day30
	{
		private static int Main(string[] args)
		{
			int[] heights = new int[] { 2, 1, 2 };
			Console.WriteLine(CalculateTrappedWater(heights));

			heights = new int[] { 3, 0, 1, 3, 0, 5 };
			Console.WriteLine(CalculateTrappedWater(heights));

			Console.ReadLine();

			return 0;
		}

		private static int CalculateTrappedWater(int[] heights)
		{
			int totalTrappedwater = 0;
			int currentPoolLeft = 0;
			int currentPoolRight = 0;

			int lowIndex = 0;
			int highIndex = heights.Length - 1;

			while (lowIndex <= highIndex)
			{
				if (heights[lowIndex] < heights[highIndex])
				{
					if (heights[lowIndex] > currentPoolLeft)
					{
						currentPoolLeft = heights[lowIndex];
					}
					else
					{
						totalTrappedwater += currentPoolLeft - heights[lowIndex];
						lowIndex++;
					}
				}
				else
				{
					if (heights[highIndex] > currentPoolRight)
					{
						currentPoolRight = heights[highIndex];
					}
					else
					{
						totalTrappedwater += currentPoolRight - heights[highIndex];
						highIndex--;
					}
				}
			}

			return totalTrappedwater;
		}
	}
}