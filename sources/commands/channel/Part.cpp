#include "../../../includes/Client.hpp"
#include "../../../includes/Channel.hpp"

void Client::part(std::ostringstream &oss)
{
    oss << CYAN BOLT << "PART <channel>" RESEND;
    oss << WHITE << "\tLeave a channel" RESEND;
}

int Client::part()
{
    // check if is authenticated
    if (_authenticated_check == false)
        return ERR_NOT_AUTHENTICATED;
        
    // check if part have 1 argument
    if (_arguments.size() != 1)
        return ERR_NEED_MORE_PARAMS;

    // initialize values
    std::string channel_name = _arguments[0];

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

    // TODO - user is removed from a channel (CHANNEL)
    target_channel->removeClient(this);
    printMessage(LEAVE_CHANNEL);

    // TODO - check if channel is empty (CHANNEL)
    if (target_channel && target_channel->getClients().empty())
    {
        _server.removeChannel(channel_name);
        target_channel = NULL;
    }
    return 0;
}
