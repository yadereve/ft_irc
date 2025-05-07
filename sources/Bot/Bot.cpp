#include "../../includes/Bot.hpp"

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

void Bot::registerToServer()
{
	sendMessage("PASS " + _password + "\r\n");
	sendMessage("NICK " + _nickname + "\r\n");
	sendMessage("USER " + _username + " * * :" + _username + "_" + "\r\n");
	sendMessage("JOIN " + _channel + "\r\n");
}
static std::string randomJoke()
{
	srand(time(0));
	int randomNum =	rand() % 11;
	std::cout << randomNum;
	switch (randomNum)
	{
		case 0:
			return " :How do you comfort a JavaScript bug? You console it.\r\n";
		case 1:
			return " :Why do programmers prefer dark mode? Because light attracts bugs!\r\n";
		case 2:
			return " :Why don’t programmers like nature? It has too many bugs.\r\n"; 
		case 3:
			return " :Why do programmers hate going outside? The sunlight causes too many errors.\r\n";
		case 4:
			return " :How many programmers does it take to change a light bulb? None. It’s a hardware problem!\r\n";
		case 5:
			return " :Why was the developer unhappy at his job? He wanted arrays but got strings.\r\n";
		case 6:
			return " :What do you call a programmer who doesn't write code? A debugger.\r\n";
		case 7:
			return " :Why was the JavaScript developer so good at relationships? Because he always knew how to handle promises.\r\n";
		case 8:
			return " :Why do C++ developers prefer coffee? Because it’s an object-oriented drink.\r\n";
		case 9:
			return " :What’s a programmer's favorite hangout spot? The loop.\r\n";
		case 10:
			return " :Why did the computer go to the doctor? It had a virus!\r\n";
	}
	return "\r\n";
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
			sendMessage("PRIVMSG " + _channel + " :Available commands: help, time, joke\r\n");

		if (message.find(":time") != std::string::npos)
			sendMessage("PRIVMSG " + _channel + " :Current time: " + getTime() + "\r\n");

		if (message.find(":joke") != std::string::npos)
			sendMessage("PRIVMSG " + _channel + randomJoke());
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

