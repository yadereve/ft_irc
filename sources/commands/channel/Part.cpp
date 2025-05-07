#include "../../../includes/Client.hpp"
#include "../../../includes/Channel.hpp"

void Client::part(std::ostringstream &oss)
{
    oss << CYAN << "├─ "  << CYAN BOLT << "PART <channel>" << std::endl;
    oss << CYAN << "│"    << WHITE << "\tLeave a channel" << std::endl;
}

int Client::part()
{
    // check if is authenticated
    if (_authenticated_check == false)
        return ERR_NOT_AUTHENTICATED;
        
    // check if part have 1 argument
    if (_arguments.empty())
        return ERR_NEED_MORE_PARAMS;

    // initialize values
    std::string channel_name = _arguments[0];
	std::string part_reason;

    // check if channel starts with #
    if (channel_name[0] != '#')
        return ERR_BAD_CHAN_MASK;

    // check if channel exist
    if (!channelExist(channel_name))
        return ERR_NO_SUCH_CHANNEL;

    // TODO - check if user is on channel (CHANNEL)
    Channel *target_channel = NULL;
    const std::vector<Channel>& channels = _server.getChannelList();
    for (size_t i = 0; i < channels.size(); ++i)
    {
        if (channels[i].getName() == channel_name)
        {
            target_channel = const_cast<Channel*>(&channels[i]);
            break;
        }
    }

    if (!target_channel || !target_channel->isMember(this))
		return ERR_NOT_ON_CHANNEL;

	if (_arguments.size() == 2)
		part_reason = _arguments[1];
	
	std::string full_mask = getFullMask();
	std::string part_message = ":" + full_mask + " PART " + channel_name;

	if (!part_reason.empty())
        part_message += " :" + part_reason;

	part_message += "\r\n";

	this->messageClient(part_message);
    target_channel->broadcast(part_message);

    // TODO - user is removed from a channel (CHANNEL)
    target_channel->removeClient(this);
	target_channel->removeOperator(this);
    printMessage(LEAVE_CHANNEL);

    // TODO - check if channel is empty (CHANNEL)
    if (target_channel && target_channel->getClients().empty())
    {
        _server.removeChannel(channel_name);
        target_channel = NULL;
    }
    return 0;
}
