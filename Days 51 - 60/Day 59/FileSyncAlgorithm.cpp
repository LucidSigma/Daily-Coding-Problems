#include <iostream>
#include <map>
#include <string>
#include <vector>

class FileDirectory
{
private:
	std::map<std::string, std::string> files;
	std::string name;

public:
	explicit FileDirectory(const std::string& name)
		: name(name)
	{ }

	bool AddFile(const std::string& path, const std::string& contents)
	{
		if (files.find(path) != files.end())
		{
			return false;
		}

		files.insert(std::make_pair(path, contents));

		return true;
	}
	
	bool UpdateFile(const std::string& path, const std::string& newContents)
	{
		if (files.find(path) == files.end())
		{
			return false;
		}

		files[path] = newContents;

		return true;
	}

	void SynchroniseTo(FileDirectory other)
	{
		std::vector<std::string> filesToRemove;

		for (auto[path, contents] : files)
		{
			if (other.files.find(path) == other.files.end())
			{
				filesToRemove.push_back(path);
			}
			else if (other.files[path] != files[path])
			{
				files[path] = other.files[path];
			}
		}

		for (const std::string& path : filesToRemove)
		{
			files.erase(path);
		}

		for (auto[path, contents] : other.files)
		{
			if (files.find(path) == files.end())
			{
				files.insert(std::make_pair(path, contents));
			}
		}
	}

	void Print() const
	{
		std::cout << name << "\n\n";

		for (const auto[path, contents] : files)
		{
			std::cout << path << "\t[" << contents << "]\n";
		}

		std::cout << "\n";
	}
};

int main(int argc, char* argv[])
{
	FileDirectory dirA("Directory A");
	dirA.AddFile("file1.txt", "file1 contents");
	dirA.AddFile("file2.txt", "file2's contents");
	dirA.AddFile("file3.txt", "file3 contents and some other stuff");

	FileDirectory dirB("Directory B");
	dirB.AddFile("file2.txt", "file2 contents");
	dirB.AddFile("file3.txt", "file3 contents");
	dirB.AddFile("file4.txt", "file4 contents");

	std::cout << "BEFORE SYNCHRONISATION:\n";
	dirA.Print();
	dirB.Print();

	dirA.SynchroniseTo(dirB);

	std::cout << "AFTER SYNCHRONISATION:\n";
	dirA.Print();
	dirB.Print();

	std::cin.get();

	return 0;
}