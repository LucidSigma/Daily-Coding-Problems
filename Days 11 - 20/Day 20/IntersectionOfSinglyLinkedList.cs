using System;

namespace DailyCodingProblem
{
	internal class Node
	{
		public int Value { get; private set; }
		public Node Next { get; private set; }

		public Node(int value, Node next = null)
		{
			this.Value = value;
			this.Next = next;
		}
	}

	internal class Day20
	{
		private static int Main(string[] args)
		{
			// Intersection
			Node node10 = new Node(10);
			Node node8 = new Node(8, node10);

			// List A
			Node node7 = new Node(7, node8);
			Node node3 = new Node(3, node7);

			// List B
			Node node1 = new Node(1, node8);
			Node node99 = new Node(99, node1);

			Console.WriteLine(GetSinglyLinkedListIntersection(node3, node99).Value);

			Console.ReadLine();

			return 0;
		}

		private static Node GetSinglyLinkedListIntersection(Node listA, Node listB)
		{
			Node listACounter = listA;
			Node listBCounter = listB;

			int lengthA = GetSinglyLinkedListLength(ref listACounter);
			int lengthB = GetSinglyLinkedListLength(ref listBCounter);

			if (listACounter != listBCounter)
			{
				return null;
			}

			int difference = Math.Abs(lengthA - lengthB);
			var (shorterList, longerList) = lengthA > lengthB ? (listB, listA) : (listA, listB);

			while (difference > 0)
			{
				longerList = longerList.Next;
				difference--;
			}

			while (longerList != shorterList)
			{
				longerList = longerList.Next;
				shorterList = shorterList.Next;
			}

			return longerList;
		}

		private static int GetSinglyLinkedListLength(ref Node list)
		{
			int count = 0;

			while (list != null)
			{
				list = list.Next;
				count++;
			}

			return count;
		}
	}
}