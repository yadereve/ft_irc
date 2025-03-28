#include "../includes/Client.hpp"

void Client::User(std::ostringstream &oss)
{
    oss << CYAN BOLT << "USER <username> * * :<real name>" RESEND;
    oss << WHITE ITALICS << "\t(Needed to join the server)" RESEND;
    oss << WHITE << "\tSet you a username and your real name" RESEND;
    oss << WHITE << "\tYour username and real name should start with a letter and" RESEND;
    oss << WHITE << "\tcan only have numbers, letters, hyphen (-) and underscore (_)" RESEND;
}

#define USER_MAX_LEN 12

/*
 * USER <user> * * :<real_name>
 * USER <user> 0 * :<real_name>
 */
int Client::User()
{
    // if USER was already setted
    if (_user_check == true)
    {
        return ERR_ALREADY_REGISTERED;
    }
    // if NICK not setted yet
    if (_nick_check == false)
    {
        return ERR_NOT_AUTHENTICATED;
    }
    // if USER doesn't has enough args
    if (_arguments.size() < 4)
    {
        return ERR_NEED_MORE_PARAMS;
    }
    // if USER second arg is not '0' neither '*'
    if ((_arguments[1] == "0" || _arguments[1] == "*") == false)
    {
        return ERR_UNKNOWN_COMMAND;
    }
    // if USER third arg is not '*'
    if (_arguments[2] != "*")
    {
        return ERR_UNKNOWN_COMMAND;
    }
    // if USER forth arg doesn't start with ':'
    if (_arguments[3][0] != ':')
    {
        return ERR_UNKNOWN_COMMAND;
    }

    // get user and real_name with proper form
    std::string user = _arguments[0].substr(0, USER_MAX_LEN);
    std::string real_name = _arguments[3].substr(1);

    // if user isn't valid
    if (ValidName(user) == false)
    {
        return ERR_ERRONEUS_USER;
    }
    // if user isn't valid
    if (ValidName(real_name) == false)
    {
        return ERR_ERRONEUS_REAL_NAME;
    }

    // set USER
    _user = user;
    _real_name = real_name;
    _authenticated_check = true;
    _user_check = true;

    return USERNAME_SUCCESS;
}