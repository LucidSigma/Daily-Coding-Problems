using System;

namespace DailyCodingProblem
{
	internal class Day61
	{
		private static int Main(string[] args)
		{
			Console.WriteLine(Pow(2, 10));
			Console.WriteLine(Pow(2, -10));
			Console.WriteLine(Pow(10, 3));
			Console.WriteLine(Pow(10, -3));
			Console.WriteLine(Pow(5, 0));

			try
			{
				Console.WriteLine(Pow(0, 0));
			}
			catch (InvalidOperationException e)
			{
				Console.WriteLine(e.Message);
			}

			Console.ReadLine();

			return 0;
		}

		private static float Pow(int x, int y)
		{
			if (x == 0 && y == 0)
			{
				throw new InvalidOperationException("0 ^ 0 is an undefined operation.");
			}

			if (y == 0)
			{
				return 1;
			}

			uint positiveY = (uint)Math.Abs(y);
			uint currentPower = 1;
			uint previousPower = 0;

			float previousResult = 0.0f;
			float result = x;

			while (currentPower <= positiveY)
			{
				previousResult = result;
				previousPower = currentPower;
				result *= result;
				currentPower <<= 1;
			}

			previousResult *= Pow(x, (int)(positiveY - previousPower));

			return y != positiveY ? 1.0f / previousResult : previousResult;
		}
	}
}