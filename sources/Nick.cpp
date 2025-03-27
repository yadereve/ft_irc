#include "../includes/Client.hpp"

static bool ValidNick(std::string str)
{
    if (str.length() < 3)
        return false;
    if (!isalpha(str[0]))
        return false;
    for (size_t i = 0; i < str.length(); i++)
        if (!isalnum(str[i]))
            return false;
    return true;
}

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
    // server password is setted
    if (_pass_check == false)
    {
        return ERR_NOT_AUTHENTICATED;
    }
    // NICK need another argument
    if (_message.size() < 1)
    {
        return ERR_NO_NICKNAME_GIVEN;
    }
    // NICK only has one argument and it is valid
    if (_message.size() > 1 || ValidNick(_message[0]) == false)
    {
        return ERR_ERRONEUS_NICKNAME;
    }
    // NICK is unique
    if (NickAlreadyExist(_message[0]) == true)
    {
        return ERR_NICKNAME_IN_USE;
    }

    _server.SetElementNickList(_message[0]);

    _nick_check = true;
    MessageUser(GREEN "Nick added\n" RESET);
    
    return 0;
}