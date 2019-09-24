#include <bitset>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <string>

// Base64 encoding available from https://github.com/ReneNyffenegger/cpp-base64
#ifndef BASE64_H_C0CE2A47_D10E_42C9_A27C_C883944E704A
#define BASE64_H_C0CE2A47_D10E_42C9_A27C_C883944E704A

std::string base64_encode(unsigned char const*, unsigned int len);
std::string base64_decode(std::string const& s);

#endif 

class CheckStructure
{
private:
	unsigned int m_storeKey = 0;

public:
	CheckStructure() = default;
	~CheckStructure() noexcept = default;

	void Add(const std::string& value)
	{
		const unsigned int valueHash = EncodeString(value);
		m_storeKey |= valueHash;
	}

	bool Check(const std::string& value) const
	{
		const unsigned int valueHash = EncodeString(value);
		const auto hashBinary = std::bitset<32>(valueHash);
		const auto keyBinary = std::bitset<32>(m_storeKey);

		for (size_t i = 0; i < 32; ++i)
		{
			if (hashBinary.test(i) && !keyBinary.test(i))
			{
				return false;
			}
		}

		return true;
	}

private:
	inline unsigned int EncodeString(const std::string& value) const
	{
		return std::stoi(base64_encode(reinterpret_cast<unsigned const char*>(value.data()), value.length()));
	}
};

int main(int argc, char* argv[])
{
	CheckStructure checker;
	checker.Add("1");
	checker.Add("2");
	checker.Add("3");

	std::cout << std::boolalpha;
	std::cout << checker.Check("1") << checker.Check("3") << checker.Check("4") << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}