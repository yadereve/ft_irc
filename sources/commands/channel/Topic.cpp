#include "../../../includes/Client.hpp"

void Client::topic(std::ostringstream &oss)
{
    oss << CYAN << "├─┬─ " << CYAN BOLT << "TOPIC <channel>" << std::endl;
    oss << CYAN << "│ │" << WHITE << "\tSee the channel topic" << std::endl;
    oss << CYAN << "│ │" << std::endl;
    oss << CYAN << "│ └─ " << CYAN BOLT << "TOPIC <channel> <new_topic>" << std::endl;
    oss << CYAN << "│" << WHITE << "\tChange the channel topic" << std::endl;
}

int Client::topic()
{
    // check if is authenticated
    if (_authenticated_check == false)
        return ERR_NOT_AUTHENTICATED;

    // check if topic have 1 argument
    if (_arguments.size() != 1 && _arguments.size() != 2)
        return ERR_NEED_MORE_PARAMS;

    // initialize values
    std::string channel_name = _arguments[0];
    std::string topic = "";
    if (_arguments.size() == 2)
        topic = _arguments[1];

    // check if channel starts with #
    if (channel_name[0] != '#')
        return ERR_BAD_CHAN_MASK;

    // check if channel exist
    if (!channelExist(channel_name))
        return ERR_NO_SUCH_CHANNEL;

    // TODO - check if user is on channel (CHANNEL)
    Channel *channel = NULL;
    std::vector<Channel> &channels = _server.getChannelList();
    for (size_t i = 0; i < channels.size(); ++i)
    {
        if (channels[i].getName() == channel_name)
        {
            channel = &channels[i];
            break;
        }
    }

    if (!channel || !channel->isMember(this)) {
		return ERR_NOT_ON_CHANNEL;
	}

	if (!channel->isOperator(this)) {
		return ERR_CHAN_OP_PRIV_NEEDED;
	}
	    

    // show topic
    if (_arguments.size() == 1)
    {
        // TODO - show channel topic do the client (CHANNEL)
        std::string current_topic = channel->getTopic();
        messageClient("Channel topic for " + channel_name + ": " + current_topic);
        printMessage(SHOWING_CHANNEL_TOPIC);
    }
    // change topic
    if (_arguments.size() == 2)
    {
        // TODO - change channel topic do the new one (CHANNEL)
        channel->setTopic(topic);

        // Broadcast the new topic to the channel
        std::string full_mask = getFullMask();
        std::string topic_message = ":" + full_mask + " TOPIC " + channel_name + " :" + topic;

        channel->broadcast(topic_message + "\r\n");

        messageClient("Channel topic for " + channel_name + " changed to: " + topic);
        printMessage(CHANNEL_TOPIC_CHANGED);
    }
    return 0;
}
