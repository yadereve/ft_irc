#ifndef BOT_HPP
#define BOT_HPP

#include "format/config_macros.h"
#include "format/text_format.h"
#include <string>
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cerrno>
#include <cstdlib>

#define BUFFER_SIZE 512

class Bot
{
public:
	Bot(const std::string& serverIp, int port, const std::string password, const std::string nickname, const std::string username, const std::string channel);
	~Bot();

	void run();

private:
	int _socketFd;
	std::string _serverIp;
	int _port;
	std::string _password;
	std::string _nickname;
	std::string _username;
	std::string _channel;

	void sendMessage(const std::string& message);
	void registerToServer();
	void handleIncomingMessage();
};

#endif
