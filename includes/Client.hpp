#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "format/text_format.h"
#include "format/config_macros.h"

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
	int pass();
	int nick();
	int user();
	// general commands
	int help();
	int oper();
	int ping();
	int quit();
	// chanel commands
	int invite();
	int join();
	int kick();
	int mode();
	int part();
	int privmsg();
	int topic();
	// commands description message
	void pass(std::ostringstream &oss);
	void nick(std::ostringstream &oss);
	void user(std::ostringstream &oss);
	void ping(std::ostringstream &oss);
	void quit(std::ostringstream &oss);
	// message client
	void messageClient(std::string);
	void messageClient(int);
	// command handler
	int parser(std::string);
	int commandHandler(int);
	void printErrorMessage(int nb);
	void printSuccessMessage(int nb);
	bool nickAlreadyExist(std::string str);
	bool validName(std::string str);
};

#endif
