#include "../../../includes/Client.hpp"

void Client::ping(std::ostringstream &oss)
{
    oss << CYAN BOLT << "PING <token>" RESEND;
    oss << WHITE << "\tPings the server" RESEND;
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
