using System;

namespace DailyCodingProblem
{
	internal class Node
	{
		public string Value { get; set; }
		public Node Next { get; set; }

		public Node(string value, Node next = null)
		{
			this.Value = value;
			this.Next = next;
		}
	}

	internal class Day73
	{
		private static int Main(string[] args)
		{
			Node n1 = new Node("1");
			Node n2 = new Node("2", n1);
			Node n3 = new Node("3", n2);
			Node n4 = new Node("4", n3);
			Node n5 = new Node("5", n4);
			Node n6 = new Node("6", n5);
			Node n7 = new Node("7", n6);
			Node n8 = new Node("8", n7);

			Console.WriteLine("Printing from tail:");
			PrintLinkedList(n1);

			Console.WriteLine("\nPrinting from head:");
			PrintLinkedList(n8);

			Console.WriteLine("\nREVERSING LIST...\n");
			ReverseLinkedList(n8);

			Console.WriteLine("Printing from old tail:");
			PrintLinkedList(n1);

			Console.WriteLine("\nPrinting from old head:");
			PrintLinkedList(n8);

			Console.ReadLine();

			return 0;
		}

		private static void ReverseLinkedList(Node head) => ReverseLinkedListHelper(head, null);

		private static Node ReverseLinkedListHelper(Node head, Node next)
		{
			if (head == null)
			{
				return next;
			}

			Node previous = head.Next;
			head.Next = next;

			return ReverseLinkedListHelper(previous, head);
		}

		private static void PrintLinkedList(Node head)
		{
			while (head != null)
			{
				Console.WriteLine(head.Value);
				head = head.Next;
			}
		}
	}
}