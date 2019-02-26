using System;

namespace DailyCodingProblem
{
	internal class Node
	{
		public int Value { get; set; }
		public bool IsLocked { get; private set; } = false;

		private Node left;
		private Node right;
		private Node parent = null;

		private int descendantLockCount = 0;

		public Node(int value, Node left = null, Node right = null)
		{
			this.Value = value;

			this.left = left;
			this.right = right;

			if (left != null)
			{
				left.parent = this;
			}

			if (right != null)
			{
				right.parent = this;
			}
		}

		public bool Lock()
		{
			if (CanBeLocked())
			{
				IsLocked = true;
				Node currentNode = parent;

				while (currentNode != null)
				{
					currentNode.descendantLockCount++;
					currentNode = currentNode.parent;
				}

				return true;
			}

			return false;
		}

		public bool Unlock()
		{
			if (CanBeLocked())
			{
				IsLocked = false;
				Node currentNode = parent;

				while (currentNode != null)
				{
					currentNode.descendantLockCount--;
					currentNode = currentNode.parent;
				}

				return true;
			}

			return false;
		}

		private bool CanBeLocked()
		{
			if (descendantLockCount > 0)
			{
				return false;
			}

			Node currentNode = parent;

			while (currentNode != null)
			{
				if (currentNode.IsLocked)
				{
					return false;
				}

				currentNode = currentNode.parent;
			}

			return true;
		}
	}

	internal class Day24
	{
		private static int Main(string[] args)
		{
			Node leftLeft = new Node(67);
			Node leftRight = new Node(43);
			Node rightRight = new Node(36);
			Node left = new Node(82, leftLeft, leftRight);
			Node right = new Node(49, null, rightRight);
			Node root = new Node(19, left, right);

			Console.WriteLine(left.Lock());
			Console.WriteLine(leftRight.Lock());

			left.Unlock();

			Console.WriteLine(leftRight.Lock());

			if (leftRight.IsLocked)
			{
				Console.WriteLine("Node leftRight is locked.");
			}

			Console.ReadLine();

			return 0;
		}
	}
}