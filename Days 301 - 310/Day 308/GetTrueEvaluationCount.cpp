#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <vector>

unsigned int GetTrueEvaluationGroupingsCount(const std::vector<char>& expression)
{
	if (expression.empty())
	{
		return 0;
	}

	std::vector<char> booleans;
	std::vector<char> operators;

	for (const auto symbol : expression)
	{
		(symbol == 'T' || symbol == 'F' ? booleans : operators).push_back(symbol);
	}

	const size_t booleanCount = booleans.size();

	std::vector<std::vector<unsigned int>> trueValues(booleanCount, std::vector<unsigned int>(booleanCount, 0));
	std::vector<std::vector<unsigned int>> falseValues(booleanCount, std::vector<unsigned int>(booleanCount, 0));

	for (size_t i = 0; i < booleanCount; ++i)
	{
		trueValues[i][i] = booleans[i] == 'T' ? 1 : 0;
		falseValues[i][i] = booleans[i] == 'F' ? 1 : 0;
	}

	for (size_t gap = 1; gap < booleanCount; ++gap)
	{
		size_t i = 0;

		for (size_t j = gap; j < booleanCount; ++j)
		{
			trueValues[i][j] = 0;
			falseValues[i][j] = 0;

			for (size_t k = 0; k < gap; ++k)
			{
				const size_t place = i + k;
				const unsigned int firstTotal = trueValues[i][place] + falseValues[i][place];
				const unsigned int secondTotal = trueValues[place + i][j] + falseValues[place + i][j];

				switch (operators[place])
				{
				case '&':
					trueValues[i][j] += trueValues[i][place] * trueValues[place + 1][j];
					falseValues[i][j] += (firstTotal * secondTotal) - (trueValues[i][place] * trueValues[place + 1][j]);

					break;

				case '|':
					falseValues[i][j] += falseValues[i][place] * falseValues[place + 1][j];
					trueValues[i][j] += (firstTotal * secondTotal) - (falseValues[i][place] * falseValues[place + 1][j]);

					break;

				case '^':
					trueValues[i][j] += (falseValues[i][place] * trueValues[place + 1][j]) + (trueValues[i][place] * falseValues[place + 1][j]);
					falseValues[i][j] += (trueValues[i][place] * trueValues[place + 1][j]) + (falseValues[i][place] * falseValues[place + 1][j]);

					break;

				default:
					break;
				}
			}
		}

		++i;
	}

	return trueValues[0][booleanCount - 1];
}

int main(const int argc, const char* const argv[])
{
	std::cout << GetTrueEvaluationGroupingsCount({ 'F', '|', 'T', '&', 'T' }) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}