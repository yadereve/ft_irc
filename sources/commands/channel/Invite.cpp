#include "../../../includes/Client.hpp"
#include "../../../includes/Channel.hpp"

void Client::invite(std::ostringstream &oss)
{
    oss << CYAN << "├─ " << CYAN BOLT << "INVITE <nick> <channel>" << std::endl;
    oss << CYAN << "│" << WHITE << "\tInvite a user to a channel" << std::endl;
}

int Client::invite()
{
    // check if is authenticated
    if (_authenticated_check == false)
        return ERR_NOT_AUTHENTICATED;

    // check if invite have 1 argument
    if (_arguments.size() != 2)
        return ERR_NEED_MORE_PARAMS;

    // initialize values
    std::string username = _arguments[0];
    std::string channel_name = _arguments[1];

    // check if user exist
    if (!nickExist(username))
        return ERR_NO_SUCH_NICK;

    // check if channel starts with #
    if (channel_name[0] != '#')
        return ERR_BAD_CHAN_MASK;

    // check if channel exist
    Channel* channel = _server.getChannelByName(channel_name);
    if (!channel)
        return ERR_NO_SUCH_CHANNEL;

    // TODO - check if user is on channel (CHANNEL)
    if (!channel->isMember(this))
        return ERR_NOT_ON_CHANNEL;

    // TODO - check if actual user has OP permissions to invite (CHANNEL)
    if (!channel->isOperator(this))
        return ERR_CHAN_OP_PRIV_NEEDED;

    // TODO - add new user to the channel (CHANNEL)
    Client* target = _server.getClientByNick(username);
    if (!target)
        return ERR_NO_SUCH_NICK;
    if (channel->isMember(target))
        return ERR_USER_ON_CHANNEL;
    
    channel->addInvited(target);
    printMessage(INVITE_SUCCESS, target->getNickname(), channel_name);

    target->printMessage(YOU_WERE_INVITED, this->getNickname(), channel_name);

    return 0;
}
