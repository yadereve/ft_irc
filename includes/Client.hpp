#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "text_format.h"
#include "config_macros.h"

#include "Server.hpp"

class Server;

class Client
{
public:
	Client(Server &, int);
	~Client();
	
	// methods
	void Parser(std::string);

	// setters
	void SetSocket(int);

private:
	// attributes
	std::string _cmd;
	std::string _message;
	const Server &_server;
	int _socket;

	// methods
	void Pass();
	void Nick();
	void User();
	void PrintMessage(std::string);

};

#endif
