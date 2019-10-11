#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <memory>
#include <numeric>
#include <optional>
#include <unordered_map>
#include <vector>

using Song = unsigned int;

template <typename T>
class LRUCache
{
private:
	struct Node
	{
		std::optional<T> value;

		std::shared_ptr<Node> next;
		std::shared_ptr<Node> previous;

		explicit Node(const std::optional<T>& value = std::nullopt, const std::shared_ptr<Node>& next = nullptr, const std::shared_ptr<Node>& previous = nullptr)
			: value(value), next(next), previous(previous)
		{ }
	};

	const size_t m_size;

	std::shared_ptr<Node> m_head{ };
	std::shared_ptr<Node> m_tail{ };

	std::unordered_map<T, std::shared_ptr<Node>> m_recentNodes;

public:
	explicit LRUCache(const size_t size)
		: m_size(size)
	{
		m_head->next = m_tail;
		m_tail->previous = m_head;
	}

	void UpdateWith(const T& value)
	{
		std::shared_ptr<Node> selectedNode = nullptr;

		if (m_recentNodes.find(value) != std::cend(m_recentNodes))
		{
			selectedNode = m_recentNodes[value];
			selectedNode->previous = selectedNode->next;
		}
		else if (m_recentNodes.size() == m_size)
		{
			selectedNode = std::make_shared<Node>(value);
			
			m_recentNodes.erase(m_head->next->value.value());
			m_head->next = m_head->next->next;
		}
		else
		{
			selectedNode = std::make_shared<Node>(value);
		}

		const auto beforeTail = m_tail->previous;
		beforeTail->next = selectedNode;
		selectedNode->next = m_tail;
		selectedNode->previous = beforeTail;
		m_tail->previous = selectedNode;
		
		m_recentNodes[value] = selectedNode;
	}

	inline bool Contains(const T& value) const
	{
		return m_recentNodes.find(value) != std::cend(m_recentNodes);
	}
};

unsigned int GetAllPlaylistsHelper(const std::vector<Song>& songs, LRUCache<Song> songBufferCache, const unsigned int remainingSongsNeeded)
{
	if (remainingSongsNeeded == 0)
	{
		return 1;
	}

	unsigned int totalPlaylists = 0;

	for (const auto song : songs)
	{
		if (songBufferCache.Contains(song))
		{
			continue;
		}

		songBufferCache.UpdateWith(song);

		totalPlaylists += GetAllPlaylistsHelper(songs, songBufferCache, remainingSongsNeeded - 1);
	}

	return totalPlaylists;
}

unsigned int GetAllPlaylists(const unsigned int songsNeeded, const unsigned int currentSongs, const size_t bufferSize)
{
	std::vector<Song> songs(songsNeeded);
	std::iota(std::begin(songs), std::end(songs), 0);

	LRUCache<Song> songBufferCache(bufferSize);

	return GetAllPlaylistsHelper(songs, songBufferCache, songsNeeded);
}

int main(const int argc, const char* const argv[])
{
	std::cout << GetAllPlaylists(10, 6, 3) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}