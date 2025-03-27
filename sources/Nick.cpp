#include "../includes/Client.hpp"

bool Client::NickAlreadyExist(std::string str)
{
    std::vector<std::string> list = _server.GetNickList();
    if (std::find(list.begin(), list.end(), str) != list.end())
    {
        return true;
    }
    return false;
}

int Client::Nick()
{
    // if PASS not setted yet
    if (_pass_check == false)
    {
        return ERR_NOT_AUTHENTICATED;
    }
    // if NICK doesn't has arguments
    if (_arguments.size() < 1)
    {
        return ERR_NO_NICKNAME_GIVEN;
    }
    // if NICK has too many argument or if NICK isn't valid
    if (_arguments.size() > 1 || ValidName(_arguments[0]) == false)
    {
        return ERR_ERRONEUS_NICKNAME;
    }
    // if NICK isn't unique
    if (NickAlreadyExist(_arguments[0]) == true)
    {
        return ERR_NICKNAME_IN_USE;
    }

    // set NICK
    _server.SetElementNickList(_nick, _arguments[0]);
    _nick = _arguments[0];
    _nick_check = true;

    return NICKNAME_SUCCESS;
}