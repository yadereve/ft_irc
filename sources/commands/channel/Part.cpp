#include "../../../includes/Client.hpp"

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
    std::string channel = _arguments[0];

    // check if channel starts with #
    if (channel[0] != '#')
        return ERR_BAD_CHAN_MASK;

    // check if channel exist
    if (channelExist(channel) == false)
        return ERR_NO_SUCH_CHANNEL;

    // TODO - check if user is on channel (CHANNEL)
    if (/* user on channel == false */ 0)
        return ERR_NOT_ON_CHANNEL;

    // TODO - user is removed from a channel (CHANNEL)
    printMessage(LEAVE_CHANNEL);

    // TODO - check if channel is empty (CHANNEL)
    if (/* channel empty == true*/ 0)
        _server.removeChannel(channel);

    return 0;
}
