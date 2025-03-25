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
	std::vector<std::string> _message;
	const Server &_server;
	int _socket;
	// 	status
	bool _pass_check;
	bool _nick_check;
	bool _user_check;


	// methods
	// 	commands
	void Pass();
	void Nick();
	void User();
	void Help();
	void PrintMessage(std::string);

};

#endif
