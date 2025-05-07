#include "../../../includes/Client.hpp"

void Client::privmsg(std::ostringstream &oss)
{
    oss << CYAN << "├─ " << CYAN BOLT << "PRIVMSG <nick/channel> :<message>" << std::endl;
    oss << CYAN << "│" << WHITE << "\tSend a message to a nick or channel" << std::endl;
}

int Client::privmsg()
{
    // Check if the client is authenticated
    if (!_authenticated_check)
        return ERR_NOT_AUTHENTICATED;

    // Ensure there are exactly two arguments: target (nick/channel) and message
    if (_arguments.size() < 2)
        return ERR_NEED_MORE_PARAMS;

    // Initialize values
    std::string destination = _arguments[0];  // Target (nickname or channel)
    std::string message;					      // Message to send
	for (size_t i = 1; i < _arguments.size(); i++)
	{
		message += _arguments[i];
		message += " ";
	}

    // Build the message with the user's full mask
    std::string full_mask = getFullMask();
    std::string formatted_message = ":" + full_mask + " PRIVMSG " + destination + " :" + message + "\r\n";
	// check if message starts with ':'
	if (message[0] != ':')
		return ERR_NO_MESSAGE_GIVEN;
	message.erase(0, 1);

    // If it's a channel (starts with '#')
    if (destination[0] == '#')
    {
        // Check if the channel exists
        Channel* channel = _server.getChannelByName(destination);
        if (!channel)
            return ERR_NO_SUCH_CHANNEL;

        // Check if the client is a member of the channel
        if (!channel->isMember(this))
            return ERR_USER_NOT_IN_CHANNEL;

		// Send the message to each client on the channel
		const std::map<std::string, Client*>& clients = channel->getClients();
		for (std::map<std::string, Client*>::const_iterator it = clients.begin(); it != clients.end(); ++it)
		{
		    Client* target = it->second;
		    if (target != this)  // Don't send to the sender
		        target->messageClient(formatted_message);  // Send message to other clients in the channel
		}
    }
    // If it's a private message (a nickname)
    else
    {
        // Check if the target client (nickname) exists
        Client* target = _server.getClientByNick(destination);
        if (!target)
            return ERR_NO_SUCH_NICK;

        // Send the message to the target client
        target->messageClient(formatted_message);
    }

    return 0;
}

