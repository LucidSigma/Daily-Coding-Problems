using System;
using System.Collections.Generic;
using System.Linq;

namespace DailyCodingProblem
{
	internal class Day29
	{
		private static int Main(string[] args)
		{
			Console.WriteLine(RunLengthEncode("AAAABBBCCDAA"));
			Console.WriteLine(RunLengthDecode("4A3B2C1D2A"));

			Console.ReadLine();

			return 0;
		}

		private static string RunLengthEncode(string text)
		{
			int counter = 1;
			char previousCharacter = text[0];
			string encodedString = "";

			for (int i = 1; i < text.Length; i++)
			{
				if (text[i] == previousCharacter)
				{
					counter++;
				}
				else
				{
					encodedString += counter.ToString() + previousCharacter;
					counter = 1;
					previousCharacter = text[i];
				}

				if (i == text.Length - 1)
				{
					encodedString += counter.ToString() + previousCharacter;
				}
			}

			return encodedString;
		}

		private static string RunLengthDecode(string text)
		{
			char[] letters = (from c in text
							  where char.IsLetter(c)
							  select c).ToArray();

			List<string> numbers = text.Split(letters).ToList();
			numbers.RemoveAll(s => string.IsNullOrEmpty(s));

			string decodedString = "";

			for (int i = 0; i < letters.Length; i++)
			{
				decodedString += new string(letters[i], Convert.ToInt32(numbers[i]));
			}

			return decodedString;
		}
	}
}