#include <array>
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using Candidate = unsigned int;
using Voter = unsigned int;

inline bool operator >(const std::pair<Candidate, unsigned int>& lhs, const std::pair<Candidate, unsigned int>& rhs) noexcept
{
	return lhs.second > rhs.second;
}

std::array<Candidate, 3> ProcessVotes()
{
	std::ifstream voteFile("input.txt");
	Voter currentVoter;
	Candidate currentCandidate;

	std::unordered_set<Voter> voterList;
	std::unordered_map<Candidate, unsigned int> votes;

	while (voteFile >> currentVoter >> currentCandidate)
	{
		if (voterList.find(currentVoter) != std::cend(voterList))
		{
			std::cout << currentVoter << " has committed voter fraud.\n";

			continue;
		}

		voterList.insert(currentVoter);

		if (votes.find(currentCandidate) == std::cend(votes))
		{
			votes[currentCandidate] = 0;
		}

		++votes[currentCandidate];
	}

	std::priority_queue<std::pair<Candidate, unsigned int>, std::vector<std::pair<Candidate, unsigned int>>, std::greater<std::pair<Candidate, unsigned int>>> sortedVotes;

	for (const auto votePair : votes)
	{
		sortedVotes.push(votePair);
	}

	std::array<Candidate, 3> topThreeCandidates;

	for (size_t i = 0; i < 3; ++i)
	{
		topThreeCandidates[i] = sortedVotes.top().first;
		sortedVotes.pop();
	}

	return topThreeCandidates;
}

template <typename T, size_t Size>
std::ostream& operator <<(std::ostream& outputStream, const std::array<T, Size>& array)
{
	for (const auto& value : array)
	{
		outputStream << value << " ";
	}

	return outputStream;
}

int main(int argc, char* argv[])
{
	std::cout << ProcessVotes() << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}