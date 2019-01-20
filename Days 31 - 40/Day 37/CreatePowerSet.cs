using System;
using System.Collections.Generic;

namespace DailyCodingProblem
{
	internal class Day37
	{
		private static int Main(string[] args)
		{
			List<int> values = new List<int> { 1, 2, 3, 4 };
			List<List<int>> powerSet = CreatePowerSet(values);

			PrintPowerSet(powerSet);

			Console.ReadLine();

			return 0;
		}

		private static List<List<T>> CreatePowerSet<T>(List<T> set)
		{
			int subsets = (int)Math.Pow(2, set.Count);
			List<List<T>> powerSet = new List<List<T>>(subsets);

			for (int i = 0; i < subsets; i++)
			{
				List<T> currentSubset = new List<T>(set.Count);

				for (int j = 0; j < subsets; j++)
				{
					int mask = 1 << j;

					if ((i & mask) == mask)
					{
						currentSubset.Add(set[j]);
					}
				}

				powerSet.Add(currentSubset);
			}

			return powerSet;
		}

		private static void PrintPowerSet<T>(List<List<T>> powerSet)
		{
			foreach (List<T> set in powerSet)
			{
				foreach (T value in set)
				{
					Console.Write($"{value} ");
				}

				Console.WriteLine();
			}
		}
	}
}