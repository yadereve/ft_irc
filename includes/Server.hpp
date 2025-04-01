#ifndef SERVER_HPP
#define SERVER_HPP

#include "text_format.h"
#include "config_macros.h"

#include "Client.hpp"

class Server
{
public:
	Server(const std::string port, const std::string pass);
	Server(const Server &other);
	Server &operator=(const Server &other);
	~Server();

	// METHODS
	int start();
	// getters
	std::string getPass() const;
	std::vector<std::string> getNickList() const;
	std::vector<std::string> getCommandList() const;
	// setters
	void setElementNickList(std::string, std::string);

private:
	Server();

	// ATTRIBUTES
	std::string _port;
	std::string _pass;
	std::string _host;
	std::vector<std::string> _nick_list;
	std::vector<std::string> _command_list;

	// METHODS
	void commandListInitializer(std::vector<std::string> &);
};

#endif
