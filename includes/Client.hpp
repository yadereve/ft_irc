#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "format/text_format.h"
#include "format/config_macros.h"

#include "Server.hpp"
#include "Utils.hpp"
#include "Channel.hpp" 

class Server;

class Client
{
public:
	Client(Server &, int);
	~Client();

	// METHODS
	void executeCommand(std::string);
	void resolveHostname();
	std::string getFullMask() const;

	// message client
	void messageClient(std::string);
	void messageClient(int);

	// SETTERS
	//void setSocket(int);

	// GETTERS
	int getSocket();

	// add for channel
	std::string getNickname() const;
	void receiveMessage(const std::string &source, const std::string &command, const std::string &args);
	

private:
	// ATTRIBUTES
	// specific data
	Server &_server;
	int _socket;
	// temporary data
	std::string _cmd;
	std::vector<std::string> _arguments;
	std::string _input;
	// user data
	std::string _nick;
	std::string _user;
	std::string _real_name;
	std::string _hostname;
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
	int ping();
	int quit();
	// chanel commands
	int invite();
	int join();
	int kick();
	int mode();
	int part();
	int privmsg();
	int hexchat();
	int topic();
	int bot();
	// commands description message
	void pass(std::ostringstream &oss);
	void nick(std::ostringstream &oss);
	void user(std::ostringstream &oss);
	void help(std::ostringstream &oss);
	void ping(std::ostringstream &oss);
	void quit(std::ostringstream &oss);
	void join(std::ostringstream &oss);
	void part(std::ostringstream &oss);
	void topic(std::ostringstream &oss);
	void kick(std::ostringstream &oss);
	void mode(std::ostringstream &oss);
	void privmsg(std::ostringstream &oss);
	void invite(std::ostringstream &oss);
	// command handler
	int parser(std::string);
	int commandHandler(int);
	void printMessage(int nb);
	void printMessage(int messageId, const std::string& arg1, const std::string& arg2);
	// command utils
	bool nickAlreadyExist(std::string str);
	bool validName(std::string str);
	bool channelExist(std::string);
	bool nickExist(std::string);
	void sendJoinMessages(const std::string& channel_name, Channel* channel);

};

#endif
