#include "../../includes/Server.hpp"

void Server::commandListInitializer(std::vector<std::string> &list)
{
	list.push_back("HELP");
	list.push_back("PING");
	list.push_back("QUIT");
	list.push_back("PASS");
	list.push_back("NICK");
	list.push_back("USER");
	list.push_back("JOIN");
	list.push_back("MODE");
	list.push_back("TOPIC");
	list.push_back("PART");
	list.push_back("PRIVMSG");
	list.push_back("INVITE");
	list.push_back("KICK");
}

std::string Server::getTime() const
{
	time_t timestamp;
	time(&timestamp);
	std::string currentTime = asctime(localtime(&timestamp));
	currentTime.erase(currentTime.end()-1); // remove '\n'
	return currentTime;
}

void Server::start()
{
	createListeningSocket();
	setupPullFds();

	std::cout << "[" << getTime() << "] " << "Server is running on port " << _port << std::endl;
	while (run)
		handlePollEvents();
}

void Server::createListeningSocket()
{
	// Create sockets
	_listening = socket(AF_INET, SOCK_STREAM, 0);
	DEBUG("_listening: " << _listening);
	if (_listening == -1)
		throw std::runtime_error("Can't create socket! Quitting");

	// Set socket to be reusable
	int opt = 1;
	setsockopt(_listening, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

	// Bind the ip address and port to socket
	_hint.sin_family = AF_INET;
	_hint.sin_port = htons(atoi(_port.c_str()));
	inet_pton(AF_INET, _host.c_str(), &_hint.sin_addr);
	if (bind(_listening, (sockaddr *)&_hint, sizeof(_hint)) == -1)
		throw std::runtime_error("Can't bind socket!");

	// Tell Winsock the socket is for listening
	if (listen(_listening, SOMAXCONN) == -1)
		throw std::runtime_error("Can't listen on socket!");

	// Non-blocking mode (as required for MacOS)
	fcntl(_listening, F_SETFL, O_NONBLOCK);
}

void Server::setupPullFds()
{
	// Poll setup
	pollfd listeningFd = {_listening, POLLIN, 0};
	_pollFds.push_back(listeningFd);
}

void Server::handlePollEvents()
{
	int pollCount = poll(_pollFds.data(), _pollFds.size(), -1);
	if (pollCount == -1)
	{
		if (errno == EINTR)
			return;
		throw std::runtime_error("Poll error!");
	}

	if (_pollFds[0].revents & POLLIN)
		handleNewConnection();
	for (size_t i = 1; i < _pollFds.size(); ++i)
	{
		if (_pollFds[i].revents & POLLIN)
			handleClientMessage(i);
	}
}

void Server::handleNewConnection()
{
	sockaddr_in clientAddr;
	socklen_t clientSize = sizeof(clientAddr);
	int clientSocket = accept(_listening, (sockaddr *)&clientAddr, &clientSize);
	if (clientSocket == -1)
		throw std::runtime_error("Error accepting client!");

	DEBUG("clientSocket: " << clientSocket);
	// Set client socket to non_blocking
	fcntl(clientSocket, F_SETFL, O_NONBLOCK);

	// Add to poll list
	pollfd clientFd = {clientSocket, POLLIN, 0};
	_pollFds.push_back(clientFd);

	// Create client object
	Client* newClient = new Client(*this, clientSocket);
	_client_list.insert((std::make_pair(clientSocket, newClient)));

	std::cout << "[" << getTime() << "] " << GREEN << "New client connected: " << clientSocket << RESET << std::endl;
}

void Server::handleClientMessage(size_t& index)
{
	char buf[4096];
	memset(buf, 0, sizeof(buf));
	int clientSocket = _pollFds[index].fd;
	int bytesReceived = recv(clientSocket, buf, sizeof(buf), 0);

	if (bytesReceived <= 0)
	{
		// Client disconnected
		std::cout << "[" << getTime() << "] " << RED << "Client " << clientSocket << " disconnected" << RESET << std::endl;
		close(clientSocket);
		_pollFds.erase(_pollFds.begin() + index);
		_client_list.erase(clientSocket);
		--index; // Adjust index after removal
	}
	else
	{
		// Process client message
		std::map<int, Client*>::iterator it = _client_list.find(clientSocket);
		if (it != _client_list.end())
			it->second->executeCommand(std::string(buf, bytesReceived));
	}
}

void Server::handleQuit(int clientSocket)
{
	std::map<int, Client*>::iterator it = _client_list.find(clientSocket);
	if (it == _client_list.end())
		return;
	std::cout << "[" << getTime() << "] " << RED << "Client " << clientSocket << " disconnected" << RESET << std::endl;
	close(clientSocket);
	for (size_t i = 0; i < _pollFds.size(); ++i)
	{
		if (_pollFds[i].fd == clientSocket)
		{
			_pollFds.erase(_pollFds.begin() + i);
			break;
		}
	}
	_client_list.erase(it);
}

void Server::privateMessage(std::string nick, std::string msg)
{
	Client *c = getClientByNick(nick);
	if (c)
	{
		DEBUG("privmsg nick: " << nick);
		c->messageClient(msg + "\r\n");
	}
}
