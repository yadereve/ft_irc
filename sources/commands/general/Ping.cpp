#include "../../../includes/Client.hpp"

void Client::ping(std::ostringstream &oss)
{
    oss << CYAN << "├─ " << CYAN BOLT << "PING <token>" << std::endl;
    oss << CYAN << "│" << WHITE << "\tPings the server" << std::endl;
}

int Client::ping()
{
    // check if is authenticated
    if (_authenticated_check == false)
        return ERR_NOT_AUTHENTICATED;

    // check if has a token
    if (_arguments.size() != 1)
        return ERR_NEED_MORE_PARAMS;

    return PONG;
}
