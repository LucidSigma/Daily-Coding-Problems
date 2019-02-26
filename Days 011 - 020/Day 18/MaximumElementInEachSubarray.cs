using System;
using System.Collections.Generic;

namespace DailyCodingProblem
{
	internal class Day18
	{
		private static int Main(string[] args)
		{
			int[] numbers = new[] { 10, 5, 2, 7, 8, 7 };
			PrintSubarrayMaximums(numbers, 3);

			Console.WriteLine();

			numbers = new int[] { 5, 8, 2, 6, 9, 3, 2, 0, 6, 7 };
			PrintSubarrayMaximums(numbers, 4);

			Console.ReadLine();

			return 0;
		}

		private static void PrintSubarrayMaximums(int[] array, int k)
		{
			LinkedList<int> elements = new LinkedList<int>();

			for (int i = 0; i < k; i++)
			{
				while (elements.Count > 0 && array[i] >= array[elements.Last.Value])
				{
					elements.RemoveLast();
				}

				elements.AddLast(i);
			}

			for (int i = k; i < array.Length; i++)
			{
				Console.WriteLine($"{array[elements.First.Value]} ");

				while (elements.Count > 0 && elements.First.Value <= i - k)
				{
					elements.RemoveFirst();
				}

				while (elements.Count > 0 && array[i] >= array[elements.Last.Value])
				{
					elements.RemoveLast();
				}

				elements.AddLast(i);
			}

			Console.WriteLine(array[elements.First.Value]);
		}
	}
}