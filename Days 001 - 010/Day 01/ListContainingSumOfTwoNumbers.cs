using System;
using System.Collections.Generic;

namespace DailyCodingProblems
{
	internal class Day1
	{
		private static int Main(string[] args)
		{
			int[] numbers = { 10, 15, 3, 7 };
			Console.WriteLine(ContainsTwoNumberSum(numbers, 10));

			Console.ReadLine();

			return 0;
		}

		private static bool ContainsTwoNumberSum(int[] numberList, int sum)
		{
			HashSet<int> searchedNumbers = new HashSet<int>();

			foreach (int number in numberList)
			{
				if (searchedNumbers.Contains(sum - number))
				{
					return true;
				}

				searchedNumbers.Add(number);
			}

			return false;
		}
	}
}