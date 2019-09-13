#include <cstdlib>
#include <iostream>
#include <iterator>
#include <unordered_set>
#include <utility>
#include <vector>

const std::unordered_set<char> g_quxColours{ 'R', 'G', 'B' };

char GetThirdColour(const std::pair<char, char>& colourPair)
{
	auto colours = g_quxColours;
	colours.erase(colourPair.first);
	colours.erase(colourPair.second);

	return *std::cbegin(colours);
}

std::vector<char> MinimiseQuxColours(const std::vector<char>& quxes)
{
	std::vector<char> quxStack;

	for (const auto qux : quxes)
	{
		if (quxStack.empty() || quxStack.back() == qux)
		{
			quxStack.push_back(qux);

			continue;
		}

		const char newQux = GetThirdColour({ qux, quxStack.back() });
		quxStack.pop_back();
		quxStack.push_back(newQux);

		while (quxStack.size() > 1 && quxStack.back() != quxStack[quxStack.size() - 2])
		{
			const char endQux = quxStack.back();
			quxStack.pop_back();

			const char penultimateQux = quxStack.back();
			quxStack.pop_back();

			quxStack.push_back(GetThirdColour({ endQux, penultimateQux }));
		}
	}

	return quxStack;
}

template <typename T>
std::ostream& operator <<(std::ostream& outputStream, const std::vector<T>& values)
{
	for (const auto& value : values)
	{
		outputStream << value << " ";
	}

	return outputStream;
}

int main(int argc, char* argv[])
{
	std::cout << MinimiseQuxColours({ 'R', 'G', 'B', 'G', 'B' }) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}