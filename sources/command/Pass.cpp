#include "../../includes/Client.hpp"

void Client::Pass()
{
    std::string pass = _server.getPass();

    if (_message.size() > 0 && _message.front() == pass)
    {
        PrintMessage(GREEN "Correct password\n" RESET);
        _pass_check = true;
        return;
    }
    PrintMessage(RED "Incorrect password\n" RESET);
}
