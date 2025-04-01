#ifndef UTILS_HPP
#define UTILS_HPP

#include "text_format.h"
#include "config_macros.h"

class Utils
{
public:
	// methods
	static std::vector<std::string> split(const std::string &, char);
	static void printVector(std::vector<std::string> vec);
	static bool compareStringsCaseInsensitive(std::string, std::string);

private:
	Utils();
	~Utils();
};

#endif
