using System;

namespace DailyCodingProblem
{
	internal class Day25
	{
		private static int Main(string[] args)
		{
			Console.WriteLine(MatchSimpleRegex(".*at", "chat"));
			Console.WriteLine(MatchSimpleRegex(".*at", "chats"));

			Console.WriteLine(MatchSimpleRegex("ra.", "ray"));
			Console.WriteLine(MatchSimpleRegex("ra.", "raymond"));

			Console.WriteLine(MatchSimpleRegex(".*", "aaaaaaaaaaaaaaaaaa"));
			Console.WriteLine(MatchSimpleRegex(".", "aaaaaaaaaaaaaaaaaa"));

			Console.ReadLine();

			return 0;
		}

		private static bool MatchSimpleRegex(string regex, string text)
		{
			bool[,] matches = new bool[text.Length + 1, regex.Length + 1];
			matches[0, 0] = true;

			const char SingleCharacter = '.';
			const char MultipleCharacters = '*';

			for (int i = 1; i < matches.GetLength(1); i++)
			{
				if (regex[i - 1] == MultipleCharacters)
				{
					matches[0, i] = matches[0, i - 2];
				}
			}

			for (int i = 1; i < matches.GetLength(0); i++)
			{
				for (int j = 1; j < matches.GetLength(1); j++)
				{
					if (regex[j - 1] == SingleCharacter || regex[j - 1] == text[i - 1])
					{
						matches[i, j] = matches[i - 1, j - 1];
					}
					else if (regex[j - 1] == MultipleCharacters)
					{
						matches[i, j] = matches[i, j - 2];

						if (regex[j - 2] == SingleCharacter || regex[j - 2] == text[i - 2])
						{
							matches[i, j] = matches[i, j] || matches[i - 1, j];
						}
					}
					else
					{
						matches[i, j] = false;
					}
				}
			}

			return matches[text.Length, regex.Length];
		}
	}
}