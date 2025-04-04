#include "../../../includes/Client.hpp"

int Client::help()
{
    std::ostringstream oss;

    // login commands
    oss << std::endl;
    pass(oss);
    oss << std::endl;
    nick(oss);
    oss << std::endl;
    user(oss);
    oss << std::endl;
    // general commands
    oss << std::endl;
    ping(oss);
    oss << std::endl;
    quit(oss);
    oss << std::endl;
    join(oss);
    oss << std::endl;

    messageClient(oss.str());

    return 0;
}
