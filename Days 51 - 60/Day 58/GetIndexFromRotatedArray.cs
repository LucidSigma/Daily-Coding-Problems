using System;

namespace DailyCodingProblem
{
	internal class Day58
	{
		private static int Main(string[] args)
		{
			int[] rotatedArray = { 13, 18, 25, 2, 8, 10 };

			Console.WriteLine(GetIndexFromRotatedArray(rotatedArray, 8));

			Console.ReadLine();

			return 0;
		}

		private static int? GetIndexFromRotatedArray(int[] rotatedArray, int number)
		{
			return GetIndexFromRotatedArrayHelper(rotatedArray, number, 0, rotatedArray.Length);
		}

		private static int? GetIndexFromRotatedArrayHelper(int[] array, int number, int first, int last)
		{
			int midIndex = first + ((last - first) / 2);

			if (array[midIndex] == number)
			{
				return midIndex;
			}
			else if (array[midIndex] > number)
			{
				return array[first] >= number
					   ? GetIndexFromRotatedArrayHelper(array, number, first, midIndex)
					   : GetIndexFromRotatedArrayHelper(array, number, midIndex, last);
			}
			else if (array[midIndex] < number)
			{
				return array[first] <= number
					   ? GetIndexFromRotatedArrayHelper(array, number, first, midIndex)
					   : GetIndexFromRotatedArrayHelper(array, number, midIndex, last);
			}
			else
			{
				return null;
			}
		}
	}
}