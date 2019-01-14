#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::vector<std::string> SplitString(const std::string& text, char delimiter = ' ')
{
	std::string currentToken;
	std::stringstream reader(text);

	std::vector<std::string> tokens;

	while (std::getline(reader, currentToken, delimiter))
	{
		tokens.push_back(currentToken);
	}

	return tokens;
}

unsigned int LengthofLongestPath(const std::string& fileString)
{
	std::vector<std::string> directories = SplitString(fileString, '\n');
	std::vector<unsigned int> lengths(directories.size() + 1, 0);
	unsigned int maxLength = 0;

	for (const std::string& directory : directories)
	{
		int currentLevel = static_cast<int>(directory.find_last_of('\t')) + 1;

		unsigned int currentLength = lengths[currentLevel] + directory.length() - currentLevel + 1;
		lengths[currentLevel + 1] = currentLength;

		if (directory.find('.') != std::string::npos)
		{
			maxLength = std::max(maxLength, currentLength - 1);
		}
	}

	return maxLength;
}

int main(int argc, char* argv[])
{
	std::cout << LengthofLongestPath("") << "\n";
	std::cout << LengthofLongestPath("dir\n\tfile.ext") << "\n";
	std::cout << LengthofLongestPath("dir\n\tsubdir1\n\tsubdir2\n\t\tfile.ext") << "\n";
	std::cout << LengthofLongestPath("dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext") << "\n";

	std::cin.get();

	return 0;
}
