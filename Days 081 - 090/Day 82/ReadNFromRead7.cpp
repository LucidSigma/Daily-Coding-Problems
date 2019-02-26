#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

class FileReader
{
private:
	mutable unsigned int offset = 0;
	const std::string contents;

	std::string nBuffer = "";

public:
	explicit FileReader(const std::string& filename)
		: contents(GetFileContents(filename))
	{ }

	std::string Read7() const noexcept
	{
		if (offset >= contents.length())
		{
			return "";
		}

		std::string sevenLetterString = contents.substr(offset, 7);
		offset += 7;

		return sevenLetterString;
	}

	std::string ReadN(unsigned int n) noexcept
	{
		while (nBuffer.length() < n)
		{
			std::string sevenLengthString = Read7();

			if (sevenLengthString.empty())
			{
				break;
			}

			nBuffer += sevenLengthString;
		}

		std::string nLengthString = nBuffer.substr(0, n);

		if (nBuffer.length() >= n)
		{
			nBuffer = nBuffer.substr(n);
		}
		else
		{
			nBuffer = nBuffer.substr(nBuffer.length());
		}

		return nLengthString;
	}

private:
	std::string GetFileContents(const std::string& filename) const
	{
		std::ifstream file(filename);

		if (!file.is_open())
		{
			throw std::invalid_argument("File " + filename + " could not be found/opened.");
		}

		std::ostringstream fileReader;
		fileReader << file.rdbuf();

		file.close();

		return fileReader.str();
	}
};

int main(int argc, char* argv[])
{
	FileReader readerA("input.txt");
	std::cout << readerA.Read7() << "\n";
	std::cout << readerA.Read7() << "\n";
	std::cout << readerA.Read7() << "\n";

	FileReader readerB("input.txt");
	std::cout << readerB.ReadN(8) << "\n";
	std::cout << readerB.ReadN(8) << "\n";
	std::cout << readerB.ReadN(8) << "\n";

	FileReader readerC("input.txt");
	std::cout << readerC.ReadN(2) << "\n";
	std::cout << readerC.ReadN(2) << "\n";
	std::cout << readerC.ReadN(2) << "\n";

	std::cin.get();

	return 0;
}