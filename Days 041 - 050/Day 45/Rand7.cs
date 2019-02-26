using System;

namespace DailyCodingProblem
{
	internal class Day45
	{
		private static Random rng = new Random();

		private static int Main(string[] args)
		{
			string[] histogram = new string[7];

			for (int i = 0; i < 250; i++)
			{
				histogram[Rand7() - 1] += '*';
			}

			for (int i = 0; i < 7; i++)
			{
				Console.WriteLine($"{i + 1}: {histogram[i]}");
			}

			Console.ReadLine();

			return 0;
		}

		private static int Rand5() => rng.Next(1, 6);

		private static int Rand7()
		{
			int sum = 0;

			for (int i = 0; i < 7; i++)
			{
				sum += Rand5();
			}

			return sum % 7 + 1;
		}
	}
}