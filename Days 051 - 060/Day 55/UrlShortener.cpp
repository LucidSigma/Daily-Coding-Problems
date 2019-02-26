#include <iostream>
#include <locale>
#include <unordered_map>
#include <string>

// Base64 encoding modified from https://github.com/ReneNyffenegger/cpp-base64
// I used base64 because it is easy to implement (as C++ does not have many inbuilt hash functions)
// MD5 or SHA2 could be used instead if the language implements them
std::string Base64Encode(const std::string& stringToEncode)
{
	static const std::string Base64Characters =	"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

	std::string encodedString;
	char charArray3[3];
	char charArray4[4];
	int i = 0;

	for (unsigned int c = 0; c < stringToEncode.length(); c++)
	{
		charArray3[i] = stringToEncode[c];
		i++;

		if (i == 3)
		{
			charArray4[0] = (charArray3[0] & 0xFC) >> 2;
			charArray4[1] = ((charArray3[0] & 0x03) << 4) + ((charArray3[1] & 0xF0) >> 4);
			charArray4[2] = ((charArray3[1] & 0x0f) << 2) + ((charArray3[2] & 0xC0) >> 6);
			charArray4[3] = charArray3[2] & 0x3F;

			for (i = 0; i < 4; i++)
			{
				encodedString += Base64Characters[charArray4[i]];
			}

			i = 0;
		}
	}

	int j = 0;

	if (i != 0)
	{
		for (j = i; j < 3; j++)
		{
			charArray3[j] = '\0';
		}

		charArray4[0] = (charArray3[0] & 0xFC) >> 2;
		charArray4[1] = ((charArray3[0] & 0x03) << 4) + ((charArray3[1] & 0xF0) >> 4);
		charArray4[2] = ((charArray3[1] & 0x0F) << 2) + ((charArray3[2] & 0xC0) >> 6);

		for (j = 0; j < i + 1; j++)
		{
			encodedString += Base64Characters[charArray4[j]];
		}

		while (i < 3)
		{
			encodedString += '=';
			i++;
		}

	}

	return encodedString;
}

class UrlShortener
{
private:
	static constexpr unsigned int CHARS_PER_CODE = 6;
	static const std::string UrlPrefix;

	static std::unordered_map<std::string, std::string> urlMap;

public:
	static std::string Shorten(const std::string& url)
	{
		std::string shortenedUrl = ShortenEncoding(Base64Encode(url));
		urlMap[shortenedUrl] = url;

		return UrlPrefix + shortenedUrl;
	}

	static std::string Restore(const std::string& url)
	{
		std::string hash = url.substr(UrlPrefix.length());

		if (urlMap.find(hash) != urlMap.end())
		{
			return urlMap[hash];
		}
		else
		{
			std::cerr << "Hash cannot be restored into a URL.\n";

			return "";
		}
	}

private:
	static std::string ShortenEncoding(const std::string& encodedString)
	{
		std::string returnedString;

		for (auto it = encodedString.crbegin(); it != encodedString.crend(); it += 2)
		{
			if (std::isalnum(*it, std::locale("en_US.UTF-8")))
			{
				returnedString += *it;
			}

			if (returnedString.length() == CHARS_PER_CODE)
			{
				break;
			}
		}

		return returnedString;
	}
};

const std::string UrlShortener::UrlPrefix = "https://www.sho.rt/";
std::unordered_map<std::string, std::string> UrlShortener::urlMap;

int main(int argc, const char* argv[])
{
	std::string shortenedUrl = UrlShortener::Shorten("https://www.google.com.au");
	std::cout << shortenedUrl << "\n";

	std::string restoredUrl = UrlShortener::Restore(shortenedUrl);
	std::cout << restoredUrl << "\n";

	shortenedUrl = UrlShortener::Shorten("https://www.github.com");
	std::cout << shortenedUrl << "\n";

	restoredUrl = UrlShortener::Restore(shortenedUrl);
	std::cout << restoredUrl << "\n";

	std::cin.get();

	return 0;
}