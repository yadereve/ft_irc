#ifndef UTILS_HPP
#define UTILS_HPP

#include "format/text_format.h"
#include "format/config_macros.h"

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
