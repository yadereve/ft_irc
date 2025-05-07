#ifndef SERVER_HPP
# define SERVER_HPP

# include "format/text_format.h"
# include "format/config_macros.h"
# include <string>
# include <vector>
# include <map>

# include "Client.hpp"
# include "Channel.hpp"

class Channel;
class Client;

class Server
{
public:
	Server(const std::string port, const std::string pass);
	Server(const Server &other);
	Server &operator=(const Server &other);
	virtual ~Server();

	// METHODS
	void start();
	void createListeningSocket();
	void setupPullFds();
	void handlePollEvents();
	void handleNewConnection();
	void handleClientMessage(size_t& index);
	void handleQuit(int clientSocket);
	std::string getTime() const;
	void privateMessage(std::string nick ,std::string msg);

	// getters
	std::string getPass() const;
	std::vector<std::string> getNickList() const;
	std::vector<std::string> getCommandList() const;
	std::vector<Channel>& getChannelList();
	Client* getClientByNick(const std::string& nickname) const;
	Channel *getChannelByName(std::string);
	std::string getHostname() const;
	// setters
	void setNewNick(std::string, std::string);
	void setNewChannel(std::string);
	// clears
	void removeChannel(std::string channel_name);

private:
	Server();

	// ATTRIBUTES
	std::string _port;
	std::string _pass;
	std::string _host;
	sockaddr_in _hint;
	int _listening;
	std::vector<pollfd> _pollFds;
	std::map<int, Client> _client_list;
	std::vector<std::string> _nick_list;
	std::vector<std::string> _command_list;
	std::vector<Channel> _channel_list;

	// METHODS
	void commandListInitializer(std::vector<std::string> &);
};

#endif
