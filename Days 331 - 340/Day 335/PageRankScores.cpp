#include <cstdlib>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <unordered_map>
#include <unordered_set>
#include <utility>

class Graph
{
public:
	using Node = char;

private:
	std::unordered_map<Node, std::unordered_set<Node>> m_edges;

public:
	Graph() = default;
	~Graph() noexcept = default;

	Graph(const std::initializer_list<std::pair<Node, Node>>& edges)
	{
		for (const auto [source, destination] : edges)
		{
			AddEdge(source, destination);
		}
	}

	void AddEdge(const Node source, const Node destination)
	{
		if (m_edges.find(source) == std::cend(m_edges))
		{
			m_edges[source] = { };
		}

		if (m_edges.find(destination) == std::cend(m_edges))
		{
			m_edges[destination] = { };
		}

		m_edges[source].insert(destination);
	}

	inline const decltype(m_edges)& GetEdges() const { return m_edges; }
};

float CalculateSiteScore(const Graph::Node node, const Graph& siteLinks, const std::unordered_map<Graph::Node, float>& siteScores)
{
	float aggregateScore = 0.0f;
	
	for (const auto& [site, edges] : siteLinks.GetEdges())
	{
		for (const auto otherSite : edges)
		{
			aggregateScore += siteScores.at(site) / static_cast<float>(edges.size());
		}
	}

	static constexpr float DampingFactor = 0.85f;

	return ((1.0f - DampingFactor) / static_cast<float>(siteLinks.GetEdges().size())) + (DampingFactor * aggregateScore);
}

std::unordered_map<Graph::Node, float> GetSiteScores(const Graph& siteLinks)
{
	std::unordered_map<Graph::Node, float> siteScores;
	float startingProbability = 1.0f / static_cast<float>(siteLinks.GetEdges().size());

	for (const auto& [site, _] : siteLinks.GetEdges())
	{
		siteScores[site] = startingProbability;
	}

	for (const auto& [site, _] : siteLinks.GetEdges())
	{
		siteScores[site] = CalculateSiteScore(site, siteLinks, siteScores);
	}

	return siteScores;
}

template <typename T, typename U>
std::ostream& operator <<(std::ostream& outputStream, const std::unordered_map<T, U>& unorderedMap)
{
	for (const auto& [key, value] : unorderedMap)
	{
		outputStream << key << ": " << value << "\n";
	}

	return outputStream;
}

int main(const int argc, const char* const argv[])
{
	const Graph siteLinks(
		{
			{ 'A', 'B' },
			{ 'A', 'C' },
			{ 'A', 'D' },
			{ 'B', 'C' },
			{ 'B', 'D' },
			{ 'C', 'D' },
			{ 'C', 'E' },
			{ 'D', 'E' }
		}
	);

	std::cout << GetSiteScores(siteLinks) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}