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

int Server::start()
{
	// Create sockets
	int listening = socket(AF_INET, SOCK_STREAM, 0);
	if (listening == -1)
		throw std::runtime_error("Can't create socket! Quitting");

	// Set socket to be reusable
	int opt = 1;
	setsockopt(listening, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

	// Bind the ip address and port to socket
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(atoi(_port.c_str()));
	inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);
	if (bind(listening, (sockaddr *)&hint, sizeof(hint)) == -1)
		throw std::runtime_error("Can't bind socket!");

	// Tell Winsock the socket is for listening
	if (listen(listening, SOMAXCONN) == -1)
		throw std::runtime_error("Can't listen on socket!");

	// Non-blocking mode (as required for MacOS)
	fcntl(listening, F_SETFL, O_NONBLOCK);

	// Poll setup
	std::vector<pollfd> pollFds;
	pollfd listeningFd = {listening, POLLIN, 0};
	pollFds.push_back(listeningFd);

	std::map<int, Client> clients;

	std::cout << "Server is running on port " << _port << std::endl;

	// Client input wait
	while (true)
	{
		int pollCount = poll(pollFds.data(), pollFds.size(), -1);
		if (pollCount == -1)
			throw std::runtime_error("Poll error!");

		if (pollFds[0].revents & POLLIN)
		{
			sockaddr_in client;
			socklen_t clientSize = sizeof(client);
			int clientSocket = accept(listening, (sockaddr *)&client, &clientSize);
			if (clientSocket == -1)
				std::cerr << "Error accepting client!" << std::endl;
			else
			{
				// Set client socket to non_blocking
				fcntl(clientSocket, F_SETFL, O_NONBLOCK);

				// Add to poll list
				pollfd clientFd = {clientSocket, POLLIN, 0};
				pollFds.push_back(clientFd);

				// Create client object
				// clients[clientSocket] = Client(*this, clientSocket);
				Client newClient(*this, clientSocket);
				clients.insert((std::make_pair(clientSocket, newClient)));
				std::cout << "New client connected: " << clientSocket << std::endl;
			}
		}

		// Check client message
		for (size_t i = 1; i < pollFds.size(); ++i)
		{
			if (pollFds[i].revents & POLLIN)
			{
				char buf[4096];
				memset(buf, 0, 4096);
				int clientSocket = pollFds[i].fd;
				int bytesReceived = recv(clientSocket, buf, 4096, 0);

				if (bytesReceived <= 0)
				{
					// Client disconnected
					std::cout << "Client " << clientSocket << " disconnected" << std::endl;
					close(clientSocket);
					pollFds.erase(pollFds.begin() + i);
					clients.erase(clientSocket);
					--i; // Adjust index after removal
				}
				else
				{
					// Process client message
					std::map<int, Client>::iterator it = clients.find(clientSocket);
					if (it != clients.end())
						it->second.ExecuteCommand(std::string(buf, bytesReceived));
				}
			}
		}
	}

	// Cleanup
	for (size_t i = 0; i < pollFds.size(); ++i)
		close(pollFds[i].fd);
	close(listening);
	return 0;
}

void Server::privateMessage(std::string nick, std::string msg)
{
	// std::cout << MAGENTA << "Getting client..." << RESEND;
	Client *c = getClientByNick(nick);
	// std::cout << MAGENTA << "To: " << c->getNickname() << RESEND;
	c->messageClient(msg);
}