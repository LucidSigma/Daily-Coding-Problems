using System;

namespace DailyCodingProblem
{
	internal class Day9
	{
		private static int Main(string[] args)
		{
			int[] numbers = new int[] { 2, 4, 6, 2, 5 };
			Console.WriteLine(FindMaxNonAdjacentSum(numbers));

			numbers = new int[] { 5, 1, 1, 5 };
			Console.WriteLine(FindMaxNonAdjacentSum(numbers));

			Console.ReadLine();

			return 0;
		}

		private static int FindMaxNonAdjacentSum(int[] numbers)
		{
			int sumWithPrevious = numbers[0];
			int sumWithoutPrevious = 0;

			for (int i = 1; i < numbers.Length; i++)
			{
				int sumWithoutPreviousNew = Math.Max(sumWithPrevious, sumWithoutPrevious);

				sumWithPrevious = sumWithoutPrevious + numbers[i];
				sumWithoutPrevious = sumWithoutPreviousNew;
			}

			return Math.Max(sumWithPrevious, sumWithoutPrevious);
		}
	}
}