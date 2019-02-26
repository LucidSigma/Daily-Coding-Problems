using System;

namespace DailyCodingProblem
{
	internal class Day40
	{
		private static int Main(string[] args)
		{
			int[] numbers = new int[] { 6, 1, 3, 3, 3, 6, 6 };
			Console.WriteLine(GetNonDuplicatedNumber(numbers));

			numbers = new int[] { 13, 19, 13, 13 };
			Console.WriteLine(GetNonDuplicatedNumber(numbers));

			Console.ReadLine();

			return 0;
		}

		private static int GetNonDuplicatedNumber(int[] numbers)
		{
			const int BitsPerInteger = sizeof(int) * 8;
			int uniqueNumber = 0;
			
			for (int i = 0; i < BitsPerInteger; i++)
			{
				int bitSums = 0;
				int currentBit = 1 << i;

				foreach (int number in numbers)
				{
					if ((number & currentBit) == currentBit)
					{
						bitSums++;
					}
				}

				const int NonDuplicateCount = 3;

				if (bitSums % NonDuplicateCount != 0)
				{
					uniqueNumber |= currentBit;
				}
			}

			return uniqueNumber;
		}
	}
}