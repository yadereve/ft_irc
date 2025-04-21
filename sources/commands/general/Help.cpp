#include "../../../includes/Client.hpp"

void Client::help(std::ostringstream &oss)
{
    oss << CYAN << "├─ " << CYAN BOLT << "HELP" RESEND;
    oss << CYAN << "│" << WHITE << "\tSee all the commands syntaxes and functions" RESEND;
}

int Client::help()
{
    std::ostringstream oss;

    // login commands
    oss << std::endl;
    oss << CYAN BOLT << "┌─────────────────────────────────────────────────┐" << RESEND;
    oss << CYAN BOLT << "│                    HELP MENU                    │" << RESEND;
    oss << CYAN BOLT << "├─────────────────────────────────────────────────┘" << RESEND;
    oss << CYAN << "│" << std::endl;
    pass(oss);
    oss << CYAN << "│" << std::endl;
    nick(oss);
    oss << CYAN << "│" << std::endl;
    user(oss);
    oss << CYAN << "│" << std::endl;
    if (_authenticated_check == true)
    {
        // general commands
        oss << CYAN << "│" << std::endl;
        help(oss);
        oss << CYAN << "│" << std::endl;
        ping(oss);
        oss << CYAN << "│" << std::endl;
        quit(oss);
        // channel commands
        oss << CYAN << "│" << std::endl;
        join(oss);
        oss << CYAN << "│" << std::endl;
        part(oss);
        oss << CYAN << "│" << std::endl;
        topic(oss);
        oss << CYAN << "│" << std::endl;
        kick(oss);
        oss << CYAN << "│" << std::endl;
        privmsg(oss);
        oss << CYAN << "│" << std::endl;
    }
    oss << CYAN BOLT << "├─────────────────────────────────────────────────┐" << RESEND;
    oss << CYAN BOLT << "│                    HELP MENU                    │" << RESEND;
    oss << CYAN BOLT << "└─────────────────────────────────────────────────┘" << RESEND;

    messageClient(oss.str());

    return 0;
}
