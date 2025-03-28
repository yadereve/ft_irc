#include "../../includes/Client.hpp"

void Client::Nick()
{
    if (_pass_check == true && _message.size() > 0)
    {
        PrintMessage(GREEN "Correct password\n" RESET);
        _pass_check = true;
        return;
    }
    PrintMessage(RED "Incorrect password\n" RESET);
}
