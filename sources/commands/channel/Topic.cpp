#include "../../../includes/Client.hpp"

void Client::topic(std::ostringstream &oss)
{
    oss << CYAN BOLT << "TOPIC <channel>" RESEND;
    oss << WHITE << "\tSee the channel topic" RESEND;
    oss << RESEND;
    oss << CYAN BOLT << "TOPIC <channel> <new_topic>" RESEND;
    oss << WHITE << "\tChange the channel topic" RESEND;
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
    std::string channel = _arguments[0];
    std::string topic = "";
    if (_arguments.size() == 2)
        topic = _arguments[1];

    // check if channel starts with #
    if (channel[0] != '#')
        return ERR_BAD_CHAN_MASK;

    // check if channel exist
    if (channelExist(channel) == false)
        return ERR_NO_SUCH_CHANNEL;

    // TODO - check if user is on channel (CHANNEL)
    if (/* user on channel == false */ 0)
        return ERR_NOT_ON_CHANNEL;

    // show topic
    if (_arguments.size() == 1)
    {
        // TODO - show channel topic do the client (CHANNEL)
        printMessage(SHOWING_CHANNEL_TOPIC);
    }
    // change topic
    if (_arguments.size() == 2)
    {
        // TODO - change channel topic do the new one (CHANNEL)
        printMessage(CHANNEL_TOPIC_CHANGED);
    }

    return 0;
}
