#include "Helper.h"

bool Helper::StringStartsWith(std::string str, std::string startsWith)
{
	if (str.length() < startsWith.length())
	{
		return false;
	}

	for (int i = 0; i < startsWith.length(); i++)
	{
		if (str[i] != startsWith[i])
		{
			return false;
		}
	}

	return true;
}

std::string Helper::ShortenStringFromLeft(std::string str, int length)
{
	if (length > str.length())
	{
		return str;
	}

	str.erase(str.begin(), str.begin() + length);

	str.shrink_to_fit();

	return str;
}

std::string Helper::GetStringUntil(std::string str, std::string until)
{
	std::string ret = "";

	std::string next = "";

	try
	{
		for (int i = 0; i < str.length(); i++)
		{
			next = "";

			for (int a = 0; a < until.length(); a++)
			{
				next += str[i];
			}

			if (next == until)
			{
				return ret;
			}

			ret += str[i];
		}
	}
	catch (std::string obj)
	{
		return str;
	}
}