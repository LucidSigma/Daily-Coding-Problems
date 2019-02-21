using System;
using System.Collections.Generic;

namespace DailyCodingProblem
{
	internal class Day75
	{
		private static Dictionary<int, int> numberCache = new Dictionary<int, int>();

		private static int Main(string[] args)
		{
			int[] array = { 0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15 };

			Console.WriteLine(GetLongestIncreasingSubsequenceLength(array));

			Console.ReadLine();

			return 0;
		}

		private static int GetLongestIncreasingSubsequenceLength(int[] array) => GetLongestIncreasingSubsequencelengthHelper(array, 0);

		private static int GetLongestIncreasingSubsequencelengthHelper(int[] array, int startIndex)
		{
			if (startIndex == array.Length)
			{
				return 0;
			}

			int currentNumber = array[startIndex];
			int maxIncrement = 1;

			for (int i = startIndex + 1; i < array.Length; i++)
			{
				int count;

				if (array[i] >= currentNumber)
				{
					if (numberCache.ContainsKey(i))
					{
						count = numberCache[i];
					}
					else
					{
						count = GetLongestIncreasingSubsequencelengthHelper(array, i) + 1;
						numberCache.Add(i, count);
					}

					maxIncrement = Math.Max(maxIncrement, count);
				}
			}

			return maxIncrement;
		}
	}
}