#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

float GetSimilarityScore(const std::unordered_set<unsigned int>& firstWebsiteUsers, const std::unordered_set<unsigned int>& secondWebsiteUsers)
{
	std::unordered_set<unsigned int> usersUnion = firstWebsiteUsers;
	std::unordered_set<unsigned int> usersIntersect = firstWebsiteUsers;

	for (const auto secondUsers : secondWebsiteUsers)
	{
		if (usersUnion.find(secondUsers) == std::cend(usersUnion))
		{
			usersUnion.insert(secondUsers);
		}
		
		if (usersIntersect.find(secondUsers) != std::cend(usersIntersect))
		{
			usersUnion.erase(secondUsers);
		}
	}

	return static_cast<float>(usersIntersect.size()) / static_cast<float>(usersUnion.size());
}

std::vector<std::pair<char, char>> GetMostSimilarWebsites(const std::vector<std::pair<char, unsigned int>>& similarityScores, const unsigned int k)
{
	std::unordered_map<char, std::unordered_set<unsigned int>> websiteUsers;
	std::vector<char> websiteList;

	for (const auto [website, users] : similarityScores)
	{
		if (websiteUsers.find(website) == std::cend(websiteUsers))
		{
			websiteUsers[website] = { };
			websiteList.push_back(website);
		}

		websiteUsers[website].insert(users);
	}

	std::priority_queue<std::pair<float, std::pair<char, char>>> mostSimilarWebsitesQueue;

	for (size_t i = 0; i < websiteList.size() - 1; ++i)
	{
		for (size_t j = i + 1; j < websiteList.size(); ++j)
		{
			const char firstWebsite = websiteList[i];
			const char secondWebsite = websiteList[j];
			const float similarityScore = -GetSimilarityScore(websiteUsers[firstWebsite], websiteUsers[secondWebsite]);

			mostSimilarWebsitesQueue.push({ similarityScore, { firstWebsite, secondWebsite } });
		}
	}

	std::vector<std::pair<char, char>> mostSimilarWebsites;

	while (!mostSimilarWebsitesQueue.empty())
	{
		const auto [_, websitePair] = mostSimilarWebsitesQueue.top();
		mostSimilarWebsitesQueue.pop();

		mostSimilarWebsites.push_back(websitePair);
	}

	return std::vector<std::pair<char, char>>(std::cbegin(mostSimilarWebsites), std::cbegin(mostSimilarWebsites) + k);
}

template <typename T, typename U>
inline std::ostream& operator <<(std::ostream& outputStream, const std::pair<T, U>& pair)
{
	outputStream << "( " << pair.first << ", " << pair.second << " )";

	return outputStream;
}

template <typename T>
std::ostream& operator <<(std::ostream& outputStream, const std::vector<T>& values)
{
	for (const auto& value : values)
	{
		outputStream << value << "\n";
	}

	return outputStream;
}

int main(int argc, char* argv[])
{
	const std::vector<std::pair<char, unsigned int>> websiteUsers
	{
		{ 'a', 1 }, { 'a', 3 }, { 'a', 5 },
		{ 'b', 2 }, { 'b', 6 },
		{ 'c', 1 }, { 'c', 2 }, { 'c', 3 }, { 'c', 4 }, { 'c', 5 },
		{ 'd', 4 }, { 'd', 5 }, { 'd', 6 }, { 'd', 7 },
		{ 'e', 1 }, { 'e', 3 }, { 'e', 5 }, { 'e', 6 }
	};

	std::cout << GetMostSimilarWebsites(websiteUsers, 1) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}