#include "../../../includes/Client.hpp"
#include "../../../includes/Channel.hpp"


void Client::join(std::ostringstream &oss)
{
    oss << CYAN BOLT << "JOIN <channel>" RESEND;
    oss << WHITE << "\tJoin a channel" RESEND;
    oss << WHITE << "\tIf channel doesn't exist:" RESEND;
    oss << WHITE << "\t- Create a new one" RESEND;
    oss << WHITE << "\t- Become de channel operator" RESEND;
}

int Client::join()
{
    // check if is authenticated
    if (_authenticated_check == false)
        return ERR_NOT_AUTHENTICATED;
        
    // check if join have 1 argument
    if (_arguments.size() != 1)
        return ERR_NEED_MORE_PARAMS;

    // initialize values
    std::string channel_name = _arguments[0];

    // check if channel starts with #
    if (channel_name[0] != '#')
        return ERR_BAD_CHAN_MASK;

    Channel *channel = NULL;

    // check if channel already exist
    if (channelExist(channel_name) == true)
    {
        // if exist just join channel
        // TODO - user join channel (CHANNEL)
        const std::vector<Channel> &channels = _server.getChannelList();
        for (size_t i = 0; i < channels.size(); ++i)
        {
            if (channels[i].getName() == channel_name)
            {
                channel = const_cast<Channel*>(&channels[i]);
                break;
            }
        }
        if (channel && !channel->isMember(this))
        {
            channel->addClient(this);
            printMessage(JOINED_CHANNEL);
        }
    }
    else
    {
        // if it doesn't exist
        // - create it
        // - join it
        // - become channel OP

        // create new channel (SERVER)
        _server.setNewChannel(channel_name);
        const std::vector<Channel> &channels = _server.getChannelList();
        for (size_t i = 0; i < channels.size(); ++i)
        {
            if (channels[i].getName() == channel_name)
            {
                channel = const_cast<Channel*>(&channels[i]);
                break;
            }
        }
        if (channel)
        {
            channel->addClient(this);
            channel->addOperator(this);
            printMessage(CHANNEL_CREATED);
            printMessage(JOINED_CHANNEL);
            printMessage(CHANNEL_OP);
        }

        

        // TODO - user join channel (CHANNEL)
       

        // TODO - user become channel OP (CHANNEL)
       
    }
    
    return 0;
}
