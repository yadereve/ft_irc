#include "../../../includes/Client.hpp"

void Client::help(std::ostringstream &oss)
{
    oss << CYAN BOLT << "HELP" RESEND;
    oss << WHITE << "\tSee all the commands syntaxes and functions" RESEND;
}

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
    help(oss);
    oss << std::endl;
    ping(oss);
    oss << std::endl;
    quit(oss);
    // channel commands
    oss << std::endl;
    join(oss);
    oss << std::endl;
    part(oss);
    oss << std::endl;
    topic(oss);
    oss << std::endl;
    kick(oss);
    oss << std::endl;

    messageClient(oss.str());

    return 0;
}
