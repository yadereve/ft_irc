#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "text_format.h"
#include "config_macros.h"

#include "Server.hpp"
#include "Utils.hpp"

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
	Server &_server;
	int _socket;
	// 	status
	bool _pass_check;
	bool _nick_check;
	bool _user_check;


	// methods
	// 	commands
	int Pass();
	int Nick();
	int User();
	void Help();
	// 	user
	void MessageUser(std::string);
	void MessageUser(int);
	void CommandHandler(int);
	bool NickAlreadyExist(std::string str);

};

#endif
