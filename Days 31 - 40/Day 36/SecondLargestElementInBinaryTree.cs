using System;

namespace DailyCodingProblem
{
	internal class Node
	{
		public Node Left { get; set; }
		public Node Right { get; set; }

		public int Value { get; set; }

		public Node(int value, Node left = null, Node right = null)
		{
			this.Value = value;
			this.Left = left;
			this.Right = right;
		}
	}

	internal class BinarySearchTree
	{
		public Node Root { get; private set; } = null;
		public int Count { get; private set; } = 0;

		public BinarySearchTree() { }

		public BinarySearchTree(params int[] values)
		{
			Insert(values);
		}

		public void Insert(params int[] values)
		{
			foreach (int value in values)
			{
				if (Root == null)
				{
					Root = new Node(value);
				}
				else
				{
					InsertHelper(Root, value);
				}

				Count++;
			}
		}

		private Node InsertHelper(Node node, int value)
		{
			if (node == null)
			{
				return new Node(value);
			}

			if (value < node.Value)
			{
				node.Left = InsertHelper(node.Left, value);
			}
			else if (value > node.Value)
			{
				node.Right = InsertHelper(node.Right, value);
			}

			return node;
		}
	}

	internal class Day36
	{
		private static int Main(string[] args)
		{
			BinarySearchTree tree = new BinarySearchTree(50, 30, 20, 40, 70, 60, 80);
			Console.WriteLine($"Second largest element in binary tree: {SecondLargest(tree)}");

			Console.ReadLine();

			return 0;
		}

		private static int SecondLargest(BinarySearchTree binaryTree)
		{
			int counter = 0;
			int secondLargest = int.MinValue;

			if (binaryTree.Root != null && binaryTree.Count >= 2)
			{
				SecondLargestHelper(binaryTree.Root, ref counter, ref secondLargest);
			}
			else
			{
				Console.WriteLine("Error: Binary tree not large enough.");
			}

			return secondLargest;
		}

		private static void SecondLargestHelper(Node node, ref int counter, ref int secondLargest)
		{
			if (node == null || counter >= 2)
			{
				return;
			}

			SecondLargestHelper(node.Right, ref counter, ref secondLargest);
			counter++;

			if (counter == 2)
			{
				secondLargest = node.Value;

				return;
			}

			SecondLargestHelper(node.Left, ref counter, ref secondLargest);
		}
	}
}