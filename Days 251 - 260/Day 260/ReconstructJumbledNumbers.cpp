#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <vector>

enum class PredecessorRelation
	: char
{
	None = '\0',
	Smaller = '-',
	Larger = '+'
};

std::vector<unsigned int> ReconstructJumbledArray(const std::vector<PredecessorRelation>& relations)
{
	const unsigned int largerCount = std::count_if(std::cbegin(relations), std::cend(relations), [](const PredecessorRelation value)
									 	 {
									 	 	 return value == PredecessorRelation::Larger;
									 	 }
									 );

	const unsigned int firstNumber = relations.size() - largerCount - 1;
	std::vector<unsigned int> jumbledNumbers{ firstNumber };

	unsigned int smallerNumber = firstNumber - 1;
	unsigned int largerNumber = firstNumber + 1;

	for (auto it = std::cbegin(relations) + 1; it != std::cend(relations); ++it)
	{
		if (const auto relation = *it;
			relation == PredecessorRelation::Larger)
		{
			jumbledNumbers.push_back(largerNumber);
			++largerNumber;
		}
		else
		{
			jumbledNumbers.push_back(smallerNumber);
			--smallerNumber;
		}
	}

	return jumbledNumbers;
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
	const auto jumbledNumbers = ReconstructJumbledArray(
		{
			 PredecessorRelation::None,
			 PredecessorRelation::Larger,
			 PredecessorRelation::Larger,
			 PredecessorRelation::Smaller,
			 PredecessorRelation::Larger
		}
	);

	std::cout << jumbledNumbers << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}