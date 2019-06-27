#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

bool StartsWith(const std::string& string, const std::string& prefix, const std::size_t offset = 0) noexcept
{
	if (string.length() < prefix.length())
	{
		return false;
	}

	for (std::size_t i = 0; i < prefix.length(); ++i)
	{
		if (i + offset >= string.length() || string[i + offset] != prefix[i])
		{
			return false;
		}
	}

	return true;
}

std::vector<std::size_t> GetAllStartingIndices(const std::string& string, const std::string& substring) noexcept
{
	std::vector<std::size_t> startingIndices;

	for (std::size_t i = 0; i < string.length() - substring.length(); ++i)
	{
		if (StartsWith(string, substring, i))
		{
			startingIndices.push_back(i);
		}
	}

	return startingIndices;
}

template <typename T>
std::ostream& operator <<(std::ostream& outputStream, const std::vector<T>& values) noexcept
{
	for (const auto& value : values)
	{
		outputStream << value << " ";
	}

	return outputStream;
}

int main(int argc, char* argv[])
{
	std::cout << GetAllStartingIndices("abracadabra", "abr") << "\n";

	std::cin.get();

	return 0;
}