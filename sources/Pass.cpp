#include "../includes/Client.hpp"

int Client::Pass()
{
    if (_message.size() != 1)
    {
        return ERR_NEED_MORE_PARAMS;
    }
    if (_message.front() != _server.GetPass())
    {
        return ERR_PASSWD_MIS_MATCH;
    }

    _pass_check = true;
    MessageUser(GREEN "Correct password\n" RESET);

    return 0;
}