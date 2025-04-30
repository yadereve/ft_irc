#include "../../includes/Bot.hpp"
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

Bot::Bot(const std::string& serverIp, int port, const std::string password, const std::string nickname, const std::string username, const std::string channel) : _serverIp(serverIp), _port(port), _password(password), _nickname(nickname), _username(username), _channel(channel)
{ }

Bot::~Bot()
{
	if (_socketFd > 0)
		close(_socketFd);
}

static std::string getTime()
{
	time_t timestamp;
	time(&timestamp);
	std::string currentTime = asctime(localtime(&timestamp));
	currentTime.erase(currentTime.end()-1); // remove '\n'
	return currentTime;
}

void Bot::sendMessage(const std::string& message)
{
	send(_socketFd, message.c_str(), message.size(), 0);
}

void Bot::registerToServer()
{
	sendMessage("PASS " + _password + "\r\n");
	sendMessage("NICK " + _nickname + "\r\n");
	sendMessage("USER " + _username + " * * : " + _username + "\r\n");
	sendMessage("JOIN " + _channel + "\r\n");
}

void Bot::handleIncomingMessage()
{
	char buffer[BUFFER_SIZE];
	while (true)
	{
		std::memset(buffer, 0, sizeof(buffer));
		int bytesRead = recv(_socketFd, buffer, sizeof(buffer) - 1, 0);
		if (bytesRead <= 0)
		{
			std::cout << "Disconnected from server." << std::endl;
			break;
		}
		std::string message(buffer);
		std::cout << "Received: " << message << std::endl;

		if (message.find("help") != std::string::npos)
		{
			sendMessage("PRIVMSG " + _channel + " :Available commands: help, time, joke, echo\r\n");
		}
		if (message.find("time") != std::string::npos)
		{
			sendMessage("PRIVMSG " + _channel + " :Current time: " + getTime() + "\r\n");
		}

		if (message.find("joke") != std::string::npos)
		{
			sendMessage("PRIVMSG " + _channel + " :Why do programmers prefer dark mode? Because light attracts bugs!\r\n");
		}

		if (message.find("echo") != std::string::npos)
		{
			sendMessage(message + "\r\n");
		}
	}
}

void Bot::run()
{
	_socketFd = socket(AF_INET, SOCK_STREAM, 0);
	if (_socketFd == -1)
	{
		std::cerr << "Failed to create socket." << std::endl;
		return;
	}
	
	struct sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(_port);
	inet_pton(AF_INET, _serverIp.c_str(), &serverAddr.sin_addr);

	if (connect(_socketFd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0)
	{
		std::cerr << "Failed to connect to server" << std::endl;
		close(_socketFd);
		return;
	}
	registerToServer();
	handleIncomingMessage();
}

