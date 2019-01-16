using System;
using System.Collections.Generic;

namespace DailyCodingProblem
{
	internal class Day12
	{
		private static int Main(string[] args)
		{
			Console.WriteLine(GetStaircasePermutations(4, 1, 3, 5));

			Console.ReadLine();

			return 0;
		}

		private static int GetStaircasePermutations(int stairCount, params int[] spacings)
		{
			List<int> sequence = new List<int>(stairCount + 1) { 1 };

			for (int i = 1; i < stairCount + 1; i++)
			{
				sequence.Add(0);
			}

			for (int i = 1; i < sequence.Count; i++)
			{
				foreach (int space in spacings)
				{
					int difference = i - space;

					if (difference > 0)
					{
						sequence[i] += sequence[difference];
					}

					if (i == space)
					{
						sequence[i]++;
					}
				}
			}

			return sequence[sequence.Count - 1];
		}
	}
}