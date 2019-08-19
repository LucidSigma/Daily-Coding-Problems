#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <string>
#include <unordered_set>
#include <vector>

template <typename T>
std::vector<T> UnorderedSetToVector(const std::unordered_set<T>& unorderedSet)
{
	std::vector<T> vector;

	for (const auto& value : unorderedSet)
	{
		vector.push_back(value);
	}

	return vector;
}

void CreateDeBruijnSequenceHelper(const std::vector<char>& characters, size_t& currentLength, const std::string& currentNode, std::unordered_set<std::string>& seenSubstrings, std::vector<size_t>& nodeEdges)
{
	for (size_t i = 0; i < currentLength; ++i)
	{
		const std::string currentSubstring = currentNode + characters[i];

		if (seenSubstrings.find(currentSubstring) == std::cend(seenSubstrings))
		{
			seenSubstrings.insert(currentSubstring);
			CreateDeBruijnSequenceHelper(characters, currentLength, currentSubstring.substr(1), seenSubstrings, nodeEdges);
			nodeEdges.push_back(i);
		}
	}
}

std::string CreateDeBruijnSequence(const std::unordered_set<char>& characters, const unsigned int substringLength)
{
	std::unordered_set<std::string> seenSubstrings;
	std::vector<size_t> nodeEdges;
	const std::vector<char> characterVector = UnorderedSetToVector(characters);
	size_t stringLength = characterVector.size();
	const std::string startingNode(substringLength - 1, characterVector.front());

	CreateDeBruijnSequenceHelper(characterVector, stringLength, startingNode, seenSubstrings, nodeEdges);

	std::string deBruijnSequence;
	const size_t edgeCount = static_cast<size_t>(std::pow(characterVector.size(), substringLength));

	for (size_t i = 0; i < edgeCount; ++i)
	{
		deBruijnSequence += characterVector[nodeEdges[i]];
	}

	deBruijnSequence += startingNode;

	return deBruijnSequence;
}

int main(int argc, char* argv[])
{
	std::cout << CreateDeBruijnSequence({ '0', '1' }, 3) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}