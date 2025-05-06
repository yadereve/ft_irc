#include "../../includes/Bot.hpp"
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cerrno>

Bot::Bot(const std::string& serverIp, int port, const std::string password,
		const std::string nickname, const std::string username,
		const std::string channel) :
		_serverIp(serverIp), _port(port), _password(password),
		_nickname(nickname), _username(username), _channel(channel)
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
	if (send(_socketFd, message.c_str(), message.length(), 0) == -1)
	{
		std::cerr << "Error send(): " << strerror(errno) << std::endl;
		return;
	}
}

static std::string extractAfterColon(std::string& str)
{
	size_t pos = str.find(":");
	if (pos != std::string::npos && pos + 1 < str.size())
		return str.substr(pos + 1);
	return "";
}

void Bot::registerToServer()
{
	sendMessage("PASS " + _password + "\r\n");
	sendMessage("NICK " + _nickname + "\r\n");
	sendMessage("USER " + _username + " * * :" + _username + "_" + "\r\n");
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
		std::cout << message;

		if (message.find(":help") != std::string::npos)
			sendMessage("PRIVMSG " + _channel + " :Available commands: help, time, joke, echo\r\n");

		if (message.find(":time") != std::string::npos)
			sendMessage("PRIVMSG " + _channel + " :Current time: " + getTime() + "\r\n");

		if (message.find(":joke") != std::string::npos)
			sendMessage("PRIVMSG " + _channel + " :Why do programmers prefer dark mode? Because light attracts bugs!\r\n");

		if (message.find(":echo") != std::string::npos)
		{
			std::string msg;
			msg = extractAfterColon(message);
			sendMessage("PRIVMASG " + _channel + ":" + msg + "\r\n");
		}
	}
}

void Bot::run()
{
	_socketFd = socket(AF_INET, SOCK_STREAM, 0);
	if (_socketFd == -1)
	{
		std::cerr << "Error socket(): " << strerror(errno) << std::endl;
		return;
	}

	struct sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(_port);
	if (inet_pton(serverAddr.sin_family, _serverIp.c_str(), &serverAddr.sin_addr) < 0)
	{
		std::cerr << "Error inet_pton(): " << strerror(errno) << std::endl;
		return;
	}

	if (connect(_socketFd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0)
	{
		std::cerr << "Error connect(): " << strerror(errno) << std::endl;
		close(_socketFd);
		return;
	}
	registerToServer();
	handleIncomingMessage();
}

