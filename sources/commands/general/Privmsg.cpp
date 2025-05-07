#include "../../../includes/Client.hpp"

void Client::privmsg(std::ostringstream &oss)
{
    oss << CYAN << "├─ " << CYAN BOLT << "PRIVMSG <nick/channel> :<message>" << std::endl;
    oss << CYAN << "│" << WHITE << "\tSend a message to a nick or channel" << std::endl;
}

int Client::privmsg()
{
    // check if is authenticated
    if (_authenticated_check == false)
        return ERR_NOT_AUTHENTICATED;

    // check if has a token
    if (_arguments.size() < 2)
        return ERR_NEED_MORE_PARAMS;

    // initialize values
    std::string destination = _arguments[0];
    std::string message;
    for (size_t i = 1; i < _arguments.size(); i++)
    {
        message += _arguments[i];
        message += " ";
    }

    // check if message starts with ':'
    if (message[0] != ':')
        return ERR_NO_MESSAGE_GIVEN;
    message.erase(0, 1);

    // if is a channel
    if (destination[0] == '#')
    {
        // check if channel exist
        if (!channelExist(destination))
            return ERR_NO_SUCH_CHANNEL;

        // TODO - check if user is on channel (CHANNEL)
        Channel *channel = _server.getChannelByName(destination);
        if (!channel->isMember(this))
            return ERR_USER_NOT_IN_CHANNEL;

        // TODO - send message to each client on channel (CHANNEL)
        const std::map<std::string, Client *> &clients = channel->getClients();
        for (std::map<std::string, Client *>::const_iterator it = clients.begin(); it != clients.end(); ++it)
        {
            Client *target = it->second;
            if (target != this) // não envia para si mesmo
                target->messageClient(this->getNickname() + " to " + destination + ": " + message);
        }
    }
    // if is a user
    else
    {
        // check if user exist
        if (!nickExist(destination))
            return ERR_NO_SUCH_NICK;

        // send message to the other client
        //_server.privateMessage(destination,":" + _nick + " PRIVMSG " + destination + " " + message); // FIX
        Client *target = _server.getClientByNick(destination);
        if (target)
            target->messageClient(this->getNickname() + " (priv): " + message + "\r\n");
    }

    return 0;
}
