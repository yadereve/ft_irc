#include "../includes/Client.hpp"

int Client::Pass()
{
    if (_message.size() != 1)
    {
        return ERROR_1;
    }
    if (_message.front() != _server.GetPass())
    {
        return ERROR_2;
    }

    _pass_check = true;
    MessageUser(GREEN "Correct password\n" RESET);

    return OK;
}