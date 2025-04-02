#ifndef UTILS_HPP
#define UTILS_HPP

#include "text_format.h"
#include "config_macros.h"

class Utils
{
public:
	// methods
	static std::vector<std::string> Split(const std::string &, char);
	static void PrintVector(std::vector<std::string> vec);

private:
	Utils();
	~Utils();

};

int parseInput(const char* port, std::string pass);

#endif
