using System;
using System.Collections.Generic;
using System.Text;

namespace DailyCodingProblem
{
	internal class UrlShortener
	{
		private const int CharsPerCode = 6;
		private const string UrlPrefix = "https://www.sho.rt/";

		private static Dictionary<string, string> urlDictionary = new Dictionary<string, string>();

		public static string Shorten(string url)
		{
			string shortenedUrl = ShortenEncoding(CreateMD5Hash(url));
			urlDictionary[shortenedUrl] = url;

			return UrlPrefix + shortenedUrl;
		}

		public static string Restore(string url)
		{
			string hash = url.Substring(UrlPrefix.Length);

			return urlDictionary.ContainsKey(hash) ? urlDictionary[hash] : null;
		}

		private static string ShortenEncoding(string encodedString) => encodedString.Substring(0, CharsPerCode);

		private static string CreateMD5Hash(string text)
		{
			using (System.Security.Cryptography.MD5 md5 = System.Security.Cryptography.MD5.Create())
			{
				byte[] inputBytes = System.Text.Encoding.ASCII.GetBytes(text);
				byte[] hashBytes = md5.ComputeHash(inputBytes);

				StringBuilder hash = new StringBuilder();

				for (int i = 0; i < hashBytes.Length; i++)
				{
					hash.Append(hashBytes[i].ToString("X2"));
				}

				return hash.ToString();
			}
		}
	}

	internal class Day55
	{
		private static int Main(string[] args)
		{
			string shortenedUrl = UrlShortener.Shorten("https://www.google.com.au");
			Console.WriteLine(shortenedUrl);

			string restoredUrl = UrlShortener.Restore(shortenedUrl);
			Console.WriteLine(restoredUrl);

			shortenedUrl = UrlShortener.Shorten("https://www.github.com");
			Console.WriteLine(shortenedUrl);

			restoredUrl = UrlShortener.Restore(shortenedUrl);
			Console.WriteLine(restoredUrl);

			Console.ReadLine();

			return 0;
		}
	}
}