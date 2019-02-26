using System;
using System.Collections.Generic;
using System.Linq;

namespace DailyCodingProblem
{
	internal class Day60
	{
		private static int Main(string[] args)
		{
			List<int> numbers = new List<int>() { 15, 5, 20, 10, 35, 15, 10 };
			Console.WriteLine(CanSplitEqually(numbers));

			numbers = new List<int>() { 15, 5, 20, 10, 35 };
			Console.WriteLine(CanSplitEqually(numbers));

			Console.ReadLine();

			return 0;
		}

		private static bool CanSplitEqually(List<int> numbers)
		{
			int sum = numbers.Sum();

			if (numbers.Count == 0 || sum % 2 == 1)
			{
				return false;
			}

			List<int> sortedNumbers = numbers;
			sortedNumbers.Sort();

			return CanSplitEquallyHelper(sortedNumbers, 0, numbers.Count - 1, 0, sum);
		}

		private static bool CanSplitEquallyHelper(List<int> numbers, int start, int end, int firstSum, int secondSum)
		{
			if (start >= end)
			{
				return false;
			}
			else if (firstSum == secondSum)
			{
				return true;
			}
			else
			{
				return CanSplitEquallyHelper(numbers, start + 1, end, firstSum + numbers[start], secondSum - numbers[start]) ||
					   CanSplitEquallyHelper(numbers, start, end - 1, firstSum + numbers[end], secondSum - numbers[end]);
			}
		}
	}
}