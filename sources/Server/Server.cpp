#include "../../includes/Server.hpp"

Server::Server()
{
}

Server::Server(const std::string port, const std::string pass)
	: _port(port), _pass(pass), _host("127.0.0.1")
{
	commandListInitializer(_command_list);
}

Server::Server(const Server &other)
{
	(void)other;
}

Server &Server::operator=(const Server &other)
{
	(void)other;
	return *this;
}

Server::~Server()
{
}

/* getters */

std::string Server::getPass() const { return _pass; }
std::vector<std::string> Server::getNickList() const { return _nick_list; }
std::vector<std::string> Server::getCommandList() const { return _command_list; }

/* setters */

void Server::setElementNickList(std::string old_nick, std::string new_nick)
{
	// if there is a old nick
	if (old_nick.length() > 0)
	{
		// look for the old nick on the _nick_lst an erase it
		std::vector<std::string>::iterator it = std::find(_nick_list.begin(), _nick_list.end(), old_nick);
		if (it != _nick_list.end())
			_nick_list.erase(it);
	}
	// add new nick
	_nick_list.push_back(new_nick);
}
