using System;
using System.Collections.Generic;

namespace DailyCodingProblem
{
	internal class FileDirectory
	{
		private Dictionary<string, string> files = new Dictionary<string, string>();
		private readonly string name;

		public FileDirectory(string name)
		{
			this.name = name;
		}

		public bool AddFile(string path, string contents)
		{
			if (files.ContainsKey(path))
			{
				return false;
			}

			files.Add(path, contents);

			return true;
		}

		public bool UpdateFile(string path, string newContents)
		{
			if (!files.ContainsKey(path))
			{
				return false;
			}

			files[path] = newContents;

			return true;
		}

		public void SynchroniseTo(FileDirectory other)
		{
			List<string> filesToRemove = new List<string>();
			List<string> filesToUpdate = new List<string>();

			foreach (var file in files)
			{
				string path = file.Key;
				string contents = file.Value;

				if (!other.files.ContainsKey(path))
				{
					filesToRemove.Add(path);
				}
				else if (other.files[path] != files[path])
				{
					filesToUpdate.Add(path);
				}
			}

			foreach (string path in filesToRemove)
			{
				files.Remove(path);
			}

			foreach (string path in filesToUpdate)
			{
				files[path] = other.files[path];
			}

			foreach (var file in other.files)
			{
				string path = file.Key;
				string contents = file.Value;

				if (!files.ContainsKey(path))
				{
					files.Add(path, contents);
				}
			}
		}

		public void Print()
		{
			Console.WriteLine($"{name}\n");

			foreach (var file in files)
			{
				Console.WriteLine($"{file.Key}\t[{file.Value}]");
			}

			Console.WriteLine();
		}
	}

	internal class Day59
	{
		private static int Main(string[] args)
		{
			FileDirectory dirA = new FileDirectory("Directory A");
			dirA.AddFile("file1.txt", "file1 contents");
			dirA.AddFile("file2.txt", "file2's contents");
			dirA.AddFile("file3.txt", "file3 contents and some other stuff");

			FileDirectory dirB = new FileDirectory("Directory B");
			dirB.AddFile("file2.txt", "file2 contents");
			dirB.AddFile("file3.txt", "file3 contents");
			dirB.AddFile("file4.txt", "file4 contents");

			Console.WriteLine("BEFORE SYNCHRONISATION:");
			dirA.Print();
			dirB.Print();

			dirA.SynchroniseTo(dirB);

			Console.WriteLine("AFTER SYNCHRONISATION:");
			dirA.Print();
			dirB.Print();

			Console.ReadLine();

			return 0;
		}
	}
}