using System;
using System.Collections.Generic;

namespace DailyCodingProblem
{
	internal class Day13
	{
		private static int Main(string[] args)
		{
			Console.WriteLine(GetMaxLengthOfDistinctSubstring("abcba", 2));

			Console.ReadLine();

			return 0;
		}

		private static string GetMaxLengthOfDistinctSubstring(string text, int k)
		{
			if (string.IsNullOrEmpty(text))
			{
				return "";
			}
			else if (text.Length <= k)
			{
				return text;
			}
			else if (k == 1)
			{
				return new string(text[0], 1);
			}

			int uniqueCharacterCount = 0;
			HashSet<int> seenCharacters = new HashSet<int>();

			char firstChar = text[0];
			int secondIndex = 0;

			while (text[secondIndex] == firstChar)
			{
				secondIndex++;
			}

			string substring = text;
			string remainderString = "";

			for (int i = 0; i < text.Length; i++)
			{
				if (!seenCharacters.Contains(text[i]))
				{
					seenCharacters.Add(text[i]);
					uniqueCharacterCount++;
				}

				if (uniqueCharacterCount > k)
				{
					substring = text.Substring(0, i);
					remainderString = text.Substring(secondIndex);

					break;
				}
			}

			string longestInRemainer = GetMaxLengthOfDistinctSubstring(remainderString, k);

			return substring.Length < longestInRemainer.Length ? longestInRemainer : substring;
		}
	}
}