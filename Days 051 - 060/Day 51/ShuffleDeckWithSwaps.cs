using System;
using System.Collections.Generic;

namespace DailyCodingProblem
{
	internal struct Card
	{
		public const int CardsPerDeck = 52;

		public string Value { get; set; }
		public string Suit { get; set; }

		public Card(string value, string suit)
		{
			this.Value = value;
			this.Suit = suit;
		}
	}

	internal class Day51
	{
		private static int Main(string[] args)
		{
			List<Card> deck = CreateDeck();
			PrintDeck(deck);

			Console.WriteLine();

			ShuffleDeck(deck);
			PrintDeck(deck);

			Console.ReadLine();

			return 0;
		}

		private static List<Card> CreateDeck()
		{
			string[] values = { "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };
			string[] suits = { "S", "H", "C", "D" };

			List<Card> deck = new List<Card>(Card.CardsPerDeck);

			foreach (string suit in suits)
			{
				foreach (string value in values)
				{
					deck.Add(new Card(value, suit));
				}
			}

			return deck;
		}

		private static void ShuffleDeck(List<Card> deck)
		{
			for (int i = 0; i < deck.Count; i++)
			{
				int swapIndex = RandomNumber(Card.CardsPerDeck) - 1;

				Card temp = deck[i];
				deck[i] = deck[swapIndex];
				deck[swapIndex] = temp;
			}
		}

		private static void PrintDeck(List<Card> deck)
		{
			for (int i = 0; i < deck.Count; i++)
			{
				Console.Write($"{deck[i].Value}{deck[i].Suit}");

				if (i < deck.Count - 1)
				{
					Console.Write(", ");
				}
			}

			Console.WriteLine();
		}

		private static int RandomNumber(int k) => new Random().Next(1, k + 1);
	}
}