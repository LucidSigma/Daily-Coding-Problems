#include <iostream>
#include <limits>
#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>

struct Node
{
	std::string key;
	int value;

	std::shared_ptr<Node> previous;
	std::shared_ptr<Node> next;

	explicit Node(const std::string& key, int value, std::shared_ptr<Node> previous = nullptr, std::shared_ptr<Node> next = nullptr)
		: key(key), value(value), previous(previous), next(next)
	{ }
};

class LRUCache
{
private:
	std::unordered_map<std::string, std::shared_ptr<Node>> cache;

	unsigned int limit;
	unsigned int size;

	std::shared_ptr<Node> leastRecentlyUsed;
	std::shared_ptr<Node> mostRecentlyUsed;

public:
	explicit LRUCache(unsigned int limit)
		: limit(limit), size(0), leastRecentlyUsed(new Node("", std::numeric_limits<int>::min())), mostRecentlyUsed(leastRecentlyUsed)
	{ }

	int Get(const std::string& key)
	{
		if (cache.find(key) == cache.end())
		{
			throw std::runtime_error("Invalid key.");
		}

		std::shared_ptr<Node> node = cache[key];

		if (node->key == mostRecentlyUsed->key)
		{
			return mostRecentlyUsed->value;
		}

		std::shared_ptr<Node> nextNode = node->next;
		std::shared_ptr<Node> previousNode = node->previous;

		if (node->key == leastRecentlyUsed->key)
		{
			nextNode->previous = nullptr;
			leastRecentlyUsed = nextNode;
		}
		else if (node->key != mostRecentlyUsed->key)
		{
			previousNode->next = nextNode;
			nextNode->previous = previousNode;
		}

		node->previous = mostRecentlyUsed;
		mostRecentlyUsed->next = node;
		mostRecentlyUsed = node;
		mostRecentlyUsed->next = nullptr;

		return node->value;
	}

	void Set(const std::string& key, int value)
	{
		if (cache.find(key) != cache.end())
		{
			return;
		}

		std::shared_ptr<Node> node = std::make_shared<Node>(key, value, mostRecentlyUsed);
		mostRecentlyUsed->next = node;

		cache[key] = node;
		mostRecentlyUsed = node;

		if (size >= limit)
		{
			cache.erase(leastRecentlyUsed->key);

			leastRecentlyUsed = leastRecentlyUsed->next;
			leastRecentlyUsed->previous = nullptr;
		}
		else if (size < limit)
		{
			if (size == 0)
			{
				leastRecentlyUsed = node;
			}

			size++;
		}
	}
};

int main(int argc, const char* argv[])
{
	LRUCache lru(3);

	lru.Set("1", 1);
	lru.Set("2", 2);
	lru.Set("3", 3);
	std::cout << lru.Get("1") << "\n";

	lru.Set("4", 4);

	try
	{
		std::cout << lru.Get("2") << "\n";
	}
	catch (const std::runtime_error&)
	{
		std::cout << "2 is not in cache.\n";
	}

	std::cin.get();

	return 0;
}