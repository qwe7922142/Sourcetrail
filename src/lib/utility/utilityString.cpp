#include "utility/utilityString.h"

#include <algorithm>
#include <cctype>
#include <iterator>
#include <string>

namespace utility
{
	std::deque<std::string> split(const std::string& str, char delimiter)
	{
		return split<std::deque<std::string>>(str, std::string(1, delimiter));
	}

	std::deque<std::string> split(const std::string& str, const std::string& delimiter)
	{
		return split<std::deque<std::string>>(str, delimiter);
	}

	std::vector<std::string> splitToVector(const std::string& str, char delimiter)
	{
		return split<std::vector<std::string>>(str, std::string(1, delimiter));
	}

	std::vector<std::string> splitToVector(const std::string& str, const std::string& delimiter)
	{
		return split<std::vector<std::string>>(str, delimiter);
	}

	std::string join(const std::deque<std::string>& list, char delimiter)
	{
		return join<std::deque<std::string> >(list, std::string(1, delimiter));
	}

	std::string join(const std::deque<std::string>& list, const std::string& delimiter)
	{
		return join<std::deque<std::string> >(list, delimiter);
	}

	std::string join(const std::vector<std::string>& list, char delimiter)
	{
		return join<std::vector<std::string> >(list, std::string(1, delimiter));
	}

	std::string join(const std::vector<std::string>& list, const std::string& delimiter)
	{
		return join<std::vector<std::string> >(list, delimiter);
	}

	std::deque<std::string> tokenize(const std::string& str, char delimiter)
	{
		return tokenize(str, std::string(1, delimiter));
	}

	std::deque<std::string> tokenize(const std::string& str, const std::string& delimiter)
	{
		size_t pos = 0;
		size_t oldPos = 0;
		std::deque<std::string> c;

		do
		{
			pos = str.find(delimiter, oldPos);

			if (pos != oldPos)
			{
				c.push_back(str.substr(oldPos, pos - oldPos));
			}

			if (pos != std::string::npos)
			{
				c.push_back(str.substr(pos, delimiter.size()));
			}

			oldPos = pos + delimiter.size();
		}
		while (pos != std::string::npos && oldPos < str.size());

		return c;
	}

	std::deque<std::string> tokenize(const std::deque<std::string>& list, char delimiter)
	{
		return tokenize(list, std::string(1, delimiter));
	}

	std::deque<std::string> tokenize(const std::deque<std::string>& list, const std::string& delimiter)
	{
		std::deque<std::string> c;

		for (std::string str : list)
		{
			if (str.size())
			{
				std::deque<std::string> c2 = tokenize(str, delimiter);
				c.insert(c.end(), c2.begin(), c2.end());
			}
		}

		return c;
	}

	std::string substrBefore(const std::string& str, char delimiter)
	{
		size_t pos = str.find(delimiter);
		if (pos != std::string::npos)
		{
			return str.substr(0, pos);
		}
		return str;
	}

	std::string substrAfter(const std::string& str, char delimiter)
	{
		size_t pos = str.find(delimiter);
		if (pos != std::string::npos)
		{
			return str.substr(pos + 1, str.size());
		}
		return str;
	}

	bool isPrefix(const std::string& prefix, const std::string& text)
	{
		typedef std::pair<std::string::const_iterator, std::string::const_iterator> ResType;
		ResType res = std::mismatch(prefix.begin(), prefix.end(), text.begin());

		return res.first == prefix.end();
	}

	std::string toUpperCase(const std::string& in)
	{
		std::string out;
		std::transform(in.begin(), in.end(), std::back_inserter(out), toupper);
		return out;
	}

	std::string toLowerCase(const std::string& in)
	{
		std::string out;
		std::transform(in.begin(), in.end(), std::back_inserter(out), tolower);
		return out;
	}

	bool equalsCaseInsensitive(const std::string& a, const std::string& b)
	{
		if (a.size() == b.size())
		{
			for (size_t i = 0; i < a.size(); i++)
			{
				if (tolower(a[i]) != tolower(b[i]))
				{
					return false;
				}
			}
			return true;
		}
		return false;
	}

	std::string replace(std::string str, const std::string& from, const std::string& to)
	{
		size_t pos = 0;

		if (from.size() == 0)
		{
			return str;
		}

		while ((pos = str.find(from, pos)) != std::string::npos)
		{
			str.replace(pos, from.length(), to);
			pos += to.length();
		}

		return str;
	}

	std::string trim(const std::string &str)
	{
		auto wsfront = std::find_if_not(str.begin(), str.end(), [](int c){ return std::isspace(c); });
		auto wsback = std::find_if_not(str.rbegin(), str.rend(), [](int c){ return std::isspace(c); }).base();
		return (wsback <= wsfront ? std::string() : std::string(wsfront, wsback));
	}
}
