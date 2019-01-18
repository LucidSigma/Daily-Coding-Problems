using System;
using System.Collections.Generic;
using System.Linq;

namespace DailyCodingProblem
{
	internal class Day28
	{
		private static int Main(string[] args)
		{
			List<string> words = "The quick brown fox jumps over the lazy dog.".Split(' ').ToList();
			List<string> lines = JustifyText(words, 16);

			PrintList(lines);

			Console.ReadLine();

			return 0;
		}

		private static List<string> JustifyText(List<string> words, int lineLength)
		{
			List<List<string>> wordsEachLine = new List<List<string>>();
			string currentLine = "";
			List<string> currentWordsInLine = new List<string>();

			foreach (string word in words)
			{
				if ((currentLine + word).Length < lineLength)
				{
					currentLine += word + ' ';
					currentWordsInLine.Add(word);
				}
				else
				{
					wordsEachLine.Add(new List<string>(currentWordsInLine));
					currentWordsInLine.Clear();

					currentLine = word + ' ';
					currentWordsInLine.Add(word);
				}

				if (word == words[words.Count - 1])
				{
					wordsEachLine.Add(new List<string>(currentWordsInLine));
				}
			}

			List<string> justifiedLines = new List<string>();

			foreach (List<string> line in wordsEachLine)
			{
				if (line.Count > 1)
				{
					int length = 0;

					foreach (string word in line)
					{
						length += word.Length;
					}

					int difference = lineLength - length;
					int spaceSize = difference / (line.Count - 1);
					int extraSpace = lineLength - length - ((line.Count - 1) * spaceSize);
					string justifiedLine = "";

					foreach (string word in line)
					{
						justifiedLine += word;
						justifiedLine += extraSpace > 0 ? new string(' ', spaceSize + 1) : new string(' ', spaceSize);

						if (extraSpace > 0)
						{
							extraSpace--;
						}
					}

					justifiedLines.Add(justifiedLine);
				}
				else
				{
					justifiedLines.Add(line[0] + new string(' ', lineLength - line[0].Length));
				}
			}

			return justifiedLines;
		}

		private static void PrintList<T>(List<T> list)
		{
			foreach (T value in list)
			{
				Console.WriteLine($"{value} ");
			}
		}
	}
}