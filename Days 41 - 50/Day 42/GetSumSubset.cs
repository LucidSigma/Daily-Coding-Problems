using System;
using System.Collections.Generic;
using System.Linq;

namespace DailyCodingProblem
{
	internal class Day42
	{
		private static int Main(string[] args)
		{
			List<int> numbers = new List<int>() { 12, 1, 61, 5, 9, 2 };
			PrintList(GetSumSubset(numbers, 24));

			Console.ReadLine();

			return 0;
		}

		private static List<int> GetSumSubset(List<int> numbers, int sum)
		{
			if (numbers.Count == 0)
			{
				return new List<int>();
			}

			if (numbers[0] == sum)
			{
				return new List<int>() { numbers[0] };
			}

			List<int> withFirstNumber = GetSumSubset(numbers.Skip(1).ToList(), sum - numbers[0]);

			if (withFirstNumber.Count > 0)
			{
				withFirstNumber.Add(numbers[0]);
				return withFirstNumber;
			}
			else
			{
				return GetSumSubset(numbers.Skip(1).ToList(), sum);
			}
		}

		private static void PrintList<T>(List<T> values)
		{
			foreach (T value in values)
			{
				Console.Write($"{value} ");
			}

			Console.WriteLine();
		}
	}
}