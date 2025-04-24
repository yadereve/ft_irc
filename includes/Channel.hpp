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

	_mapclient			clients;
	_mapclient			invited;
	std::vector<Client*> operators;
	std::string			mode;
	std::string			name;
	std::string			key;
	std::string			topic;
	std::string			password;
	int					usersLimit;
	int					usersCount;
	bool				inviteOnly;
	bool				topicRestricted;

public:
	// Construtor e destrutor
	Channel();
	Channel(std::string);
	~Channel();

	// Métodos principais
	void				addClient(Client *client);
	void				removeClient(Client *client);
	bool				isMember(Client *client);
	bool				addOperator(Client *client);
	bool				removeOperator(Client *client);
	bool				isOperator(Client *client) const;

	// Getters e setters
	const std::string&	getName(void) const;
	void				setName(const std::string &src);

	const std::string&	getTopic(void) const;
	void				setTopic(const std::string &src);

	const std::string&	getPassword(void) const;
	void				setPassword(const std::string& password);
	void				removePassword();

	const std::string&	getKey(void) const;
	void				setKey(std::string &src);

	int					getUserLimit() const;
	void				setUserLimit(int limit);
	void				removeUserLimit();

	int					getUserCount() const;
	void				setUserCount(int count);

	const std::string	getMode(void) const;

	const _mapclient&	getClients(void) const;
	void				setClients(_mapclient &src);

	const _mapclient&	getInvited(void) const;
	void				setInvited(_mapclient &src);

	// Invite-only
	void				setInviteOnly(bool value);
	bool				isInviteOnly() const;

	// Restrição de tópico
	void				setTopicRestriction(bool value);
	bool				isTopicRestricted() const;

	// Outros
	bool				isEmpty(void);
	std::string			getPrefix(Client *client) const;
	std::string			getSymbol(void) const;

	// Mensagens
	void				sendMessage(const std::string &source, const std::string &command, const std::string &args);
	void				privateMessage(const std::string &source, const std::string &command, const std::string &args);

	// Convites
	bool				isInvited(Client *client);
	void				addInvited(Client *client);
	void				delInvited(Client *client);

	// Modos
	std::string			addMode(const std::string &mode);
	std::string			delMode(const std::string &mode);
};

// Para debug/log
std::ostream &operator<<(std::ostream &o, const Channel &src);

#endif
