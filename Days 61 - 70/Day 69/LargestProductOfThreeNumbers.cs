using System;

namespace DailyCodingProblem
{
	internal class TripleMax
	{
		public int A { get; private set; } = int.MinValue;
		public int B { get; private set; } = int.MinValue;
		public int C { get; private set; } = int.MinValue;

		public int TotalAdded { get; private set; } = 0;

		public void Add(int number)
		{
			if (number > A)
			{
				C = B;
				B = A;
				A = number;
			}
			else if (number > B)
			{
				C = B;
				B = number;
			}
			else if (number > C)
			{
				C = number;
			}

			TotalAdded++;
		}
	}

	internal class Day69
	{
		private static int Main(string[] args)
		{
			Console.WriteLine(GetMaxProductFromThreeNumbers(new int[] { -10, -10, 5, 2 }));
			Console.WriteLine(GetMaxProductFromThreeNumbers(new int[] { -10, 10, 5, 2 }));
			Console.WriteLine(GetMaxProductFromThreeNumbers(new int[] { -10, -10, -5, 2, 7, 9 }));
			Console.WriteLine(GetMaxProductFromThreeNumbers(new int[] { -10, 10, -5, 2, 7, 9 }));
			Console.WriteLine(GetMaxProductFromThreeNumbers(new int[] { -10, 5, 0, -20 }));
			Console.WriteLine(GetMaxProductFromThreeNumbers(new int[] { -10, 5, 0, 20 }));

			Console.ReadLine();

			return 0;
		}

		private static int GetMaxProductFromThreeNumbers(int[] numbers)
		{
			if (numbers.Length == 3)
			{
				return numbers[0] * numbers[1] * numbers[2];
			}

			TripleMax maxPositives = new TripleMax();
			(int, int) minNegatives = (int.MaxValue, int.MaxValue);
			int negativeCount = 0;

			foreach (int number in numbers)
			{
				if (number >= 0)
				{
					maxPositives.Add(number);
				}
				else
				{
					AddToNegativePair(ref minNegatives, number);
					negativeCount++;
				}
			}

			int productWithNegatives = int.MinValue;

			if (negativeCount >= 2 && maxPositives.TotalAdded >= 1)
			{
				productWithNegatives = minNegatives.Item1 * minNegatives.Item2 * maxPositives.A;
			}

			int productWithoutNegatives = maxPositives.A * maxPositives.B * maxPositives.C;

			return Math.Max(productWithoutNegatives, productWithNegatives);
		}

		private static void AddToNegativePair(ref (int, int) negativePair, int number)
		{
			if (number < negativePair.Item1)
			{
				negativePair.Item2 = negativePair.Item1;
				negativePair.Item1 = number;
			}
			else if (number < negativePair.Item2)
			{
				negativePair.Item2 = number;
			}
		}
	}
}