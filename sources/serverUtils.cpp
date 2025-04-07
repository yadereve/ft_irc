#include "../includes/Utils.hpp"

int parseInput(const std::string& portStr, const std::string& pass)
{
	//Password checking
	if (pass.empty() || pass.find(' ') != std::string::npos)
		throw std::invalid_argument("Error: empty password");
	
	//Port cheking
	int port;
	std::stringstream portStream(portStr);
	if (!(portStream >> port) || !portStream.eof())
		throw std::invalid_argument("Error: invalid port");
	if (port < MIN_ALLOWED_PORT || port > MAX_ALLOWED_PORT)
		throw std::invalid_argument("Error: Port must be a number from 1024 to 65535");
	return 0;
}
