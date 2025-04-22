#include "../../../includes/Client.hpp"

void Client::quit(std::ostringstream &oss)
{
    oss << CYAN << "├─ " << CYAN BOLT << "QUIT [<reason>]" << std::endl;
    oss << CYAN << "│"   << WHITE << "\tLeave the server" << std::endl;
}

int Client::quit()
{
    std::string reason;
    if (_arguments.size() < 1)
        reason = "";
    else
	{
		reason = _arguments[0];
		reason.insert(0, ":");
	}

    // print quit message to user (CLIENT)
	messageClient(":" + _nick + "!" + _user + " QUIT " + reason + "\r\n");

    // TODO - send message to the channels with the (string) reason (CHANNEL)

    // TODO - remove client form server (SERVER)
	DEBUG("_socket: " << _socket);
	_server.handleQuit(_socket);

    return 0;
}
