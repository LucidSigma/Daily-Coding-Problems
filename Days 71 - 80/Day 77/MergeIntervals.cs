using System;
using System.Collections.Generic;
using System.Linq;

namespace DailyCodingProblem
{
	internal class Day77
	{
		private static int Main(string[] args)
		{
			List<(int, int)> intervals = new List<(int, int)>
			{
				(1, 3),
				(5, 8),
				(4, 10),
				(20, 25)
			};

			PrintList(MergeOverlappingIntervals(intervals));

			Console.ReadLine();

			return 0;
		}

		private static List<(int, int)> MergeOverlappingIntervals(List<(int, int)> intervals)
		{
			HashSet<int> starts = new HashSet<int>();
			HashSet<int> ends = new HashSet<int>();

			foreach ((int currentStart, int currentEnd) in intervals)
			{
				starts.Add(currentStart);
				ends.Add(currentEnd);
			}

			int minStart = starts.Min();
			int maxEnd = ends.Max();
			int current = 0;
			List<int> statuses = new List<int> { current };

			for (int i = minStart; i < maxEnd; i++)
			{
				if (ends.Contains(i))
				{
					current--;
				}

				if (starts.Contains(i))
				{
					current++;
				}

				statuses.Add(current);
			}

			int start = 0;
			int end = 0;
			List<(int, int)> merged = new List<(int, int)>();

			for (int i = 1; i < statuses.Count; i++)
			{
				if (statuses[i] != 0 && statuses[i - 1] == 0)
				{
					start = i;
				}

				if (statuses[i] == 0 && statuses[i - 1] != 0)
				{
					end = i;
					merged.Add((start, end));

					start = 0;
					end = 0;
				}
			}

			return merged;
		}

		private static void PrintList<T>(List<T> list)
		{
			foreach (T value in list)
			{
				Console.WriteLine(value);
			}
		}
	}
}