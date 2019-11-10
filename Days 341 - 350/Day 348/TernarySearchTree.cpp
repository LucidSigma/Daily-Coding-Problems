#include <cstdlib>
#include <iostream>
#include <memory>
#include <optional>
#include <string>
#include <vector>

class TernarySearchTree
{
private:
	std::optional<char> m_value;

	std::shared_ptr<TernarySearchTree> m_left;
	std::shared_ptr<TernarySearchTree> m_middle;
	std::shared_ptr<TernarySearchTree> m_right;

public:
	inline static std::shared_ptr<TernarySearchTree> AddTree(const nullptr_t, const std::string& word)
	{
		const auto location = std::make_shared<TernarySearchTree>();
		
		return location->AddWord(word), location;
	}

	inline static std::shared_ptr<TernarySearchTree> AddTree(const std::shared_ptr<TernarySearchTree>& location, const std::string& word)
	{
		return location->AddWord(word), location;
	}

	inline explicit TernarySearchTree(const std::optional<char> value = std::nullopt, const std::shared_ptr<TernarySearchTree>& left = nullptr, const std::shared_ptr<TernarySearchTree>& middle = nullptr, const std::shared_ptr<TernarySearchTree>& right = nullptr)
		: m_value(value), m_left(left), m_middle(middle), m_right(right)
	{ }

	void AddWord(const std::string& word)
	{
		if (word.empty())
		{
			return;
		}

		const char firstCharacter = word.front();
		const std::string remainingWord = word.substr(1);

		if (!m_value.has_value())
		{
			m_value = firstCharacter;
			m_middle = AddTree(m_middle, remainingWord);
		}
		else if (m_value == firstCharacter)
		{
			m_middle = AddTree(m_middle, remainingWord);
		}
		else if (m_value < firstCharacter)
		{
			m_left = AddTree(m_left, word);
		}
		else
		{
			m_right = AddTree(m_right, word);
		}
	}

	bool HasWord(const std::string& word) const
	{
		const char firstCharacter = word.front();
		const std::string remainingWord = word.substr(1);

		if (firstCharacter == m_value)
		{
			if (!remainingWord.empty() && !m_value.has_value())
			{
				return true;
			}

			return m_middle->HasWord(remainingWord);
		}
		else if (firstCharacter < m_value)
		{
			if (m_left == nullptr)
			{
				return false;
			}

			return m_left->HasWord(remainingWord);
		}
		else
		{
			if (m_right == nullptr)
			{
				return false;
			}

			return m_right->HasWord(remainingWord);
		}
	}

	inline std::optional<char> GetValue() const noexcept { return m_value; }
	inline const std::shared_ptr<TernarySearchTree>& GetLeft() const noexcept { return m_left; }
	inline const std::shared_ptr<TernarySearchTree>& GetMiddle() const noexcept { return m_middle; }
	inline const std::shared_ptr<TernarySearchTree>& GetRight() const noexcept { return m_right; }
};

int main(const int argc, const char* const argv[])
{
	const std::vector<std::string> words
	{
		"code", "cob", "be", "ax", "war", "we"
	};

	const auto ternarySearchTree = std::make_shared<TernarySearchTree>();

	for (const auto& word : words)
	{
		ternarySearchTree->AddWord(word);
	}

	std::cout << std::boolalpha;
	std::cout << ternarySearchTree->HasWord("code") << "\n";
	std::cout << ternarySearchTree->HasWord("ax") << "\n";
	std::cout << ternarySearchTree->HasWord("war") << "\n";
	std::cout << ternarySearchTree->HasWord("apple") << "\n";
	std::cout << ternarySearchTree->HasWord("axe") << "\n";
	std::cout << ternarySearchTree->HasWord("fort") << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}