using System;

namespace DailyCodingProblem
{
	internal class Node
	{
		public string Value { get; private set; }

		public Node Left { get; private set; }
		public Node Right { get; private set; }

		public Node(string value, Node left = null, Node right = null)
		{
			this.Value = value;
			this.Left = left;
			this.Right = right;
		}
	}

	internal class Day50
	{
		private static int Main(string[] args)
		{
			Node leftLeft = new Node("3");
			Node leftRight = new Node("2");
			Node rightLeft = new Node("4");
			Node rightRight = new Node("5");
			Node left = new Node("+", leftLeft, leftRight);
			Node right = new Node("+", rightLeft, rightRight);
			Node root = new Node("*", left, right);

			Console.WriteLine(SolveTreeExpression(root));

			Console.ReadLine();

			return 0;
		}

		private static int SolveTreeExpression(Node node)
		{
			if (int.TryParse(node.Value, out int num))
			{
				return num;
			}
			else
			{
				switch (node.Value[0])
				{
					case '+':
						return SolveTreeExpression(node.Left) + SolveTreeExpression(node.Right);

					case '-':
						return SolveTreeExpression(node.Left) - SolveTreeExpression(node.Right);

					case '*':
						return SolveTreeExpression(node.Left) * SolveTreeExpression(node.Right);

					case '/':
						return SolveTreeExpression(node.Left) / SolveTreeExpression(node.Right);

					default:
						throw new InvalidOperationException("Invalid operator in tree.");
				}
			}
		}
	}
}