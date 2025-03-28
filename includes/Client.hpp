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
	
	// METHODS
	void ExecuteCommand(std::string);

	// SETTERS
	void SetSocket(int);

private:
	// ATTRIBUTES
	// specific data
	Server &_server;
	int _socket;
	// temporary data
	std::string _cmd;
	std::vector<std::string> _arguments;
	// user data
	std::string _nick;
	std::string _user;
	std::string _real_name;
	// status
	bool _pass_check;
	bool _nick_check;
	bool _user_check;
	bool _authenticated_check;


	// METHODS
	// login commands
	int Pass();
	int Nick();
	int User();
	// general commands
	int Help();
	int Oper();
	int Ping();
	int Quit();
	// chanel commands
	int Invite();
	int Join();
	int Kick();
	int Mode();
	int Part();
	int Privmsg();
	int Topic();
	// commands description message
	void Pass(std::ostringstream &oss);
	void Nick(std::ostringstream &oss);
	void User(std::ostringstream &oss);
	// message client
	void MessageClient(std::string);
	void MessageClient(int);
	// command candler
	int Parser(std::string);
	int CommandHandler(int);
	void PrintErrorMessage(int nb);
	void PrintSuccessMessage(int nb);
	bool NickAlreadyExist(std::string str);
	bool ValidName(std::string str);
};

#endif
