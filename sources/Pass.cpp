#include "../includes/Client.hpp"

/*
 * PASS <pass>
 */
int Client::Pass()
{
    // if PASS was already setted
    if (_pass_check == true)
    {
        return ERR_ALREADY_REGISTERED;
    }
    // if PASS doesn't have args
    if (_arguments.size() < 1)
    {
        return ERR_NEED_MORE_PARAMS;
    }
    // if PASS have too many args
    if (_arguments.size() > 1)
    {
        return ERR_INVALID_PASSWORD;
    }
    // if PASS was incorrect
    if (_arguments.front() != _server.GetPass())
    {
        return ERR_PASSWD_MIS_MATCH;
    }

    // set PASS
    _pass_check = true;

    return PASSWORD_SUCCESS;
}