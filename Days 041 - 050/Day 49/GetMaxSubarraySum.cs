using System;
using System.Linq;

namespace DailyCodingProblem
{
	internal class Day49
	{
		private static int Main(string[] args)
		{
			int[] numbers = new int[] { 34, -50, 42, 14, -5, 86 };
			Console.WriteLine(GetMaxSubarraySum(numbers));

			numbers = new int[] { -5, -1, -8, -9 };
			Console.WriteLine(GetMaxSubarraySum(numbers));

			Console.ReadLine();

			return 0;
		}

		private static int GetMaxSubarraySum(int[] numbers)
		{
			int maxElement = numbers.Max();

			if (numbers.Length == 0 || maxElement < 0)
			{
				return 0;
			}

			int currentMaxSum = numbers[0];
			int maxSum = numbers[0];

			for (int i = 1; i < numbers.Length; i++)
			{
				currentMaxSum = Math.Max(numbers[i], currentMaxSum + numbers[i]);
				maxSum = Math.Max(maxSum, currentMaxSum);
			}

			return maxSum;
		}
	}
}