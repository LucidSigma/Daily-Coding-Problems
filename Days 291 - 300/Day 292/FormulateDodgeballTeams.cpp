#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <optional>
#include <unordered_map>
#include <unordered_set>
#include <utility>

class Team
{
private:
	std::unordered_set<unsigned int> m_members;
	std::unordered_set<unsigned int> m_enemies;

public:
	Team() = default;

	void AddStudent(const unsigned int student, const std::unordered_set<unsigned int>& enemies)
	{
		m_members.insert(student);

		for (const auto enemy : enemies)
		{
			if (m_enemies.find(enemy) == std::cend(m_enemies))
			{
				m_enemies.erase(enemy);
			}
			else
			{
				m_enemies.insert(enemy);
			}
		}
	}

	inline bool IsEmpty() const
	{
		return m_members.empty();
	}

	inline bool IsEnemy(const unsigned int student) const
	{
		return m_enemies.find(student) != std::cend(m_enemies);
	}

	inline size_t MemberCount() const
	{
		return m_members.size();
	}

	inline operator std::unordered_set<unsigned int>()
	{
		return m_members;
	}
};

std::optional<std::pair<std::unordered_set<unsigned int>, std::unordered_set<unsigned int>>> GetDodgeballTeams(const std::unordered_map<unsigned int, std::unordered_set<unsigned int>>& enemyList)
{
	std::unordered_set<unsigned int> students;

	for (const auto& [student, _] : enemyList)
	{
		students.insert(student);
	}

	Team firstTeam;
	Team secondTeam;

	for (const auto student : students)
	{
		if (firstTeam.IsEmpty() || !firstTeam.IsEnemy(student))
		{
			firstTeam.AddStudent(student, enemyList.at(student));
		}
		else if (secondTeam.IsEmpty() || !secondTeam.IsEnemy(student))
		{
			secondTeam.AddStudent(student, enemyList.at(student));
		}
	}

	if (firstTeam.MemberCount() + secondTeam.MemberCount() == students.size())
	{
		return std::make_pair(firstTeam, secondTeam);
	}
	else
	{
		return { };
	}
}

template <typename T>
std::ostream& operator <<(std::ostream& outputStream, const std::unordered_set<T>& unorderedSet)
{
	for (const auto& item : unorderedSet)
	{
		outputStream << item << " ";
	}

	return outputStream;
}

template <typename T, typename U>
inline std::ostream& operator <<(std::ostream& outputStream, const std::pair<T, U>& pair)
{
	outputStream << pair.first << "\n" << pair.second;
	
	return outputStream;
}

int main(int argc, char* argv[])
{
	const std::unordered_map<unsigned int, std::unordered_set<unsigned int>> firstEnemyList
	{
		{ 0, { 3 } },
		{ 1, { 2 } },
		{ 2, { 1, 4 } }, 
		{ 3, { 0, 4, 5 } },
		{ 4, { 2, 3 } },
		{ 5, { 3 } }
	};

	std::cout << GetDodgeballTeams(firstEnemyList).value() << "\n";

	const std::unordered_map<unsigned int, std::unordered_set<unsigned int>> secondEnemyList
	{
		{ 0, { 3 } },
		{ 1, { 2 } },
		{ 2, { 1, 3, 4 } },
		{ 3, { 0, 2, 4, 5 } },
		{ 4, { 2, 3 } },
		{ 5, { 3 } }
	};

	std::cout << GetDodgeballTeams(secondEnemyList).value_or(std::make_pair<std::unordered_set<unsigned int>, std::unordered_set<unsigned int>>({ }, { })) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}