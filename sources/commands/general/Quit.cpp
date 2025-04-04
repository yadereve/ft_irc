#include "../../../includes/Client.hpp"

void Client::quit(std::ostringstream &oss)
{
    oss << CYAN BOLT << "QUIT <reason>" RESEND;
    oss << WHITE ITALICS << "\t(Reason is optional)" RESEND;
    oss << WHITE << "\tLeave the server" RESEND;
}

int Client::quit()
{
    std::string reason;
    if (_arguments.size() < 1)
        reason = "";
    else
        reason = _arguments[0];

    // print quit message to user (CLIENT)
    messageClient(BRIGHT_RED "Leaving the server...\n" RESET);

    //TODO - send message to the channels with the reason (CHANNEL)

    //TODO - remove client form server (SERVER)
    
    return 0;
}
