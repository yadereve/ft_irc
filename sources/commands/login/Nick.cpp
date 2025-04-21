#include "../../../includes/Client.hpp"

void Client::nick(std::ostringstream &oss)
{
    oss << CYAN << "├─ " << CYAN BOLT << "NICK <nickname>" << std::endl;
    oss << CYAN << "│"   << WHITE ITALICS << "\t(Needed to join the server)" << std::endl;
    oss << CYAN << "│"   << WHITE << "\tSet a new nickname" << std::endl;
    oss << CYAN << "│"   << WHITE << "\tYour nickname should start with a letter and" << std::endl;
    oss << CYAN << "│"   << WHITE << "\tcan only have numbers, letters, hyphen (-) and underscore (_)" << std::endl;
}

bool Client::nickAlreadyExist(std::string str)
{
    std::vector<std::string> list = _server.getNickList();
    if (std::find(list.begin(), list.end(), str) != list.end())
    {
        return true;
    }
    return false;
}

/*
 * NICK <nick>
 */
int Client::nick()
{
    // if PASS not setted yet
    if (_pass_check == false)
        return ERR_NOT_AUTHENTICATED;

    // if NICK doesn't has arguments
    if (_arguments.size() < 1)
        return ERR_NO_NICKNAME_GIVEN;

    // if NICK has too many argument or if NICK isn't valid
    if (_arguments.size() > 1 || validName(_arguments[0]) == false)
        return ERR_ERRONEUS_NICKNAME;

    // if NICK isn't unique
    if (nickAlreadyExist(_arguments[0]) == true)
        return ERR_NICKNAME_IN_USE;

    // set NICK
    _server.setNewNick(_nick, _arguments[0]);
    _nick = _arguments[0];
    _nick_check = true;

    return NICKNAME_SUCCESS;
}
