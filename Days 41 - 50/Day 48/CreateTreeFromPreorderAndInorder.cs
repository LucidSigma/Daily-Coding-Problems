using System;
using System.Collections.Generic;

namespace DailyCodingProblem
{
	internal class Node
	{
		public string Value { get; private set; }

		public Node Left { get; set; } = null;
		public Node Right { get; set; } = null;

		public Node(string value)
		{
			this.Value = value;
		}
	}

	internal class Day48
	{
		private static int Main(string[] args)
		{
			List<string> preorder = new List<string>() { "a", "b", "d", "e", "c", "f", "g" };
			List<string> inorder = new List<string>() { "d", "b", "e", "a", "f", "c", "g" };
			Node tree = CreateTree(preorder, inorder);

			Console.WriteLine(tree.Left.Right.Value);

			Console.ReadLine();

			return 0;
		}

		private static Node CreateTree(List<string> preorder, List<string> inorder)
		{
			if (preorder.Count == 0 || inorder.Count == 0)
			{
				return null;
			}

			Node rootNode = new Node(preorder[0]);

			if (preorder.Count == 1)
			{
				return rootNode;
			}

			for (int i = 0; i < inorder.Count; i++)
			{
				if (inorder[i] == rootNode.Value)
				{
					List<string> shorteningPreorder = preorder.GetRange(1, i);
					List<string> shorteningInorder = inorder.GetRange(0, i + 1);

					rootNode.Left = CreateTree(shorteningPreorder, shorteningInorder);

					shorteningPreorder = preorder.GetRange(i + 1, preorder.Count - i - 1);
					shorteningInorder = inorder.GetRange(i + 1, preorder.Count - i - 1);

					rootNode.Right = CreateTree(shorteningPreorder, shorteningInorder);
				}
			}

			return rootNode;
		}
	}
}