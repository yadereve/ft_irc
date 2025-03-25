#ifndef SERVER_HPP
#define SERVER_HPP

#include "text_format.h"

class Server
{
public:
	Server();
	Server(const std::string port, const std::string pass);
	Server(const Server& other);
	Server& operator=(const Server& other);
	~Server();
	
	int start();

private:
	std::string _port;
	std::string _pass;
	std::string _host;

};

#endif
