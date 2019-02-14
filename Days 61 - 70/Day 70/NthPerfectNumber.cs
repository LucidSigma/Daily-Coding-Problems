using System;

namespace DailyCodingProblem
{
	internal class Day70
	{
		private static int Main(string[] args)
		{
			for (int i = 1; i <= 20; i++)
			{
				Console.WriteLine(GetNthPerfectNumber(i));
			}

			Console.ReadLine();

			return 0;
		}

		private static int GetNthPerfectNumber(int n) => 9 * (n + (n / 10)) + 10;
	}
}