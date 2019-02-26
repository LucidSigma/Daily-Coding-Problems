using System;
using System.Collections.Generic;

namespace DailyCodingProblem
{
	internal class Day33
	{
		private static int Main(string[] args)
		{
			int[] numbers = new int[] { 2, 1, 5, 7, 2, 0, 5 };
			PrintRunningMedian(numbers);

			Console.ReadLine();

			return 0;
		}

		private static void PrintRunningMedian(int[] sequence)
		{
			if (sequence.Length == 0)
			{
				return;
			}

			List<int> mins = new List<int>();
			List<int> maxes = new List<int>();
			List<int> medians = new List<int>();

			foreach (int number in sequence)
			{
				mins.Add(number);
				mins.Sort();

				if (mins.Count > maxes.Count + 1)
				{
					int smallestElement = mins[0];
					mins.RemoveAt(0);

					maxes.Add(-smallestElement);
					maxes.Sort();
				}

				float median = mins.Count == maxes.Count ? (mins[0] - maxes[0]) / 2.0f : mins[0];

				Console.WriteLine(median);
			}
		}
	}
}