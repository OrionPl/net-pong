#pragma once

#include <iostream>
#include <string>

class Helper {
public:
	static bool StringStartsWith(std::string str, std::string startsWith);
	std::string ShortenStringFromLeft(std::string str, int length);
	std::string GetStringUntil(std::string str, std::string until);
};

