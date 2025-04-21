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
std::vector<Channel> &Server::getChannelList() { return _channel_list; }
Channel *Server::getChannelByName(std::string channel_name)
{
	const std::vector<Channel> &channels = getChannelList();
	for (size_t i = 0; i < channels.size(); ++i)
	{
		if (channels[i].getName() == channel_name)
			return const_cast<Channel *>(&channels[i]);
	}
	return NULL;
}

Client *Server::getClientByNick(std::string nickname)
{
	// std::cout << MAGENTA << "getClientByNick:" << RESEND;
	for (size_t i = 0; i < _client_list.size(); ++i)
	{
		// std::cout << MAGENTA << "Client[i] pointer: ";
		// std::cout << &_client_list[i] << RESEND;
		if (_client_list[i].getNickname() == nickname)
			return &_client_list[i];
	}
	return NULL;
}

/* setters */

void Server::setNewChannel(std::string channel_name)
{
	Channel newChannel(channel_name);
	_channel_list.push_back(newChannel);
}

void Server::setNewNick(std::string old_nick, std::string new_nick)
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

/* clears */

void Server::removeChannel(std::string channel_name)
{
	std::vector<Channel>::iterator it;
	for (it = _channel_list.begin(); it != _channel_list.end(); ++it)
	{
		if (it->getName() == channel_name)
		{
			_channel_list.erase(it);
			break;
		}
	}
}
