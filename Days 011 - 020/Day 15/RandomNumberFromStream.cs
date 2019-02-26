using System;

namespace DailyCodingProblem
{
	internal class Day15
	{
		private static Random rng = new Random();

		private static int randomStreamNumber = 0;
		private static int count = 0;

		private static int Main(string[] args)
		{
			int randomNumber = 0;

			Console.Write("Total number of numbers to enter: ");
			int numberCount = Convert.ToInt32(Console.ReadLine());

			for (int i = 0; i < numberCount; i++)
			{
				Console.Write("Enter a number: ");
				int currentNumber = Convert.ToInt32(Console.ReadLine());

				randomNumber = SelectRandomFromStream(currentNumber);
			}

			Console.WriteLine($"Random number: {randomNumber}");

			Console.ReadLine();

			return 0;
		}

		private static int SelectRandomFromStream(int currentNumber, bool resetStream = false)
		{
			if (resetStream)
			{
				randomStreamNumber = 0;
				count = 0;
			}

			count++;

			if (count == 1)
			{
				randomStreamNumber = currentNumber;
			}
			else
			{
				int randomNumber = rng.Next(0, count + 1);

				if (randomNumber == count - 1)
				{
					randomStreamNumber = currentNumber;
				}
			}

			return randomStreamNumber;
		}
	}
}