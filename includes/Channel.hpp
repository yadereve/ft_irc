#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "format/text_format.h"
# include "format/config_macros.h"
# include "../includes/Client.hpp"
# include <map>
# include <string>
# include <vector>

class Client;

class Channel
{
private:
	typedef std::map<std::string, Client *> _mapclient;

	_mapclient		clients;
	_mapclient		invited;
	std::vector<Client*>	operators;
	std::string			mode;
	std::string			name;
	std::string			key;
	std::string			topic;
	std::string			password;
	int					usersLimit;
	int					usersCount;

public:
	Channel();
	Channel(std::string);
	~Channel();

	// METHODS
	void			addClient(Client *client);
	bool			isMember(Client *client);
	bool			addOperator(Client* client);
	void			removeClient(Client *client);
	bool			isOperator(Client *client) const;
	// GETTERS
	const std::string		&getName(void) const;
	const _mapclient	&getClients(void) const;

	const std::string		&getTopic(void) const;
	void						setTopic(const std::string &src);

//	std::string getName() const;

private:

	// ATTRIBUTES
	std::string _name;

	// Client management
	bool			isEmpty(void);
	
	// Messaging
	void			sendMessage(const std::string &source, const std::string &command, const std::string &args);
	void			privateMessage(const std::string &source, const std::string &command, const std::string &args);
	
	// Invitation
	bool			isInvited(Client *client);
	void			addInvited(Client *client);
	void			delInvited(Client *client);
	
	// Mode management
	std::string		addMode(const std::string &mode);
	std::string		delMode(const std::string &mode);
	std::string		getPrefix(Client *client) const;
	std::string		getSymbol(void) const;

	// Operator methods
	bool			removeOperator(Client* client);

	// Password methods
	void			setPassword(const std::string& password);
	const std::string& getPassword() const;
	void			removePassword();

	// Getters and setters
	void						setName(const std::string &src);
	void						setClients(_mapclient &src);
	const std::string		&getKey(void) const;
	void						setKey(std::string &src);
	void						setInvited(_mapclient &src);
	const _mapclient	&getInvited(void) const;
	const std::string		getMode(void) const;
	int 						getUserLimit() const;
	void						setUserLimit(int limit);
	void 						removeUserLimit();
	int 						getUserCount() const;
	void						setUserCount(int count);
};

std::ostream &operator<<(std::ostream &o, const Channel &src);

#endif
