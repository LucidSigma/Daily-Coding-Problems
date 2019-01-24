using System;
using System.Collections.Generic;

namespace DailyCodingProblem
{
	internal class Node
	{
		public string Key { get; set; }
		public int Value { get; set; }

		public Node Previous { get; set; }
		public Node Next { get; set; }

		public Node(string key, int value, Node previous = null, Node next = null)
		{
			this.Key = key;
			this.Value = value;
			this.Previous = previous;
			this.Next = next;
		}
	}

	internal class LRUCache
	{
		private Dictionary<string, Node> cache = new Dictionary<string, Node>();

		private int limit;
		private int size;

		private Node leastRecentlyUsed;
		private Node mostRecentlyUsed;

		public LRUCache(int limit)
		{
			this.limit = limit;
			size = 0;

			leastRecentlyUsed = new Node("", int.MinValue);
			mostRecentlyUsed = leastRecentlyUsed;
		}

		public int Get(string key)
		{
			if (!cache.ContainsKey(key))
			{
				throw new ArgumentOutOfRangeException("Invalid key.");
			}

			Node node = cache[key];

			if (node.Key == mostRecentlyUsed.Key)
			{
				return mostRecentlyUsed.Value;
			}

			Node nextNode = node.Next;
			Node previousNode = node.Previous;

			if (node.Key == leastRecentlyUsed.Key)
			{
				nextNode.Previous = null;
				leastRecentlyUsed = nextNode;
			}
			else if (node.Key != mostRecentlyUsed.Key)
			{
				previousNode.Next = nextNode;
				nextNode.Previous = previousNode;
			}

			node.Previous = mostRecentlyUsed;
			mostRecentlyUsed.Next = node;
			mostRecentlyUsed = node;
			mostRecentlyUsed.Next = null;

			return node.Value;
		}

		public void Set(string key, int value)
		{
			if (cache.ContainsKey(key))
			{
				return;
			}

			Node node = new Node(key, value, mostRecentlyUsed);
			mostRecentlyUsed.Next = node;

			cache.Add(key, node);
			mostRecentlyUsed = node;

			if (size >= limit)
			{
				cache.Remove(leastRecentlyUsed.Key);

				leastRecentlyUsed = leastRecentlyUsed.Next;
				leastRecentlyUsed.Previous = null;
			}
			else if (size < limit)
			{
				if (size == 0)
				{
					leastRecentlyUsed = node;
				}

				size++;
			}
		}
	}

	internal class Day52
	{
		private static int Main(string[] args)
		{
			LRUCache lru = new LRUCache(3);

			lru.Set("1", 1);
			lru.Set("2", 2);
			lru.Set("3", 3);
			Console.WriteLine(lru.Get("1"));

			lru.Set("4", 4);

			try
			{
				Console.WriteLine(lru.Get("2"));
			}
			catch (ArgumentOutOfRangeException)
			{
				Console.WriteLine("2 is not in cache.");
			}

			Console.ReadLine();

			return 0;
		}
	}
}