using System;
using System.Diagnostics;

namespace DailyCodingProblems
{
	internal class Node
	{
		private const string NullNode = "-";

		public string Value { get; private set; }

		public Node Left { get; private set; }
		public Node Right { get; private set; }

		public Node(string value, Node left = null, Node right = null)
		{
			this.Value = value;
			this.Left = left;
			this.Right = right;
		}

		public string Serialise()
		{
			return SerialiseHelper(this);
		}

		private string SerialiseHelper(Node node)
		{
			if (node == null)
			{
				return NullNode + " ";
			}

			string serialisedTree = node.Value + " ";
			serialisedTree += SerialiseHelper(node.Left);
			serialisedTree += SerialiseHelper(node.Right);

			return serialisedTree;
		}

		public static Node Deserialise(string tree)
		{
			return DeserialiseHelper(tree);
		}

		private static Node DeserialiseHelper(string tree)
		{
			string value = tree.Substring(0, tree.IndexOf(' '));
			string subtree = tree.Substring(tree.IndexOf(' ') + 1);

			if (value == NullNode)
			{
				return null;
			}

			Node node = new Node(value);
			node.Left = DeserialiseHelper(subtree);
			node.Right = DeserialiseHelper(subtree);

			return node;
		}
	}

	internal class Day3
	{
		private static int Main(string[] args)
		{
			Node leftLeft = new Node("left.left");
			Node leftRight = new Node("left.right");
			Node right = new Node("right");
			Node left = new Node("left", leftLeft, leftRight);
			Node node = new Node("root", left, right);

			string decodedNode = Node.Deserialise(node.Serialise()).Left.Left.Value;

			Debug.Assert(decodedNode == "left.left");

			Console.ReadLine();

			return 0;
		}
	}
}