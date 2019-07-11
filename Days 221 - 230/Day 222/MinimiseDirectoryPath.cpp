#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

std::vector<std::string> SplitString(const std::string& text, const char delimiter = ' ')
{
	std::string currentToken;
	std::istringstream reader(text);

	std::vector<std::string> tokens;

	while (std::getline(reader, currentToken, delimiter))
	{
		tokens.push_back(currentToken);
	}

	return tokens;
}

std::string MinimisePath(const std::string& path) noexcept
{
	static constexpr char DirectorySeparator = '/';
	std::stack<std::string> directoryStack;
	const std::vector<std::string> directories = SplitString(path, DirectorySeparator);

	for (const auto& directory : directories)
	{
		static const std::string currentDirectory = ".";
		static const std::string previousDirectory = "..";

		if (directory == previousDirectory && !directoryStack.empty())
		{
			directoryStack.pop();
		}
		else if (directory != currentDirectory && !directory.empty())
		{
			directoryStack.push(directory);
		}
	}

	std::string minimisedDirectory(1, DirectorySeparator);
	
	while (!directoryStack.empty())
	{
		minimisedDirectory = DirectorySeparator + directoryStack.top() + minimisedDirectory;
		directoryStack.pop();
	}

	return minimisedDirectory;
}

int main(int argc, char* argv[])
{
	std::cout << MinimisePath("/usr/bin/../bin/./scripts/../") << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}
