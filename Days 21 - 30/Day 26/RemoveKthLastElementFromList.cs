using System;

namespace DailyCodingProblem
{
	internal class Node
	{
		public int Value { get; private set; }
		public Node Next { get; set; }

		public Node(int value, Node next = null)
		{
			this.Value = value;
			this.Next = next;
		}
	}

	internal class Day26
	{
		private static int Main(string[] args)
		{
			Node n1 = new Node(4);
			Node n2 = new Node(8, n1);
			Node n3 = new Node(10, n2);
			Node n4 = new Node(3, n3);
			Node n5 = new Node(9, n4);
			Node n6 = new Node(7, n5);
			Node n7 = new Node(1, n6);
			Node n8 = new Node(2, n7);

			PrintLinkedList(n8);

			RemoveKthLastElementFromList(n8, 3);
			PrintLinkedList(n8);

			Console.ReadLine();

			return 0;
		}

		private static void RemoveKthLastElementFromList(Node head, int k)
		{
			Node front = head;
			Node back = head;

			while (front != null)
			{
				front = front.Next;

				if (k < 0)
				{
					back = back.Next;
				}

				k--;
			}

			if (k == 0)
			{
				head = head.Next;
			}
			else if (back.Next != null)
			{
				back.Next = back.Next.Next;
			}
		}

		private static void PrintLinkedList(Node head)
		{
			while (head != null)
			{
				Console.Write($"{head.Value} ");
				head = head.Next;
			}

			Console.WriteLine();
		}
	}
}