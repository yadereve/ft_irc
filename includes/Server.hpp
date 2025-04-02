#ifndef SERVER_HPP
#define SERVER_HPP

#include "text_format.h"
#include "config_macros.h"

#include "Client.hpp"

class Server
{
public:
	Server();
	Server(const std::string port, const std::string pass);
	Server(const Server& other);
	Server& operator=(const Server& other);
	~Server();
	
	 //METHODS
	int start();
	// getters
	std::string GetPass() const;
	std::vector<std::string> GetNickList() const;
	// setters
	void SetElementNickList(std::string, std::string);

private:
	// ATTRIBUTES
	std::string _port;
	std::string _pass;
	std::string _host;
	std::vector<std::string> _nick_list;

};

#endif
