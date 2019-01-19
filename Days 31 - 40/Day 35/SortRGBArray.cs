using System;

namespace DailyCodingProblem
{
	internal class Day35
	{
		private static int Main(string[] args)
		{
			char[] array = new char[] { 'G', 'B', 'R', 'R', 'B', 'R', 'G' };
			Console.Write("Original array: ");
			PrintArray(array);

			Console.Write("  Sorted array: ");
			PrintArray(SortRGBArray(array));

			Console.ReadLine();

			return 0;
		}

		private static char[] SortRGBArray(char[] array)
		{
			const int TotalElements = 3;
			char[] Elements = new char[TotalElements] {'R', 'G', 'B' };

			char[] sortedArray = new char[array.Length];
			Array.Copy(array, sortedArray, array.Length);

			int partition = -1;

			for (int i = 0; i < TotalElements; i++)
			{
				partition = PullElementsToFront(sortedArray, partition + 1, sortedArray.Length - 1, Elements[i]);
			}

			return sortedArray;
		}

		private static int PullElementsToFront(char[] array, int startIndex, int endIndex, char element)
		{
			int currentIndex = -1;

			while (startIndex < endIndex)
			{
				if (array[startIndex] == element)
				{
					currentIndex = startIndex;
					startIndex++;
				}
				else if (array[endIndex] != element)
				{
					endIndex--;
				}
				else
				{
					currentIndex = startIndex;

					char temp = array[startIndex];
					array[startIndex] = array[endIndex];
					array[endIndex] = temp;
				}
			}

			return currentIndex;
		}

		private static void PrintArray<T>(T[] array)
		{
			foreach (T value in array)
			{
				Console.Write($"{value} ");
			}

			Console.WriteLine();
		}
	}
}