#include <iostream>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>

class LFUCache
{
private:
	struct Node
	{
	public:
		std::string key;
		std::string value;

		std::shared_ptr<Node> next;
		std::shared_ptr<Node> previous;

	public:
		Node(const std::string& key, const std::string& value)
			: key(key), value(value)
		{ }
	};

	class LinkedList
	{
	private:
		std::shared_ptr<Node> head = nullptr;
		std::shared_ptr<Node> tail = nullptr;

		unsigned int size = 0;

	public:
		void Add(std::shared_ptr<Node> node)
		{
			if (head == nullptr)
			{
				head = node;
			}
			else
			{
				tail->next = node;
				node->previous = tail;
			}

			tail = node;
			size++;
		}

		void Remove(std::shared_ptr<Node> node)
		{

			if (node->next == nullptr)
			{
				tail = node->previous;
			}
			else
			{
				node->next->previous = node->previous;
			}

			if (head->key == node->key)
			{
				head = node->next;
			}
			else
			{
				node->previous->next = node->next;
			}

			size--;
		}

		inline std::shared_ptr<Node> GetHead() { return head; }
		inline unsigned int GetSize() { return size; }
	};

	std::unordered_map<std::string, std::shared_ptr<Node>> values;
	std::unordered_map<std::string, unsigned int> counts;
	std::map<unsigned int, LinkedList> frequencies;

	const int limit;

public:
	explicit LFUCache(int limit)
		: limit(limit)
	{ }

	std::string Get(const std::string& key)
	{
		if (values.find(key) == values.end())
		{
			throw std::out_of_range("Key not in cache.");
		}

		std::shared_ptr<Node> node = values[key];

		int frequency = counts[key];
		frequencies[frequency].Remove(node);
		RemoveEmptyList(frequency);

		if (frequencies.find(frequency + 1) == frequencies.end())
		{
			frequencies[frequency + 1].Add(node);
		}

		counts[key] = frequency + 1;

		return values[key]->value;
	}

	void Set(std::string key, std::string value)
	{
		if (values.find(key) == values.end())
		{
			std::shared_ptr<Node> node = std::make_shared<Node>(key, value);

			if (values.size() == limit)
			{
				unsigned int minCount = (*frequencies.begin()).first;
				std::shared_ptr<Node> nodeTodelete = frequencies[minCount].GetHead();
				frequencies[minCount].Remove(nodeTodelete);

				std::string keyToDelete = nodeTodelete->key;
				RemoveEmptyList(minCount);

				values.erase(keyToDelete);
				counts.erase(keyToDelete);
			}

			values[key] = node;
			counts[key] = 1;

			if (frequencies.find(1) == frequencies.end())
			{
				frequencies[1].Add(node);
			}
		}
	}

private:
	void RemoveEmptyList(unsigned int frequency)
	{
		if (frequencies[frequency].GetSize() == 0)
		{
			frequencies.erase(frequency);
		}
	}
};

int main(int argc, char* argv[])
{
	LFUCache cache(5);
	cache.Set("1", "1");
	cache.Set("2", "2");
	cache.Set("3", "3");
	cache.Set("4", "4");
	cache.Set("5", "5");

	cache.Set("2", "2");
	cache.Set("3", "3");
	cache.Set("4", "4");
	cache.Set("5", "5");

	cache.Set("3", "3");
	cache.Set("4", "4");
	cache.Set("5", "5");

	cache.Set("4", "4");
	cache.Set("5", "5");

	cache.Set("5", "5");

	cache.Set("6", "6");

	try
	{
		std::cout << cache.Get("1") << "\n";
	}
	catch (const std::out_of_range&)
	{
		std::cout << "1 has been removed from the cache.\n";
	}

	std::cin.get();

	return 0;
}