#include "../../includes/Server.hpp"

void Server::commandListInitializer(std::vector<std::string> &list)
{
	list.push_back("CAP");
	list.push_back("HELP");
	list.push_back("PING");
	list.push_back("QUIT");
	list.push_back("PASS");
	list.push_back("NICK");
	list.push_back("USER");
	list.push_back("WHOIS");
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
	{
		std::cerr << "Can't create socket! Quitting" << std::endl;
		return -1;
	}

	// Bind the ip address and port to socket
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(atoi(_port.c_str()));
	inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);
	if (bind(listening, (sockaddr *)&hint, sizeof(hint)) == -1)
	{
		std::cout << "Can't bind\n";
		return -2;
	}

	// Tell Winsock the socket is for listening
	listen(listening, SOMAXCONN);

	// Wait for a connection
	sockaddr_in client;
	socklen_t clientSize = sizeof(client);
	int clientSocket = accept(listening, (sockaddr *)&client, &clientSize);
	char host[NI_MAXHOST];	  // Client's remote name
	char service[NI_MAXSERV]; // Service (i. e. port) the client is connect on

	memset(host, 0, NI_MAXHOST); // same as memset(host, 0, NI_MAXHOST);
	memset(service, 0, NI_MAXSERV);

	if (getnameinfo((sockaddr *)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0))
		std::cout << host << " connected on port " << service << std::endl;
	else
	{
		inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
		std::cout << host << " connect on " << ntohs(client.sin_port) << std::endl;
	}

	// Close listening socket
	close(listening);

	// While loop: accept and message back to client
	char buff[4096];

	// Create 1 client
	Client client1(*this, clientSocket);

	// Client input wait
	while (true)
	{
		memset(buff, 0, 4096);

		// Wait for client to send data
		int bytesReceived = recv(clientSocket, buff, 4096, 0);
		if (bytesReceived == -1)
		{
			std::cerr << "Error in recv(). Quitting\n";
			break;
		}
		if (bytesReceived == 0)
		{
			std::cout << "Client disconnected\n";
			break;
		}

		client1.ExecuteCommand(std::string(buff, 0, bytesReceived));
	}

	// Close socket
	close(clientSocket);

	return 0;
}
