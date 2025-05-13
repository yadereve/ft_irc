#include "../../../includes/Client.hpp"
#include "../../../includes/Channel.hpp"

void Client::kick(std::ostringstream &oss)
{
    oss << CYAN << "├─ " << CYAN BOLT << "KICK <channel> <user> [<message>]" << std::endl;
    oss << CYAN << "│" << WHITE << "\tKicks a user from a channel" << std::endl;
}

int Client::kick()
{
    // check if is authenticated
    if (_authenticated_check == false)
        return ERR_NOT_AUTHENTICATED;

    // check if part have 1 argument
    if (_arguments.size() != 2 && _arguments.size() != 3)
        return ERR_NEED_MORE_PARAMS;

    // initialize values
    std::string channel_name = _arguments[0];
    std::string username = _arguments[1];
    std::string message = "";
    if (_arguments.size() == 3)
        message = _arguments[2];

    // check if user exist
    if (!nickExist(username))
        return ERR_NO_SUCH_NICK;

    // check if channel starts with #
    if (channel_name[0] != '#')
        return ERR_BAD_CHAN_MASK;

    // check if channel exist
    if (!channelExist(channel_name))
        return ERR_NO_SUCH_CHANNEL;

    // TODO - check if user is on channel (CHANNEL)
    Channel *channel = NULL;
    const std::vector<Channel> &channels = _server.getChannelList();
    for (size_t i = 0; i < channels.size(); ++i)
    {
        if (channels[i].getName() == channel_name)
        {
            channel = const_cast<Channel *>(&channels[i]);
            break;
        }
    }
	Client *target = _server.getClientByNick(username);
	if (!target || !channel->isMember(target))
	    return ERR_NOT_ON_CHANNEL;	
	// TODO - check if actual user has OP permissions on channel (CHANNEL)
	if (!channel->isOperator(this))
	    return ERR_CHAN_OP_PRIV_NEEDED;

	channel->addKickedClient(target);	
    // TODO - user is removed from channel (CHANNEL)
    channel->removeClient(target);

	std::string kick_msg = ":" + getFullMask() + " KICK " + channel_name + " " + username;
	if (!message.empty())
		kick_msg += " :" + message;

	const std::map<std::string, Client*> &clients = channel->getClients();
	for (std::map<std::string, Client*>::const_iterator it = clients.begin(); it != clients.end(); ++it) {
		Client *client = it->second;
		if (client != target) 
			client->messageClient(kick_msg + "\r\n");
	}

	target->messageClient(kick_msg + "\r\n");

	target->messageClient(":" + getFullMask() + " :You have been kicked from " + channel_name + "\r\n");

    if (message.size() > 0)
        printMessage(KICK_SOMEONE_MESSAGE);
    else
        printMessage(KICK_SOMEONE);

    return 0;
}
