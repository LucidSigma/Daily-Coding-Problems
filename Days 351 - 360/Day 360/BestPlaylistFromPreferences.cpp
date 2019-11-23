#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <queue>
#include <unordered_map>
#include <utility>
#include <vector>

using Song = unsigned int;

inline bool operator <(const std::pair<Song, float>& lhs, const std::pair<Song, float>& rhs)
{
	return lhs.second < rhs.second;
}

std::vector<Song> GetBestPlaylist(const std::vector<std::vector<Song>>& preferences)
{
	std::unordered_map<Song, float> songScores;

	for (const auto& preference : preferences)
	{
		const size_t currentSongCount = preference.size();
		const unsigned int currentTotalScore = ((currentSongCount + 1) * currentSongCount) / 2;

		for (size_t i = 0; i < preference.size(); ++i)
		{
			if (songScores.find(preference[i]) == std::cend(songScores))
			{
				songScores[preference[i]] = 0.0f;
			}

			songScores[preference[i]] += static_cast<float>(currentTotalScore) / static_cast<float>(i + 1);
		}
	}

	std::priority_queue<std::pair<Song, float>> sortedSongs;

	for (const auto songScorePair : songScores)
	{
		sortedSongs.push(songScorePair);
	}

	std::vector<Song> bestPlaylist;
	bestPlaylist.reserve(sortedSongs.size());

	while (!sortedSongs.empty())
	{
		const auto [song, _score] = sortedSongs.top();
		sortedSongs.pop();

		bestPlaylist.push_back(song);
	}

	std::reverse(std::begin(bestPlaylist), std::end(bestPlaylist));

	return bestPlaylist;
}

template <typename T>
std::ostream& operator <<(std::ostream& outputStream, const std::vector<T>& values)
{
	for (const auto value : values)
	{
		outputStream << value << " ";
	}

	return outputStream;
}

int main(const int argc, const char* const argv[])
{
	std::cout << GetBestPlaylist({ { 1, 7, 3 }, { 2, 1, 6, 7, 9 }, { 3, 9, 5 } }) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}