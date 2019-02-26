using System;
using System.Collections.Generic;

namespace DailyCodingProblem
{
	internal class Day27
	{
		private enum BracketState { Open, Closed }
		private enum BracketType { Parenthesis, Square, Brace, Chevron }

		private static int Main(string[] args)
		{
			Console.WriteLine(HasValidBrackets("([])[]({})"));
			Console.WriteLine(HasValidBrackets("([)]"));
			Console.WriteLine(HasValidBrackets("(((()"));
			Console.WriteLine(HasValidBrackets("s(sd[g35{4mj6m,j5l<46k>5kik65mkili}7]uu7gd)78fsdf"));

			Console.ReadLine();

			return 0;
		}

		private static bool HasValidBrackets(string text)
		{
			char[,] brackets = new char[,]
			{
				{ '(', ')' },
				{ '[', ']' },
				{ '{', '}' },
				{ '<', '>' }
			};

			bool IsBracket(char bracket, BracketState state)
			{
				for (int i = 0; i < brackets.GetLength(0); i++)
				{
					if (bracket == brackets[i, (int)state])
					{
						return true;
					}
				}

				return false;
			}

			BracketType? GetBracketType(char bracket)
			{
				for (int i = 0; i < brackets.GetLength(0); i++)
				{
					if (bracket == brackets[i, (int)BracketState.Open] || bracket == brackets[i, (int)BracketState.Closed])
					{
						return (BracketType)i;
					}
				}

				return null;
			}

			Stack<char> bracketStack = new Stack<char>();

			foreach (char letter in text)
			{
				if (IsBracket(letter, BracketState.Open))
				{
					bracketStack.Push(letter);
				}
				else if (IsBracket(letter, BracketState.Closed))
				{
					if (bracketStack.Peek() == brackets[(int)GetBracketType(letter), (int)BracketState.Open])
					{
						bracketStack.Pop();
					}
					else
					{
						return false;
					}
				}
			}

			return bracketStack.Count == 0;
		}
	}
}