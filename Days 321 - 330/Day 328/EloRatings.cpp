#include <cstdlib>
#include <iostream>
#include <iterator>
#include <string>
#include <unordered_map>

class EloRating
{
private:
	static constexpr int s_StartRating = 1000;

	std::unordered_map<std::string, int> m_ratings;

public:
	enum class Result
	{
		Win, Loss, Draw
	};

	EloRating() = default;
	~EloRating() noexcept = default;

	void AddPlayer(const std::string& name)
	{
		m_ratings[name] = s_StartRating;
	}

	void AddResult(const std::string& player, const std::string& opponent, const Result result)
	{
		static constexpr int DifferenceWeighting = 10;
		
		if (result == Result::Draw)
		{
			if (m_ratings[player] == m_ratings[opponent])
			{
				return;
			}

			const int pointDifference = (m_ratings[player] > m_ratings[opponent] ? m_ratings[player] : -m_ratings[opponent]) / (DifferenceWeighting * 2);

			m_ratings[player] -= pointDifference;
			m_ratings[opponent] += pointDifference;
		}
		else
		{
			const std::string& losingPlayer = result == Result::Win ? player : opponent;
			const std::string& winningPlayer = result != Result::Win ? player : opponent;
			const int pointDifference = m_ratings[losingPlayer] / DifferenceWeighting;

			m_ratings[losingPlayer] -= pointDifference;
			m_ratings[winningPlayer] += pointDifference;
		}
	}

	inline std::unordered_map<std::string, int>::iterator begin() { return std::begin(m_ratings); }
	inline std::unordered_map<std::string, int>::iterator end() { return std::end(m_ratings); }
	inline std::unordered_map<std::string, int>::const_iterator cbegin() const { return std::cbegin(m_ratings); }
	inline std::unordered_map<std::string, int>::const_iterator cend() const { return std::cend(m_ratings); }
};

int main(const int argc, const char* const argv[])
{
	EloRating ratings;

	ratings.AddPlayer("A");
	ratings.AddPlayer("B");
	ratings.AddPlayer("C");
	ratings.AddPlayer("D");

	ratings.AddResult("A", "B", EloRating::Result::Win);
	ratings.AddResult("C", "D", EloRating::Result::Loss);
	ratings.AddResult("D", "B", EloRating::Result::Win);
	ratings.AddResult("C", "A", EloRating::Result::Draw);

	for (const auto& [player, rating] : ratings)
	{
		std::cout << player << ": " << rating << "\n";
	}

	std::cin.get();

	return EXIT_SUCCESS;
}