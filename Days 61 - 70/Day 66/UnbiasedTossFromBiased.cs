using System;

namespace DailyCodingProblem
{
	internal class Day66
	{
		private static Random rng = new Random();

		private static int Main(string[] args)
		{
			const int TestCount = 100;
			string[] histogram = { "", "" };

			for (int i = 0; i < TestCount; i++)
			{
				int flip = TossUnbiased() ? 1 : 0;
				histogram[flip] += '*';
			}

			for (int i = 0; i < histogram.Length; i++)
			{
				Console.WriteLine($"{i} results: {histogram[i]}");
			}

			Console.ReadLine();

			return 0;
		}

		private static bool TossBiased()
		{
			int randomNumber = rng.Next(1, 11);

			return randomNumber <= 7;
		}

		private static bool TossUnbiased()
		{
			const int Iterations = 10_000;
			int[] coinTosses = { 0, 0 };

			for (int i = 0; i < Iterations; i++)
			{
				bool currentFlip = TossBiased();
				currentFlip = i % 2 == 0 ? !currentFlip : currentFlip;

				int index = currentFlip ? 1 : 0;
				coinTosses[index]++;
			}

			return coinTosses[0] < coinTosses[1];
		}
	}
}