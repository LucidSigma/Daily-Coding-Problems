using System;
using System.Collections.Generic;
using System.Linq;

namespace DailyCodingProblem
{
	internal class LFUCache
	{
		private class Node
		{
			public string Key { get; set; }
			public string Value { get; set; }

			public Node Next { get; set; }
			public Node Previous { get; set; }

			public Node(string key, string value)
			{
				this.Key = key;
				this.Value = value;
			}
		}

		private class LinkedList
		{
			public  Node Head { get; private set; } = null;
			private Node tail = null;

			public int Size { get; private set; } = 0;

			public void	Add(Node node)
			{
				if (Head == null)
				{
					Head = node;
				}
				else
				{
					tail.Next = node;
					node.Previous = tail;
				}

				tail = node;
				Size++;
			}

			public void Remove(Node node)
			{
				if (node.Next == null)
				{
					tail = node.Previous;
				}
				else
				{
					node.Next.Previous = node.Previous;
				}

				if (Head.Key == node.Key)
				{
					Head = node.Next;
				}
				else
				{
					node.Previous.Next = node.Next;
				}

				Size++;
			}
		}

		private Dictionary<string, Node> values = new Dictionary<string, Node>();
		private Dictionary<string, int> counts = new Dictionary<string, int>();
		private SortedDictionary<int, LinkedList> frequencies = new SortedDictionary<int, LinkedList>();

		private readonly int limit;

		public LFUCache(int limit)
		{
			this.limit = limit;
		}

		public string Get(string key)
		{
			if (!values.ContainsKey(key))
			{
				throw new ArgumentOutOfRangeException("Key not in cache.");
			}

			Node node = values[key];
			int frequency = counts[key];
			frequencies[frequency].Remove(node);
			RemoveEmptyList(frequency);

			if (!frequencies.ContainsKey(frequency + 1))
			{
				frequencies.Add(frequency + 1, new LinkedList());
				frequencies[frequency + 1].Add(node);
			}

			counts[key] = frequency + 1;

			return values[key].Value;
		}

		public void Set(string key, string value)
		{
			if (!values.ContainsKey(key))
			{
				Node node = new Node(key, value);

				if (value.Length == limit)
				{
					int minCount = frequencies.First().Key;
					Node nodeToDelete = frequencies[minCount].Head;
					frequencies[minCount].Remove(nodeToDelete);

					string keyToDelete = nodeToDelete.Key;
					RemoveEmptyList(minCount);

					values.Remove(keyToDelete);
					counts.Remove(keyToDelete);
				}

				values[key] = node;
				counts[key] = 1;

				if (!frequencies.ContainsKey(1))
				{
					frequencies.Add(1, new LinkedList());
					frequencies[1].Add(node);
				}
			}
		}

		private void RemoveEmptyList(int frequency)
		{
			if (frequencies[frequency].Size == 0)
			{
				frequencies.Remove(frequency);
			}
		}
	}

	internal class Day67
	{
		private static int Main(string[] args)
		{
			LFUCache cache = new LFUCache(5);
			cache.Set("1", "1");
			cache.Set("2", "2");
			cache.Set("3", "3");
			cache.Set("4", "4");
			cache.Set("5", "5");

			cache.Set("2", "2");
			cache.Set("3", "3");
			cache.Set("4", "4");
			cache.Set("5", "5");

			cache.Set("3", "3");
			cache.Set("4", "4");
			cache.Set("5", "5");

			cache.Set("4", "4");
			cache.Set("5", "5");

			cache.Set("5", "5");

			cache.Set("6", "6");

			try
			{
				Console.WriteLine(cache.Get("1"));
			}
			catch (ArgumentOutOfRangeException)
	{
				Console.WriteLine("1 has been removed from the cache.");
			}

			Console.ReadLine();

			return 0;
		}
	}
}