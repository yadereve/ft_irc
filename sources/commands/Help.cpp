#include "../../includes/Client.hpp"

int Client::help()
{
    std::ostringstream oss;

    oss << std::endl;
    pass(oss);
    oss << std::endl;
    nick(oss);
    oss << std::endl;
    user(oss);
    oss << std::endl;

    messageClient(oss.str());

    return 0;
}
