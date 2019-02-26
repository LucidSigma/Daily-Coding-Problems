#include <iostream>
#include <string>
#include <vector>

unsigned int GetDecodings(const std::string& code)
{
	std::vector<unsigned int> results(code.length() + 1);
	results[0] = 1;
	results[1] = 1;

	for (unsigned int i = 2; i < results.size(); i++)
	{
		results[i] = 0;

		if (code[i - 1] > '0')
		{
			results[i] = results[i - 1];
		}

		if ((code[i - 2] == '1') || ((code[i - 2] == '2' && code[i - 1] < '7')))
		{
			results[i] += results[i - 2];
		}
	}

	return results[results.size() - 1];
}

int main(int argc, char* argv[])
{
	std::cout << GetDecodings("111") << "\n";
	std::cout << GetDecodings("1112") << "\n";
	std::cout << GetDecodings("1220487311121120348981012121") << "\n";

	std::cin.get();

	return 0;
}
