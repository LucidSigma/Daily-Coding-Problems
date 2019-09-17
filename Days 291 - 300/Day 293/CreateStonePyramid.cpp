#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <vector>

std::vector<unsigned int> CreatePyramidHelper(const size_t length)
{
	const size_t summit = (length / 2) + 1;
	std::vector<unsigned int> ascent;

	for (size_t i = 1; i < summit; ++i)
	{
		ascent.push_back(i);
	}

	std::vector<unsigned int> descent = ascent;
	std::reverse(std::begin(descent), std::end(descent));

	std::vector<unsigned int> pyramid;
	pyramid.insert(std::cend(pyramid), std::cbegin(ascent), std::cend(ascent));
	pyramid.push_back(summit);
	pyramid.insert(std::cend(pyramid), std::cbegin(descent), std::cend(descent));

	return pyramid;
}

std::vector<unsigned int> CreatePyramid(const std::vector<unsigned int>& stones)
{
	size_t pyramidLength = stones.size() % 2 != 0 ? stones.size() : stones.size() - 1;
	
	while (pyramidLength > 0)
	{
		const auto currentPyramid = CreatePyramidHelper(pyramidLength);

		for (const auto offset : std::array<size_t, 2>{ 0, stones.size() - pyramidLength })
		{
			bool isValidPyramid = true;

			for (size_t i = 0; i < currentPyramid.size(); ++i)
			{
				const size_t currentIndex = i + offset;

				if (currentPyramid[i] > stones[currentIndex])
				{
					isValidPyramid = false;

					break;
				}
			}

			if (isValidPyramid)
			{
				std::vector<unsigned int> pyramid(offset, 0);
				pyramid.insert(std::cend(pyramid), std::cbegin(currentPyramid), std::cend(currentPyramid));

				std::vector<unsigned int> tail(stones.size() - offset - pyramidLength, 0);
				pyramid.insert(std::cend(pyramid), std::cbegin(tail), std::cend(tail));

				return pyramid;
			}
		}

		pyramidLength -= 2;
	}

	return { };
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
	std::cout << CreatePyramid({ 1, 1, 3, 3, 2, 1 }) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}