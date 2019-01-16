using System;

namespace DailyCodingProblem
{
	internal class Node
	{
		public int Value { get; private set; }

		public Node Left { get; private set; }
		public Node Right { get; private set; }

		public Node(int value = 0, Node left = null, Node right = null)
		{
			this.Value = value;
			this.Left = left;
			this.Right = right;
		}
	}

	internal class Day8
	{
		private static int Main(string[] args)
		{
			Node grandGrandChildA = new Node(1);
			Node grandGrandChildB = new Node(1);
			Node grandChildA = new Node(1, grandGrandChildA, grandGrandChildB);
			Node grandChildB = new Node(0);
			Node childA = new Node(1);
			Node childB = new Node(0, grandChildA, grandChildB);
			Node root = new Node(0, childA, childB);

			Console.WriteLine(GetUnivalTreeCount(root));

			Console.ReadLine();

			return 0;
		}

		private static int GetUnivalTreeCount(Node root)
		{
			int count = 0;
			IsTreeUnival(root, ref count);

			return count;
		}

		private static bool IsTreeUnival(Node node, ref int counter)
		{
			if (node == null)
			{
				return true;
			}

			bool isLeftUnival = IsTreeUnival(node.Left, ref counter);
			bool isRightUnival = IsTreeUnival(node.Right, ref counter);

			if (!isLeftUnival || !isRightUnival)
			{
				return false;
			}

			if (node.Left != null && node.Value != node.Left.Value)
			{
				return false;
			}

			if (node.Right != null && node.Value != node.Right.Value)
			{
				return false;
			}

			counter++;

			return true;
		}
	}
}