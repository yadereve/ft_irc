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
	for (size_t i = 0; i < _pollFds.size(); ++i)
		close(_pollFds[i].fd);
	close(_listening);
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

std::string Server::getHostname() const
{
    char buffer[256];  // Buffer para armazenar o nome do host
    if (gethostname(buffer, sizeof(buffer)) == 0) {
        return std::string(buffer);  // Retorna o nome do host como string
    } else {
        return "Unknown";  // Se falhar, retorna "Unknown"
    }
}

Client* Server::getClientByNick(const std::string& nickname) const
{
	for (std::map<int, Client>::const_iterator it = _client_list.begin(); it != _client_list.end(); ++it)
	{
		if (it->second.getNickname() == nickname)
			return const_cast<Client*>(&it->second);
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

void Server::handleCC(int signal)
{
	(void)signal;
	Server::~Server();
}

