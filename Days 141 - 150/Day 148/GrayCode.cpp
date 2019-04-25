#include <iostream>
#include <iterator>
#include <string>
#include <vector>

std::vector<std::string> GetGrayCode(const unsigned int n) noexcept
{
	if (n == 0)
	{
		return { "" };
	}

	std::vector<std::string> lesserGrayCode = GetGrayCode(n - 1);
	std::vector<std::string> leadingZero;
	std::vector<std::string> leadingOne;

	for (unsigned int i = 0; i < lesserGrayCode.size(); i++)
	{
		leadingZero.push_back('0' + lesserGrayCode[i]);
		leadingOne.push_back('1' + lesserGrayCode[lesserGrayCode.size() - i - 1]);
	}

	std::vector<std::string> allGrayCodes = leadingZero;
	allGrayCodes.insert(std::cend(allGrayCodes), std::cbegin(leadingOne), std::cend(leadingOne));

	return allGrayCodes;
}

template <typename T>
void PrintVector(const std::vector<T>& values) noexcept
{
	for (const auto& value : values)
	{
		std::cout << value << " ";
	}

	std::cout << "\n";
}

int main(int argc, char* argv[])
{
	PrintVector(GetGrayCode(1));
	PrintVector(GetGrayCode(2));
	PrintVector(GetGrayCode(3));
	PrintVector(GetGrayCode(4));

	std::cin.get();

	return 0;
}