using System;
using System.Collections.Generic;

namespace DailyCodingProblems
{
	internal class Day4
	{
		private static int Main(string[] args)
		{
			List<int> numbers = new List<int> { 3, 4, -1, 1 };
			Console.WriteLine(GetSmallestMissingPositive(numbers));

			numbers = new List<int> { 1, 2, 0 };
			Console.WriteLine(GetSmallestMissingPositive(numbers));

			Console.ReadLine();

			return 0;
		}

		private static int GetSmallestMissingPositive(List<int> numbers)
		{
			int nonPositiveCount = SplitPositives(numbers);

			if (nonPositiveCount == numbers.Count)
			{
				return 1;
			}

			int positiveCount = numbers.Count - nonPositiveCount;

			for (int i = nonPositiveCount; i < numbers.Count; i++)
			{
				if (numbers[i] - 1 < positiveCount)
				{
					numbers[numbers[i] - 1] *= -1;
				}
			}

			for (int i = nonPositiveCount; i < numbers.Count; i++)
			{
				if (numbers[i] > 0)
				{
					return i + 1;
				}
			}

			return positiveCount + 1;
		}

		private static int SplitPositives(List<int> numbers)
		{
			int nonPositiveCount = 0;

			for (int i = 0; i < numbers.Count; i++)
			{
				if (numbers[i] <= 0)
				{
					int temp = numbers[i];
					numbers[i] = numbers[nonPositiveCount];
					numbers[nonPositiveCount] = temp;

					nonPositiveCount++;
				}
			}

			return nonPositiveCount;
		}
	}
}