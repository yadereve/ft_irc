#include "../../../includes/Client.hpp"

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
    // check if join have 1 argument
    if (_arguments.size() != 1)
        return ERR_NEED_MORE_PARAMS;

    // check if channel starts with #
    if (_arguments[0][0] != '#')
        return ERR_BAD_CHAN_MASK;

    // check if channel already exist
    if (channelExist(_arguments[0]) == true)
    {
        // if exist just join channel
        // TODO - user join channel (CHANNEL)
        printMessage(JOINED_CHANNEL);
    }
    else
    {
        // if it doesn't exist
        // - create it
        // - join it
        // - become channel OP

        // create new channel (SERVER)
        _server.setNewChannel(_arguments[0]);
        printMessage(CHANNEL_CREATED);

        // TODO - user join channel (CHANNEL)
        printMessage(JOINED_CHANNEL);

        // TODO - user become channel OP (CHANNEL)
        printMessage(CHANNEL_OP);
    }
    return 0;
}
