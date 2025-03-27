#include "../includes/Client.hpp"

#define USER_MAX_LEN 12

int Client::User()
{
    /*
     *
     * USER syntax
     *
     * USER <user> * * :<real_name>
     * or
     * USER <user> 0 * :<real_name>
     *
     */

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
    // if USER third arg in not '*'
    if (_arguments[2] != "*")
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