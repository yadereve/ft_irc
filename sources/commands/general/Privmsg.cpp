#include "../../../includes/Client.hpp"

void Client::privmsg(std::ostringstream &oss)
{
    oss << CYAN << "├─ " << CYAN BOLT << "PRIVMSG <nick/channel> <message>" << std::endl;
    oss << CYAN << "│" << WHITE << "\tSend a message to a nick or channel" << std::endl;
}

int Client::privmsg()
{
    // check if is authenticated
    if (_authenticated_check == false)
        return ERR_NOT_AUTHENTICATED;

    // check if has a token
    if (_arguments.size() != 2)
        return ERR_NEED_MORE_PARAMS;

    // initialize values
    std::string destination = _arguments[0];
    std::string message = _arguments[1];

    // if is a channel
    if (destination[0] == '#')
    {
        // check if channel exist
        if (!channelExist(destination))
            return ERR_NO_SUCH_CHANNEL;

        // TODO - check if user is on channel (CHANNEL)
        if (0 /* user not on channel */)
            return ERR_USER_NOT_IN_CHANNEL;

        // TODO - send message to each client on channel (CHANNEL)
    }
    // if is a user
    else
    {
        // check if user exist
        if (!nickExist(destination))
            return ERR_NO_SUCH_NICK;

        // send message to the other client
        _server.privateMessage(destination, message);
    }

    return PONG;
}
